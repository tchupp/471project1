#include "stdafx.h"
#include "Synthesizer.h"
#include "ToneInstrument.h"
#include "SubtractiveInstrument.h"
#include "xmlhelp.h"
#include "Note.h"
#include <algorithm>

using namespace std;

const wstring TONE_INSTRUMENT = L"ToneInstrument";
const wstring SCRATCH_INSTRUMENT = L"ScratchInstrument";
const wstring SUBTRACTIVE_INSTRUMENT = L"SubtractiveInstrument";

CSynthesizer::CSynthesizer()
{
	CoInitialize(nullptr);

	mChannels = 2;
	mSampleRate = 44100.;
	mSamplePeriod = 1 / mSampleRate;
	mTime = 0;

	mBpm = 120;
	mSecPerBeat = 0.5;
	mBeatsPerMeasure = 4;

	mScratchFactory.LoadFile("wav/rave1.wav");
}


CSynthesizer::~CSynthesizer()
{
}

void CSynthesizer::Start()
{
	mCurrentNote = 0;
	mMeasure = 0;
	mBeat = 0;
	mTime = 0;
}

void CSynthesizer::Clear()
{
	mInstruments.clear();
	m_notes.clear();
}

bool CSynthesizer::Generate(double* frame)
{
	//
	// Phase 1: Determine if any notes need to be played.
	//

	while (mCurrentNote < int(m_notes.size()))
	{
		// Get a pointer to the current note
		CNote* note = &m_notes[mCurrentNote];

		// If the measure is in the future we can't play
		// this note just yet.
		if (note->Measure() > mMeasure) break;

		// If this is the current measure, but the
		// beat has not been reached, we can't play
		// this note.
		if (note->Measure() == mMeasure && note->Beat() > mBeat) break;

		//
		// Play the note!
		//

		// Create the instrument object
		CInstrument* instrument = nullptr;
		if (note->Instrument() == TONE_INSTRUMENT)
		{
			instrument = new CToneInstrument();
		}
		else if (note->Instrument() == SCRATCH_INSTRUMENT)
		{
			mScratchFactory.SetNote(note);
			instrument = mScratchFactory.CreateInstrument();
		}
		else if (note->Instrument() == SUBTRACTIVE_INSTRUMENT)
		{
			instrument = new CSubtractiveInstrument(note->Feature(), note->Waveform());
		}
		// Configure the instrument object
		if (instrument != nullptr)
		{
			instrument->SetSampleRate(GetSampleRate());
			instrument->SetNote(note, mSecPerBeat);
			instrument->Start();

			mInstruments.push_back(instrument);
		}

		mCurrentNote++;
	}

	//
	// Phase 2: Clear all channels to silence 
	//

	for (int c = 0; c < GetNumChannels(); c++)
	{
		frame[c] = 0;
	}

	//
	// Phase 3: Play an active instruments
	//

	//
	// We have a list of active (playing) instruments.  We iterate over 
	// that list.  For each instrument we call generate, then add the
	// output to our output frame.  If an instrument is done (Generate()
	// returns false), we remove it from the list.
	//

	for (auto node = mInstruments.begin(); node != mInstruments.end();)
	{
		// Since we may be removing an item from the list, we need to know in 
		// advance, what is after it in the list.  We keep that node as "next"
		auto next = node;
		next++;

		// Get a pointer to the allocated instrument
		CInstrument* instrument = *node;

		// Call the generate function
		if (instrument->Generate())
		{
			// If we returned true, we have a valid sample.  Add it 
			// to the frame.
			for (int c = 0; c < GetNumChannels(); c++)
			{
				frame[c] += instrument->Frame(c);
			}
		}
		else
		{
			// If we returned false, the instrument is done.  Remove it
			// from the list and delete it from memory.
			mInstruments.erase(node);
			delete instrument;
		}

		// Move to the next instrument in the list
		node = next;
	}

	//
	// Phase 4: Advance the time and beats
	//

	// Time advances by the sample period
	mTime += GetSamplePeriod();

	// Beat advances by the sample period divided by the 
	// number of seconds per beat.  The inverse of seconds
	// per beat is beats per second.
	mBeat += GetSamplePeriod() / mSecPerBeat;

	// When the measure is complete, we move to
	// a new measure.  We might be a fraction into
	// the new measure, so we subtract out rather 
	// than just setting to zero.
	if (mBeat > mBeatsPerMeasure)
	{
		mBeat -= mBeatsPerMeasure;
		mMeasure++;
	}

	//
	// Phase 5: Determine when we are done
	//

	// We are done when there is nothing to play.  We'll put something more 
	// complex here later.
	return !mInstruments.empty() || mCurrentNote < int(m_notes.size());
}

void CSynthesizer::OpenScore(CString& filename)
{
	Clear();

	//
	// Create an XML document
	//

	CComPtr<IXMLDOMDocument> pXMLDoc;
	bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
		IID_IXMLDOMDocument, (void**)&pXMLDoc));
	if (!succeeded)
	{
		AfxMessageBox(L"Failed to create an XML document to use");
		return;
	}

	// Open the XML document
	VARIANT_BOOL ok;
	succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
	if (!succeeded || ok == VARIANT_FALSE)
	{
		AfxMessageBox(L"Failed to open XML score file");
		return;
	}

	//
	// Traverse the XML document in memory!!!!
	// Top level tag is <score>
	//

	CComPtr<IXMLDOMNode> node;
	pXMLDoc->get_firstChild(&node);
	for (int i = 0; node != NULL; i++, NextNode(node))
	{
		// Get the name of the node
		CComBSTR nodeName;
		node->get_nodeName(&nodeName);

		if (nodeName == "score")
		{
			XmlLoadScore(node);
		}
	}

	sort(m_notes.begin(), m_notes.end());
}

void CSynthesizer::XmlLoadScore(IXMLDOMNode* xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == L"bpm")
		{
			value.ChangeType(VT_R8);
			mBpm = value.dblVal;
			mSecPerBeat = 1 / (mBpm / 60);
		}
		else if (name == L"beatspermeasure")
		{
			value.ChangeType(VT_I4);
			mBeatsPerMeasure = value.intVal;
		}
	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"instrument")
		{
			XmlLoadInstrument(node);
		}
	}
}

void CSynthesizer::XmlLoadInstrument(IXMLDOMNode* xml)
{
	wstring instrument = L"";
	wstring feature = L"";
	wstring waveform = L"";

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "instrument")
		{
			instrument = value.bstrVal;
		}
		else if (name == "feature")
		{
			feature = value.bstrVal;
		}

		else if (name == "waveform")
		{
			waveform = value.bstrVal;
		}
	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"note")
		{
			XmlLoadNote(node, instrument, feature, waveform);
		}
	}
}

void CSynthesizer::XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument, std::wstring& feature, std::wstring& waveform)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, instrument, feature, waveform);
}

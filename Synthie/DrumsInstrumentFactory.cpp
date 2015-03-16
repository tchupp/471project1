#include "stdafx.h"
#include "DrumsInstrumentFactory.h"
#include "DrumsInstrument.h"
#include "audio/DirSoundSource.h"
#include "Note.h"


CDrumsInstrumentFactory::CDrumsInstrumentFactory()
{
}


CDrumsInstrumentFactory::~CDrumsInstrumentFactory()
{
}

void CDrumsInstrumentFactory::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (auto i = 0; i < len; i++)
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

		if (name == L"drumType")
		{
			SetDrumType(value.bstrVal);
		}
	}
}

CInstrument* CDrumsInstrumentFactory::CreateInstrument()
{
	auto instrument = new CDrumsInstrument();
	instrument->SetSamples(&mWaveL[0], &mWaveR[0], int(mWaveL.size()));

	return instrument;
}

bool CDrumsInstrumentFactory::LoadFile(const char* filename)
{
	mWaveL.clear();
	mWaveR.clear();

	CDirSoundSource mFile;
	if (!mFile.Open(filename))
	{
		CString message = L"Unable to open audio file: ";
		message += filename;
		AfxMessageBox(message);
		return false;
	}

	for (auto i = 0; i < mFile.NumSampleFrames(); ++i)
	{
		short frame[2];
		mFile.ReadFrame(frame);
		mWaveL.push_back(frame[0]);
		mWaveR.push_back(frame[1]);
	}
	mFile.Close();
	return true;
}

void CDrumsInstrumentFactory::SetDrumType(std::wstring type)
{
	if (type == L"bass")
	{
		LoadFile("wav/drums/bass.wav");
	}
	else if (type == L"cymbals")
	{
		LoadFile("wav/drums/cymbals.wav");
	}
	else if (type == L"tomshort")
	{
		LoadFile("wav/drums/tomshort.wav");
	}
	else if (type == L"tomlong")
	{
		LoadFile("wav/drums/tomlong.wav");
	}
	else if (type == L"snare")
	{
		LoadFile("wav/drums/snare.wav");
	}
}
#include "stdafx.h"
#include "DrumsInstrumentFactory.h"
#include "DrumsInstrument.h"
#include "audio/DirSoundSource.h"
#include "Note.h"
#include "ADSREnvelope.h"
#include "AmplitudeFilter.h"
#include "SineWave.h"

CDrumsInstrumentFactory::CDrumsInstrumentFactory()
{
}


CDrumsInstrumentFactory::~CDrumsInstrumentFactory()
{
}

// Setting a note
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

// Initializing and creating an instrument
CInstrument* CDrumsInstrumentFactory::CreateInstrument()
{
	auto instrument = new CDrumsInstrument();

	if (mPitchFilter)
	{
		instrument->SetPitchFilter(true);
	}
	if (mResonFilter)
	{
		instrument->SetResonFilter(true);
	}

	instrument->SetSamples(&mWaveL[0], &mWaveR[0], int(mWaveL.size()));

	return instrument;
}

// Loading wav file samples
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

	for (double i = 0; i < mFile.NumSampleFrames(); ++i)
	{
		short frame[2];
		mFile.ReadFrame(frame);
		mWaveL.push_back(frame[0]);
		mWaveR.push_back(frame[0]);
	}

	mFile.Close();
	return true;
}


void CDrumsInstrumentFactory::SetDrumType(std::wstring type)
{
	// This is the generated bass synthesis, the rest are processed from wav samples
	if (type == L"bass")
	{
		LoadBassWave();
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

	else if (type == L"sharpbass")
	{
		LoadFile("wav/drums/bass.wav");
	}

	else if (type == L"resoncymbals")
	{
		LoadFile("wav/drums/cymbals.wav");
		mResonFilter = true;
	}

	else if (type == L"resontomshort")
	{
		LoadFile("wav/drums/tomshort.wav");
		mResonFilter = true;
	}

	else if (type == L"resontomlong")
	{
		LoadFile("wav/drums/tomlong.wav");
		mResonFilter = true;
	}

	else if (type == L"resonsnare")
	{
		LoadFile("wav/drums/snare.wav");
		mResonFilter = true;
	}

	else if (type == L"resonsharpbass")
	{
		LoadFile("wav/drums/bass.wav");
		mResonFilter = true;
	}

	else if (type == L"pitchcymbals")
	{
		LoadFile("wav/drums/cymbals.wav");
		mPitchFilter = true;
	}

	else if (type == L"pitchtomshort")
	{
		LoadFile("wav/drums/tomshort.wav");
		mPitchFilter = true;
	}

	else if (type == L"pitchtomlong")
	{
		LoadFile("wav/drums/tomlong.wav");
		mPitchFilter = true;
	}

	else if (type == L"pitchsnare")
	{
		LoadFile("wav/drums/snare.wav");
		mPitchFilter = true;
	}

	else if (type == L"pitchsharpbass")
	{
		LoadFile("wav/drums/bass.wav");
		mPitchFilter = true;
	}

	else if (type == L"808clap")
	{
		LoadFile("wav/drums/808clap.wav");
	}

	else if (type == L"resonbass")
	{
		LoadBassWave();
		mResonFilter = true;
	}

	else if (type == L"pitchbass")
	{
		LoadBassWave();
		mPitchFilter = true;
	}

	else if (type == L"reson808clap")
	{
		LoadFile("wav/drums/808clap.wav");
		mResonFilter = true;
	}

	else if (type == L"pitch808clap")
	{
		LoadFile("wav/drums/808clap.wav");
		mPitchFilter = true;
	}

	else if (type == L"resonpitchbass")
	{
		LoadBassWave();
		mPitchFilter = true;
		mResonFilter = true;
	}
}

// Custom Synthesized Drum for Kick/Bass
bool CDrumsInstrumentFactory::LoadBassWave()
{
	mWaveL.clear();
	mWaveR.clear();

	CSineWave bassWave;
	bassWave.SetAmplitude(8000);
	bassWave.SetFreq(170);
	bassWave.SetSampleRate(GetSampleRate());

	CADSREnvelope envelope;
	envelope.SetDuration(3);
	envelope.SetAttack(0.05);
	envelope.SetDecay(1.0);
	envelope.SetSustainLevel(.75);
	envelope.SetRelease(3);
	envelope.SetSampleRate(GetSampleRate());

	CAmplitudeFilter amplitudeFilter;
	amplitudeFilter.SetEnvelope(&envelope);
	amplitudeFilter.SetSource(&bassWave);
	amplitudeFilter.SetSampleRate(GetSampleRate());
	amplitudeFilter.SetDuration(5);
	
	bassWave.Start();
	amplitudeFilter.Start();
	envelope.Generate();

	while (amplitudeFilter.Generate())
	{
		mWaveL.push_back(amplitudeFilter.Frame(0));
		mWaveR.push_back(amplitudeFilter.Frame(1));

		bassWave.Generate();
		envelope.Generate();
	}

	return true;
}
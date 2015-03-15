#include "stdafx.h"
#include "SubtractiveInstrument.h"
#include "Note.h"
#include "Notes.h"

double const RESONGAIN = 10;

CSubtractiveInstrument::CSubtractiveInstrument()
{
	mDuration = 0.1;
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}

void CSubtractiveInstrument::Start()
{
	//mSinewave.SetSampleRate(GetSampleRate());
	//mSinewave.Start();

	mTime = 0;
	ResonFilter();
	// Tell the AR object it gets its samples from 
	// the sine wave object.

	if (mWaveform == Sawtooth)
	{
		mSawtooth.SetSampleRate(GetSampleRate());
		mSawtooth.Start();
		mReson.SetSource(&mSawtooth);
		mADSR.SetSource(&mSawtooth);
		
	}
	else if (mWaveform == Triangle)
	{
		mTriangle.SetSampleRate(GetSampleRate());
		mTriangle.Start();
		mReson.SetSource(&mTriangle);
		mADSR.SetSource(&mTriangle);
	}
	else if (mWaveform == Square)
	{
		mSquare.SetSampleRate(GetSampleRate());
		mSquare.Start();
		mReson.SetSource(&mSquare);
		mADSR.SetSource(&mSquare);	
	}
	else
	{
		mReson.SetSource(&mSinewave);
		mADSR.SetSource(&mSinewave);
	}
	mReson.SetSampleRate(GetSampleRate());
	mReson.SetDuration(mDuration);
	mReson.Start();

	mADSR.SetSampleRate(GetSampleRate());
	mADSR.SetDuration(mDuration);
	mADSR.Start();
}

bool CSubtractiveInstrument::Generate()
{
	if (mWaveform == Sawtooth)
	{
		mSawtooth.Generate();
	}
	else if (mWaveform == Triangle)
	{
		mTriangle.Generate();
	}
	else if (mWaveform == Square)
	{
		mSquare.Generate();
	}
	else
	{
		mSinewave.Generate();
	}

	auto filterValid = mReson.Generate();
	auto valid = mADSR.Generate();

	// Read the component's sample and make it our resulting frame.
	mFrame[0] = mADSR.Frame(0);
	mFrame[1] = mADSR.Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return valid;
}

void CSubtractiveInstrument::SetNote(CNote* note, double secPerBeat)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);
	
	StringToWaveform(note->Waveform());

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

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// number of beats * seconds per beat = seconds for note
			SetDuration(value.dblVal * secPerBeat);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "resonfrequency")
		{
			value.ChangeType(VT_R8);
			mResonFrequency = value.dblVal;
		}

		else if (name == "resonbandwidth")
		{
			value.ChangeType(VT_R8);
			mResonBandwidth = value.dblVal;
		}
	}
}

void CSubtractiveInstrument::StringToWaveform(std::wstring waveform)
{
	if (waveform == L"sawtooth")
	{
		mWaveform = Sawtooth;
	}
	else if (waveform == L"triangle")
	{
		mWaveform = Triangle;
	}
	else if (waveform == L"square")
	{
		mWaveform = Square;
	}
}

void CSubtractiveInstrument::SetFreq(double f)
{
	mSinewave.SetFreq(f);
	mSawtooth.SetFreq(f);
	mTriangle.SetFreq(f);
	mSquare.SetFreq(f);
}

void CSubtractiveInstrument::SetAmplitude(double a)
{
	mSinewave.SetAmplitude(a);
	mSawtooth.SetAmplitude(a);
	mTriangle.SetAmplitude(a);
	mSquare.SetAmplitude(a);
}

void CSubtractiveInstrument::ResonFilter()
{
	mReson.SetBandwidth(mResonBandwidth);
	mReson.SetFrequency(mResonFrequency);
}


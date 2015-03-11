#include "stdafx.h"
#include "Subtractive.h"
#include "Note.h"
#include "Notes.h"

CSubtractive::CSubtractive(std::wstring feature, std::wstring waveform)
{
	mDuration = 0.1;
	stringToFeature(feature);
	stringToWaveform(waveform);
}


CSubtractive::~CSubtractive()
{
}

void CSubtractive::Start()
{
	mSinewave.SetSampleRate(GetSampleRate());
	mSinewave.Start();

	mSawtooth.SetSampleRate(GetSampleRate());
	mSawtooth.Start();

	mTriangle.SetSampleRate(GetSampleRate());
	mTriangle.Start();

	mSquare.SetSampleRate(GetSampleRate());
	mSquare.Start();

	mTime = 0;

	// Tell the AR object it gets its samples from 
	// the sine wave object.

	if (mFeature == Sawtooth)
	{
		mAR.SetSource(&mSawtooth);
	}
	else if (mFeature == Triangle)
	{
		mAR.SetSource(&mTriangle);
	}
	else if (mFeature == Square)
	{
		mAR.SetSource(&mSquare);
	}
	else
	{
		mAR.SetSource(&mSinewave);
	}
	mAR.SetSampleRate(GetSampleRate());
	mAR.SetDuration(mDuration);
	mAR.Start();
}

bool CSubtractive::Generate()
{
	if (mFeature == Sawtooth)
	{
		mSawtooth.Generate();
	}
	else if (mFeature == Triangle)
	{
		mTriangle.Generate();
	}
	else if (mFeature == Square)
	{
		mSquare.Generate();
	}
	else
	{
		mSinewave.Generate();
	}
	
	/*mSinewave.Generate();*/
	auto valid = mAR.Generate();

	// Read the component's sample and make it our resulting frame.
	mFrame[0] = mAR.Frame(0);
	mFrame[1] = mAR.Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return valid;
}

void CSubtractive::SetNote(CNote* note, double secPerBeat)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
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
	}
}

void CSubtractive::stringToWaveform(std::wstring waveform)
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

void CSubtractive::stringToFeature(std::wstring feature)
{
	if (feature == L"Reson")
	{
		mFeature = Reson;
	}
	else if (feature == L"Polyphony")
	{
		mFeature = Polyphony;
	}
	else if (feature == L"FilterEnvelope")
	{
		mFeature = FilterEnvelope;
	}
	else if (feature == L"Envelope")
	{
		mFeature = Envelope;
	}
}

void CSubtractive::SetFreq(double f)
{
	mSinewave.SetFreq(f);
	mSawtooth.SetFreq(f);
	mTriangle.SetFreq(f);
	mSquare.SetFreq(f);
}

void CSubtractive::SetAmplitude(double a)
{
	mSinewave.SetAmplitude(a);
	mSawtooth.SetAmplitude(a);
	mTriangle.SetAmplitude(a);
	mSquare.SetAmplitude(a);

}

/**
 * \file ScratchInstrument.cpp
 *
 * \author Theo Chupp
 */

#include "stdafx.h"
#include "Note.h"
#include "ScratchInstrument.h"
#include "CustomEnvelopeFactory.h"
#include "CustomEnvelope.h"


CScratchInstrument::CScratchInstrument()
{
	mDuration = 0.1;
	mType = Baby;
}


CScratchInstrument::~CScratchInstrument()
{
}

void CScratchInstrument::Start()
{
	CCustomEnvelopeFactory factory;
	switch (mType)
	{
	case Baby:
		mEnvelope = factory.CreateBabyScratchEnvelope();
		break;
	case Scribble:
		mEnvelope = factory.CreateScribbleScratchEnvelope();
		break;
	default:
		mEnvelope = new CEnvelope();
		break;
	}
	mEnvelope->SetSampleRate(GetSampleRate());

	mPitchFilter.SetEnvelope(mEnvelope);
	mAmplitudeFilter.SetEnvelope(mEnvelope);

	mTime = 0;

	mWavPlayer.SetSampleRate(GetSampleRate());

	mPitchFilter.SetSource(&mWavPlayer);
	mPitchFilter.SetSampleRate(GetSampleRate());
	mPitchFilter.SetDuration(mDuration);

	mAmplitudeFilter.SetSource(&mPitchFilter);
	mAmplitudeFilter.SetSampleRate(GetSampleRate());
	mAmplitudeFilter.SetDuration(mDuration);

	mPitchFilter.Start();
	mAmplitudeFilter.Start();
	mWavPlayer.Start();
}

bool CScratchInstrument::Generate()
{
	// Call generate on the envelope here!! Instead of in a filter
	mEnvelope->Generate();

	mPitchFilter.Generate();
	mAmplitudeFilter.Generate();

	mFrame[0] = mAmplitudeFilter.Frame(0);
	mFrame[1] = mAmplitudeFilter.Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

//! not implemented
void CScratchInstrument::SetNote(CNote* note, double secPerBeat)
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

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// number of beats * seconds per beat = seconds for note
			SetDuration(value.dblVal * secPerBeat);
		}
		else if (name == "scratch")
		{
			SetScratchType(value.bstrVal);
		}
	}
}

void CScratchInstrument::SetScratchType(std::wstring type)
{
	if (type == L"baby")
	{
		mType = Baby;
	}
	else if (type == L"scribble")
	{
		mType = Scribble;
	}
	else if (type == L"chirp")
	{
		mType = Chirp;
	}
	else if (type == L"transform")
	{
		mType = Transform;
	}
}

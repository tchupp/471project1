#include "stdafx.h"
#include "Note.h"
#include "ScratchInstrument.h"


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
	mWavPlayer.SetSampleRate(GetSampleRate());
	mWavPlayer.Start();
	mTime = 0;
}

bool CScratchInstrument::Generate()
{
	mWavPlayer.Generate();

	mFrame[0] = mWavPlayer.Frame(0);
	mFrame[1] = mWavPlayer.Frame(1);

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
		else if (name == "feature")
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
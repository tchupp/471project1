#include "stdafx.h"
#include "DrumsInstrument.h"
#include "Note.h"
#include "Envelope.h"


CDrumsInstrument::CDrumsInstrument()
{
	mDuration = 0.25;
}


CDrumsInstrument::~CDrumsInstrument()
{
}


void CDrumsInstrument::Start()
{
	mWavPlayer.SetSampleRate(GetSampleRate());
	mWavPlayer.Start();
	mTime = 0;
	mEnvelope = new CADSREnvelope();
}

bool CDrumsInstrument::Generate()
{
	// Call generate on the envelope here!! Instead of in a filter
	mEnvelope->Generate();

	mWavPlayer.Generate();

	mFrame[0] = mWavPlayer.Frame(0);
	mFrame[1] = mWavPlayer.Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

//! not implemented
void CDrumsInstrument::SetNote(CNote* note, double secPerBeat)
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
	}
}

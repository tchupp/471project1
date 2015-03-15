#include "stdafx.h"
#include "ChorusEffect.h"
#include "Note.h"


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Process(double* input, double* output)
{
}

void CChorusEffect::Start()
{
}

bool CChorusEffect::Generate()
{
	return false;
}

void CChorusEffect::SetNote(CNote *note, double secPerBeat)
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

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "wet")
		{
			value.ChangeType(VT_R8);
			SetWet(value.dblVal);
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			SetDry(value.dblVal);
		}
		else if (name == "delay")
		{
			value.ChangeType(VT_R8);
			SetDelay(value.dblVal);
		}

		//TODO(jordan)   Other attributes relevant to Chorus
	}

}
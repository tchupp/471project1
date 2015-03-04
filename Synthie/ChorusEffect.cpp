#include "stdafx.h"
#include "ChorusEffect.h"


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Process(double* input, double* output)
{
}

void CChorusEffect::XmlLoad(IXMLDOMNode* xml)
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

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "delay")
		{
			value.ChangeType(VT_R8);
			mDelay = value.dblVal;
		}
		else if (name == "wet")
		{
			value.ChangeType(VT_R8);
			mWet = value.dblVal;
			
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			mDry = value.dblVal;
		}
		else if (name == "rate")
		{
			value.ChangeType(VT_R8);
			mRate = value.dblVal;
		}
		else if (name == "range")
		{
			value.ChangeType(VT_R8);
			mRange = value.dblVal;
		}
	}
}
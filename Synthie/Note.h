#pragma once
#include <string>

class CNote
{
public:
	CNote();
	~CNote();

	int Measure() const { return mMeasure; }

	double Beat() const { return mBeat; }

	const std::wstring& Instrument() const { return mInstrument; }

	IXMLDOMNode* Node() { return mNode; }

	void XmlLoad(IXMLDOMNode* xml, std::wstring& instrument);

	bool operator<(const CNote& b);

private:
	std::wstring mInstrument;
	int mMeasure;
	double mBeat;
	CComPtr<IXMLDOMNode> mNode;
};

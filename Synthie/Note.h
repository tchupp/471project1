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
	const std::wstring& Feature() const { return mFeature; }
	const std::wstring& Waveform() const { return mWaveform; }

	IXMLDOMNode* Node() { return mNode; }

	void XmlLoad(IXMLDOMNode* xml, std::wstring& instrument, std::wstring& feature, std::wstring& waveform);

	bool operator<(const CNote& b);

private:
	std::wstring mInstrument;
	std::wstring mFeature;
	std::wstring mWaveform;
	int mMeasure;
	double mBeat;
	CComPtr<IXMLDOMNode> mNode;
};

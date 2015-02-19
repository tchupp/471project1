#pragma once

#include <list>
#include <vector>

class CNote;
class CInstrument;

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();

	//! Number of audio channels
	int GetNumChannels() { return mChannels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return mSampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return mSamplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { mChannels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { mSampleRate = s; mSamplePeriod = 1.0 / s; }

	void Start();
	void Clear();

	bool Generate(double* frame);

	//! Get the time since we started generating audio
	double GetTime() { return mTime; }

	void OpenScore(CString& filename);

private:
	int mChannels;
	double mSampleRate;
	double mSamplePeriod;
	double mTime;
	std::list<CInstrument *> mInstruments;
	std::vector<CNote> m_notes;

	double mBpm; //!< Beats per minute
	int mBeatsPerMeasure; //!< Beats per measure
	double mSecPerBeat; //!< Seconds per beat

	void XmlLoadScore(IXMLDOMNode* xml);
	void XmlLoadInstrument(IXMLDOMNode* xml);
	void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);

	int mCurrentNote; //!< The current note we are playing
	int mMeasure; //!< The current measure
	double mBeat; //!< The current beat within the measure
};

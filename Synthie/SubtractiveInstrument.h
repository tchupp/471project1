#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "TriangleWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include "ADSR.h"
#include <vector>

class CSubtractiveInstrument : public CInstrument
{
public:
	CSubtractiveInstrument(std::wstring feature, std::wstring waveform);
	virtual ~CSubtractiveInstrument();
	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note, double secPerBeat) override;

	void SetFreq(double f);
	void SetAmplitude(double a);

	void SetDuration(double d) { mDuration = d; }

	void ProcessFilter();
	void ResonFilter();

	enum Waveform { Sawtooth, Triangle, Square };

	enum Feature { Reson, Polyphony, FilterEnvelope, Envelope };

private:
	CSineWave mSinewave;
	CSawtoothWave mSawtooth;
	CTriangleWave mTriangle;
	CSquareWave mSquare;
	double mDuration;
	double mTime;
	CADSR mADSR;
	Feature mFeature;
	Waveform mWaveform;

	void StringToWaveform(std::wstring waveform);
	void StringToFeature(std::wstring feature);

	struct FilterTerm
	{
		int m_delay;
		double m_weight;
	};

	std::vector<FilterTerm> mFilterXTerms;
	std::vector<FilterTerm> mFilterYTerms;

	int mNumXFilters;
	int mNumYFilters;
};

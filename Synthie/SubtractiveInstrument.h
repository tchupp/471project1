#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "TriangleWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include "ResonFilter.h"
#include <vector>

class CSubtractiveInstrument : public CInstrument
{
public:
	CSubtractiveInstrument();
	virtual ~CSubtractiveInstrument();
	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note, double secPerBeat) override;

	void SetFreq(double f);
	void SetAmplitude(double a);
	void SetDuration(double d) { mDuration = d; }

	void ResonFilterSetup();

	enum Waveform { Sawtooth, Triangle, Square };

private:
	CSineWave mSinewave;
	CSawtoothWave mSawtooth;
	CTriangleWave mTriangle;
	CSquareWave mSquare;

	double mResonFrequency;
	double mResonBandwidth;

	double mDuration;
	double mTime;
	
	CResonFilter mReson;
	Waveform mWaveform;

	void StringToWaveform(std::wstring waveform);

	bool mResonFilter;

};

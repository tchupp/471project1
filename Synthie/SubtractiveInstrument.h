#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "TriangleWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include "ADSR.h"
#include <vector>
#include "ResonFilter.h"
#include "BaseWave.h"
#include "AmplitudeFilter.h"

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
	CADSR mADSR;
	
	CAmplitudeFilter mAmplitudeFilter;

	CResonFilter mReson;
	Waveform mWaveform;

	void StringToWaveform(std::wstring waveform);

	bool mResonFilter;

};

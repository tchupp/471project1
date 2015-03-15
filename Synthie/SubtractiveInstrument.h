#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "Triangle.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include "ADSR.h"

class CSubtractiveInstrument : public CInstrument
{
public:
	CSubtractiveInstrument(std::wstring feature, std::wstring waveform);
	virtual ~CSubtractiveInstrument();
	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note, double secPerBeat) override;

	void SetFreq(double f);
	void SetAmplitude(double a);
	void SetDuration(double d) { mDuration = d; }

	enum Waveform { Sawtooth, Triangle, Square };
	enum Feature { Reson, Polyphony, FilterEnvelope, Envelope };

	void stringToWaveform(std::wstring waveform);
	void stringToFeature(std::wstring feature);

private:
	CSineWave mSinewave;
	CSawtoothWave mSawtooth;
	CTriangle mTriangle;
	CSquareWave mSquare;
	double mDuration;
	double mTime;
	CADSR mADSR;
	Feature mFeature;
	Waveform mWaveform;

	
};

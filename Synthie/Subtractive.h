#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "AR.h"
#include <string>

class CSubtractive : public CInstrument
{
public:
	CSubtractive(std::wstring feature, std::wstring waveform);
	virtual ~CSubtractive();
	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note, double secPerBeat) override;

	void SetFreq(double f) { mSinewave.SetFreq(f); }
	void SetAmplitude(double a) { mSinewave.SetAmplitude(a); }
	void SetDuration(double d) { mDuration = d; }

	enum Waveform { Sawtooth, Triangle, Square };
	enum Feature { Reson, Polyphony, FilterEnvelope, Envelope };

	void stringToWaveform(std::wstring waveform);
	void stringToFeature(std::wstring feature);

	bool GenerateSawtooth();
	bool GenerateTriangle();
	bool GenerateSquare();

private:
	CSineWave mSinewave;
	double mDuration;
	double mTime;
	CAR mAR;
	Feature mFeature;
	Waveform mWaveform;
	double mPhase;
};

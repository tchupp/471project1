#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "ADSR.h"

class CToneInstrument :
	public CInstrument
{
public:
	CToneInstrument();
	virtual ~CToneInstrument();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note, double secPerBeat) override;

	void SetFreq(double f) { mSinewave.SetFreq(f); }

	void SetAmplitude(double a) { mSinewave.SetAmplitude(a); }

	void SetDuration(double d) { mDuration = d; }

private:
	CSineWave mSinewave;
	double mDuration;
	double mTime;
	CADSR mADSR;
};

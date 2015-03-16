#pragma once
#include "Instrument.h"
#include "CustomWave.h"
#include "ADSR.h"

using namespace std;

class CAdditiveInstrument :
	public CInstrument
{
public:
	CAdditiveInstrument();
	virtual ~CAdditiveInstrument();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note, double secPerBeat) override;

	void SetFreq(double f) { mHarmonicsWave.SetFreq(f); }

	void SetAmplitude(double a) { mHarmonicsWave.SetAmplitude(a); }

	void SetDuration(double d) { mDuration = d; }

	void AddHarmonics(std::wstring harmonics);

private:
	double mDuration;
	double mTime;

	// The attack-delay-sustain-release object
	CADSR mADSR;
	
	CCustomWave mHarmonicsWave;
};

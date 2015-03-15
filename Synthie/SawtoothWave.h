#pragma once

#include "AudioNode.h"
#include <vector>

class CSawtoothWave : public CAudioNode
{
public:
	CSawtoothWave();
	virtual ~CSawtoothWave();

	//! Start audio generation
	virtual void Start() override;

	//! Generate one frame of audio
	virtual bool Generate() override;

	//! Set the sine wave frequency
	void SetFreq(double f) { mFreq = f; }

	double GetFreq() { return mFreq; }
	double GetAmp() { return mAmp; }
	double GetPhase() { return mPhase; }

	//! Set the sine wave amplitude
	void SetAmplitude(double a) { mAmp = a; }

	void SetWavetables();

private:
	double mFreq;
	double mAmp;
	int mPhase;
	std::vector<double> mWavetable;
};


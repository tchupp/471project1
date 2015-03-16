#pragma once
#include "AudioNode.h"
#include <vector>
class BaseWave : public CAudioNode
{
public:
	BaseWave();
	virtual ~BaseWave();

	//! Start audio generation
	virtual void Start() override = 0;
	//! Generate one frame of audio
	virtual bool Generate() override = 0;
	//! Sets wavetables per wave
	void SetWavetables();

	void SetFreq(double f) { mFreq = f; }
	//! Set the sine wave amplitude
	void SetAmplitude(double a) { mAmp = a; }

	double GetFreq() { return mFreq; }
	double GetAmp() { return mAmp; }
	double GetPhase() { return mPhase; }
	bool GetIfFilter() { return mFilter; }
	double GetWavetableSize() { return mWavetable.size(); }

protected:
	double mFreq;
	double mAmp;
	int mPhase;
	bool mFilter;
	std::vector<double> mWavetable;
};


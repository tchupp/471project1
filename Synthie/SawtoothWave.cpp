#include "stdafx.h"
#include "SawtoothWave.h"

#include <cmath>

using namespace std;

CSawtoothWave::CSawtoothWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}


CSawtoothWave::~CSawtoothWave()
{
}

void CSawtoothWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CSawtoothWave::Generate()
{
	mFrame[0] = mWavetable[mPhase];
	mFrame[1] = mFrame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CSawtoothWave::SetWavetables()
{
	mWavetable.resize(GetSampleRate());
	double time = 0;

	for (int i = 0; i < (GetSampleRate()); i++, time += 1. / GetSampleRate())
	{
		short sawtoothSample = 0;
		int nyquist = GetSampleRate() / 2;
		int harm = 1;

		while (mFreq * harm < nyquist)
		{
			sawtoothSample += RangeBound(mAmp / harm * sin(time * 2 * PI * mFreq * harm));
			harm += 1;
		}
		mWavetable[i] = RangeBound(sawtoothSample);
	}
}

short CSawtoothWave::RangeBound(double sample)
{
	if (sample > 32767)
	{
		return 32767;
	}
	else if (sample < -32768)
	{
		return -32768;
	}

	return short(sample);
}

#include "stdafx.h"
#include "SquareWave.h"

#include <cmath>

using namespace std;

CSquareWave::CSquareWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CSquareWave::~CSquareWave()
{
}

void CSquareWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CSquareWave::Generate()
{
	mFrame[0] = mWavetable[mPhase];
	mFrame[1] = mFrame[0];

	mPhase = (mPhase+1) % mWavetable.size();

	return true;
}

void CSquareWave::SetWavetables()
{
	mWavetable.resize(GetSampleRate());
	double time = 0.;
	auto sr = GetSampleRate();

	for (int i = 0; i < sr; i++, time += 1. / sr)
	{
		double squareSample = 0;
		int nyquist = GetSampleRate() / 2;
		int harm = 1;

		while (mFreq * harm < nyquist)
		{
			squareSample += RangeBound(mAmp / harm * sin(time * 2 * PI * mFreq * harm));
			harm += 2;
		}
		mWavetable[i] =	RangeBound(squareSample);
		auto hello = true;
	}
}

short CSquareWave::RangeBound(double sample)
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


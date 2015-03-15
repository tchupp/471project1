#include "stdafx.h"
#include "SquareWave.h"

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

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CSquareWave::SetWavetables()
{
	mWavetable.resize(GetSampleRate());
	auto time = 0.;

	for (auto i = 0; i < GetSampleRate(); i++ , time += 1. / GetSampleRate())
	{
		auto squareSample = 0.;
		int nyquist = GetSampleRate() / 2;
		auto harm = 1.;

		while (mFreq * harm < nyquist)
		{
			squareSample += mAmp / harm * sin(time * 2 * PI * mFreq * harm);
			harm += 2;
		}
		mWavetable[i] = squareSample;
	}
}

#include "stdafx.h"
#include "SineWave.h"

using namespace std;

CSineWave::CSineWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CSineWave::~CSineWave()
{
}

void CSineWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CSineWave::Generate()
{
	mFrame[0] = mWavetable[mPhase];
	mFrame[1] = mFrame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CSineWave::SetWavetables()
{
	mWavetable.resize(GetSampleRate());
	auto time = 0.;

	for (auto i = 0; i < GetSampleRate(); i++ , time += 1. / GetSampleRate())
	{
		auto sineSample = mAmp * sin(time * 2 * PI * mFreq);
		mWavetable[i] = sineSample;
	}
}

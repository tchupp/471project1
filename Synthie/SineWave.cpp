#include "stdafx.h"
#include "SineWave.h"


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
}

bool CSineWave::Generate()
{
	mFrame[0] = mAmp * sin(mPhase * 2 * PI);
	mFrame[1] = mFrame[0];

	mPhase += mFreq * GetSamplePeriod();

	return true;
}
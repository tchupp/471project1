#include "stdafx.h"
#include "SawtoothWave.h"


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
}

bool CSawtoothWave::Generate()
{
	mFrame[0] = mAmp * sin(mPhase * 2 * PI);
	mFrame[1] = mFrame[0];

	mPhase += mFreq * GetSamplePeriod();

	return true;
}
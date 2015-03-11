#include "stdafx.h"
#include "SquareWave.h"


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
}

bool CSquareWave::Generate()
{
	mFrame[0] = mAmp * sin(mPhase * 2 * PI);
	mFrame[1] = mFrame[0];

	mPhase += mFreq * GetSamplePeriod();

	return true;
}
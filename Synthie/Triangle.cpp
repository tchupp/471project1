#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}


CTriangle::~CTriangle()
{
}

void CTriangle::Start()
{
	mPhase = 0;
}

bool CTriangle::Generate()
{
	mFrame[0] = mAmp * sin(mPhase * 2 * PI);
	mFrame[1] = mFrame[0];

	mPhase += mFreq * GetSamplePeriod();

	return true;
}

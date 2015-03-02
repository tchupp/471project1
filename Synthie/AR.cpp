#include "stdafx.h"
#include "AR.h"


CAR::CAR()
{
	mAttack = 0.05;
	mRelease = 0.05;
}


CAR::~CAR()
{
}

void CAR::Start()
{
	mTime = 0;
}

bool CAR::Generate()
{
	// percentage for the ramp
	double fac = 1;
	if (mTime < mAttack)
	{
		fac = mTime / mAttack;
	}
	else if (mTime > mDuration - mRelease)
	{
		fac = 1 - (mTime - (mDuration - mRelease)) / mRelease;
	}
	mFrame[0] = fac * mSource->Frame(0);
	mFrame[1] = fac * mSource->Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return mTime < mDuration;
}
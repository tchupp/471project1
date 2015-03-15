#include "stdafx.h"
#include "ADSR.h"


CADSR::CADSR()
{
	mAttack = 0.05;
	mDecay = 0.;
	mSustainLevel = 1.;
	mRelease = 0.05;
}


CADSR::~CADSR()
{
}

void CADSR::Start()
{
	mTime = 0;
}

bool CADSR::Generate()
{
	mSource->Generate();
	// percentage for the ramp
	double fac;

	if (mTime <= mAttack) // attack
	{
		fac = mTime / mAttack;
	}
	else if (mTime > mDuration - mRelease) // release
	{
		fac = 1 - (mTime - (mDuration - mRelease)) / mRelease;
	}
	else if (mTime > mAttack && mTime <= mAttack + mDecay) // decay
	{
		fac = (mSustainLevel - 1) * ((mTime - (mDuration - mDecay)) / mDecay) + 1;
	}
	else // sustain
	{
		fac = mSustainLevel;
	}
	mFrame[0] = fac * mSource->Frame(0);
	mFrame[1] = fac * mSource->Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return mTime < mDuration;
}

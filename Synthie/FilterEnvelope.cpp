#include "stdafx.h"
#include "FilterEnvelope.h"


CFilterEnvelope::CFilterEnvelope()
{
	mAttack = 0.05;
	mDecay = 0.;
	mSustainLevel = 1.;
	mRelease = 0.05;
}


CFilterEnvelope::~CFilterEnvelope()
{
}

void CFilterEnvelope::Start()
{
	mEnvelopeLevel = 1;
	mTime = 0;
}

bool CFilterEnvelope::Generate()
{
	if (mTime <= mAttack) // attack
	{
		mEnvelopeLevel = mTime / mAttack;
	}
	else if (mTime > mDuration - mRelease) // release
	{
		mEnvelopeLevel = 1 - (mTime - (mDuration - mRelease)) / mRelease;
	}
	else if (mTime > mAttack && mTime <= mAttack + mDecay) // decay
	{
		mEnvelopeLevel = (mSustainLevel - 1) * ((mTime - (mDuration - mDecay)) / mDecay) + 1;
	}
	else // sustain
	{
		mEnvelopeLevel = mSustainLevel;
	}

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}
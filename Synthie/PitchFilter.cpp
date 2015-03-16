#include "stdafx.h"
#include "PitchFilter.h"


CPitchFilter::CPitchFilter()
{
	mEnvelope.SetAttack(0.);
	mEnvelope.SetRelease(0.);
}


CPitchFilter::~CPitchFilter()
{
}


void CPitchFilter::Start()
{
	mTime = 0;

	mEnvelope.SetDuration(mDuration);
	mEnvelope.Start();
}


bool CPitchFilter::Generate()
{
	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

#include "stdafx.h"
#include "AmplitudeFilter.h"


CAmplitudeFilter::CAmplitudeFilter()
{
	mEnvelope.SetAttack(0.);
	mEnvelope.SetRelease(0.);
}


CAmplitudeFilter::~CAmplitudeFilter()
{
}


void CAmplitudeFilter::Start()
{
	mTime = 0;

	mEnvelope.SetDuration(mDuration);
	mEnvelope.Start();
}


bool CAmplitudeFilter::Generate()
{
	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

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
	mEnvelope.SetSampleRate(GetSampleRate());
	mEnvelope.Start();
}


bool CAmplitudeFilter::Generate()
{
	mEnvelope.Generate();
	auto amplitudeFactor = mEnvelope.GetEnvelopeLevel();

	mFrame[0] = amplitudeFactor * mSource->Frame(0);
	mFrame[1] = amplitudeFactor * mSource->Frame(1);

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

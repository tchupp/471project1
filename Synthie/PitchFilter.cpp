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
	mPosition = 0;
	mSampleNum = 0;

	mEnvelope.SetDuration(mDuration);
	mEnvelope.SetSampleRate(GetSampleRate());
	mEnvelope.Start();

	mSource->Start();
	auto valid = mSource->Generate();
	while (valid)
	{
		mQueueL.push_back(mSource->Frame(0));
		mQueueR.push_back(mSource->Frame(1));
		valid = mSource->Generate();
	}
}


bool CPitchFilter::Generate()
{
	mSampleNum = int(mPosition + 0.5) % mQueueL.size();

	mFrame[0] = mQueueL[mSampleNum];
	mFrame[1] = mQueueR[mSampleNum];

	mEnvelope.Generate();
	mPosition += mEnvelope.GetEnvelopeLevel();

	if (mSampleNum < 0) mPosition = mQueueL.size();

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

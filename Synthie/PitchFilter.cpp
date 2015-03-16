#include "stdafx.h"
#include "PitchFilter.h"
#include "Envelope.h"


CPitchFilter::CPitchFilter()
{
}


CPitchFilter::~CPitchFilter()
{
}


void CPitchFilter::Start()
{
	mTime = 0;
	mPosition = 0;
	mSampleNum = 0;

	// Make sure you do this!
	mEnvelope->SetDuration(mDuration);
	mEnvelope->SetSampleRate(GetSampleRate());
	mEnvelope->Start();

	mSource->Start();
	auto valid = mSource->Generate();
	for (auto time = 0.; time < mDuration; time += GetSamplePeriod())
	{
		mQueueL.push_back(mSource->Frame(0));
		mQueueR.push_back(mSource->Frame(1));
		valid = mSource->Generate();
	}
}


bool CPitchFilter::Generate()
{
	// No need to generate mEnvelope anymore!!
	mSampleNum = int(mPosition + 0.5) % mQueueL.size();

	mFrame[0] = mQueueL[mSampleNum];
	mFrame[1] = mQueueR[mSampleNum];

	mPosition += mEnvelope->GetEnvelopeLevel();

	if (mSampleNum < 0) mPosition = mQueueL.size();

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

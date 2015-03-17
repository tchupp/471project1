/**
 * \file AmplitudeFilter.cpp
 *
 * \author Theo Chupp
 */

#include "stdafx.h"
#include "AmplitudeFilter.h"
#include "Envelope.h"


CAmplitudeFilter::CAmplitudeFilter()
{
}


CAmplitudeFilter::~CAmplitudeFilter()
{
}


void CAmplitudeFilter::Start()
{
	mTime = 0;
	// Make sure you do this!
	mEnvelope->SetDuration(mDuration);
	mEnvelope->SetSampleRate(GetSampleRate());
	mEnvelope->Start();
}


bool CAmplitudeFilter::Generate()
{
	// No need to generate mEnvelope anymore!!
	auto amplitudeFactor = mEnvelope->GetEnvelopeLevel();

	mFrame[0] = amplitudeFactor * mSource->Frame(0);
	mFrame[1] = amplitudeFactor * mSource->Frame(1);

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

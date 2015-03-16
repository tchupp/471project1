/**
 * \file CustomEnvelope.cpp
 *
 * \author Su Adanali
 */

#include "stdafx.h"
#include "CustomEnvelope.h"
#include <algorithm>

using namespace std;

CCustomEnvelope::CCustomEnvelope()
{
}


CCustomEnvelope::~CCustomEnvelope()
{
}

void CCustomEnvelope::AddPoint(double time, double level)
{
	EnvelopePoint point;
	point.mTime = time;
	point.mLevel = level;
	mEnvelopePoints.push_back(point);
}

void CCustomEnvelope::Start()
{
	sort(mEnvelopePoints.begin(), mEnvelopePoints.end());
}

bool CCustomEnvelope::Generate()
{
	mTime = 0.2;
	SetEnvelopePoints();
	mEnvelopeLevel = GenerateLevelValue();
	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

double CCustomEnvelope::GenerateLevelValue()
{
	double yLevelValue;

	yLevelValue = (mPreviousEnvelopePoint.mLevel - mNextEnvelopePoint.mLevel) 
			/ (mPreviousEnvelopePoint.mTime - mNextEnvelopePoint.mTime)
				* (mTime - mPreviousEnvelopePoint.mTime) + mPreviousEnvelopePoint.mLevel;

	return yLevelValue;
}

void CCustomEnvelope::SetEnvelopePoints()
{
	auto index = 0;
	for (auto point : mEnvelopePoints)
	{
		///future add a check to see if this is the end of the vector
		if (mTime > point.mTime)
		{
			mPreviousEnvelopePoint = point;
			mNextEnvelopePoint = mEnvelopePoints[index + 1];
			return;
		}
		index++;
	}

}
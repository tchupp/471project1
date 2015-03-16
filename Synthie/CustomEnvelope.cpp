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
	mEnvelopeLevel = 1;
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
	mTime = 0;
}

bool CCustomEnvelope::Generate()
{
	SetEnvelopePoints();
	mEnvelopeLevel = GenerateLevelValue();

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}

double CCustomEnvelope::GenerateLevelValue()
{
	auto yLevelValue = (mPrevPoint.mLevel - mNextPoint.mLevel)
		/ (mPrevPoint.mTime - mNextPoint.mTime)
		* (mTime - mPrevPoint.mTime) + mPrevPoint.mLevel;

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
			mPrevPoint = point;
			mNextPoint = mEnvelopePoints[index + 1];
			return;
		}
		index++;
	}
}

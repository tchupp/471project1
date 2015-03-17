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
	if (mEnvelopePoints.size())
	{
		if (mTime < mEnvelopePoints[0].mTime)
		{
			mEnvelopeLevel = mEnvelopePoints[0].mLevel / mEnvelopePoints[0].mTime * mTime;
		}

		else if (mEnvelopePoints[0].mTime < mTime < mEnvelopePoints[mEnvelopePoints.size() - 1].mTime)
		{
			SetEnvelopePoints();
			mEnvelopeLevel = GenerateLevelValue();
		}
		else
		{
			mEnvelopeLevel = -1 * mEnvelopePoints[mEnvelopePoints.size() - 1].mLevel / (mDuration - mEnvelopePoints[mEnvelopePoints.size() - 1].mTime) * mTime;
		}
	}
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
		if (point.mTime > mTime)
		{
			mNextPoint = point;
			mPrevPoint = mEnvelopePoints[index - 1];
			return;
		}
		index++;
	}
}

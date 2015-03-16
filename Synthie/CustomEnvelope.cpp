/**
 * \file CustomEnvelope.cpp
 *
 * \author Su Adanali
 */

#include "stdafx.h"
#include "CustomEnvelope.h"


CCustomEnvelope::CCustomEnvelope()
{
}


CCustomEnvelope::~CCustomEnvelope()
{
}

void CCustomEnvelope::SetPoint(double level, double time)
{
	EnvelopePoint point;
	point.mLevel = level;
	point.mTime = time;

	mEnvelopePoints.push_back(point);
}

void CCustomEnvelope::Start()
{

}

bool CCustomEnvelope::Generate()
{
	return true;
}

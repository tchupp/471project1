#include "stdafx.h"
#include "FilterEnvelope.h"


CFilterEnvelope::CFilterEnvelope()
{
	mAttack = 0.05;
	mDecay = 0.;
	mSustainLevel = 1.;
	mRelease = 0.05;
}


CFilterEnvelope::~CFilterEnvelope()
{
}

void CFilterEnvelope::Start()
{
	mEnvelopeLevel = 1;
}

bool CFilterEnvelope::Generate()
{
	return true;
}
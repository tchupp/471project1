#include "stdafx.h"
#include "NoiseGateEffect.h"


CNoiseGateEffect::CNoiseGateEffect()
{
}


CNoiseGateEffect::~CNoiseGateEffect()
{
}

void CNoiseGateEffect::Process(double *input, double *output, double time)
{

}

void CNoiseGateEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CNoiseGateEffect::Generate()
{
	return true;
}

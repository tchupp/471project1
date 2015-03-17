#include "stdafx.h"
#include "ReverbEffect.h"


CReverbEffect::CReverbEffect()
{
}


CReverbEffect::~CReverbEffect()
{
}

void CReverbEffect::Process(double *input, double *output)
{

}

void CReverbEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CReverbEffect::Generate()
{
	return true;
}

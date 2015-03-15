#include "stdafx.h"
#include "ChorusEffect.h"


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Process(double* input, double* output)
{
	for (int i = 0; i < 2; i++)
	{
		mQueue[mWrloc + i] = input[i];
		output[i] = mDry * input[i] + mWet * mQueue[mRdloc + i];
	}

	// In progres...
}

void CChorusEffect::Start()
{
}

bool CChorusEffect::Generate()
{
	return false;
}
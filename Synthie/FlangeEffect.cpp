#include "stdafx.h"
#include "FlangeEffect.h"


CFlangeEffect::CFlangeEffect()
{
}


CFlangeEffect::~CFlangeEffect()
{
}

void CFlangeEffect::Process(double *input, double *output)
{
	for (int i = 0; i < 2; i++)
	{
		mQueue[mWrloc + i] = input[i];
		output[i] = mDry * input[i] + mWet * mQueue[mRdloc + i];
	}

	// In progress..
}

void CFlangeEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CFlangeEffect::Generate()
{
	return true;
}
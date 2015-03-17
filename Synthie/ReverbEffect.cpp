#include "stdafx.h"
#include "ReverbEffect.h"

const int MAXQUEUESIZE = 200000;

CReverbEffect::CReverbEffect()
{
}


CReverbEffect::~CReverbEffect()
{
}

void CReverbEffect::Process(double *input, double *output, double time)
{
	for (int c = 0; c<2; c++)
	{
		mQueue[mWrloc + c] = input[c];
		output[c] = mDry * input[c] + mWet * mQueue[mRdloc + c];
	}


	mWrloc = (mWrloc + 2) % MAXQUEUESIZE;
	mRdloc = (mRdloc + 2) % MAXQUEUESIZE;

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

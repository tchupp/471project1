#include "stdafx.h"
#include "ChorusEffect.h"

const int MAXQUEUESIZE = 200000;
const double M_PI = 3.14159265359;

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
		output[i] = mDry * input[i] + mWet * mQueue[(mRdloc + i) % MAXQUEUESIZE];
	}

	double chorus = 0.025 + sin(0.25 * 2 * M_PI) * 0.004;

	int delaylength = int((chorus * GetSampleRate() + 0.5) + 2);

	mWrloc = (mWrloc + 2) % MAXQUEUESIZE;
	mRdloc = (mWrloc + MAXQUEUESIZE - delaylength) % MAXQUEUESIZE;

}

void CChorusEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CChorusEffect::Generate()
{
	return true;
}
#include "stdafx.h"
#include "FlangeEffect.h"

const int MAXQUEUESIZE = 200000;
const double M_PI = 3.14159265359;

CFlangeEffect::CFlangeEffect()
{
}


CFlangeEffect::~CFlangeEffect()
{
}

void CFlangeEffect::Process(double *input, double *output, double time)
{
	for (int i = 0; i < 2; i++)
	{
		mQueue[mWrloc + i] = input[i];
		output[i] = mDry * input[i] + mWet * mQueue[mRdloc + i];
	}

	double flange = 0.006 + sin(0.25 * 2 * M_PI * time) * 0.004;

	int delaylength = int((flange*GetSampleRate() + 0.5) * 2);

	mWrloc = (mWrloc + 2) % MAXQUEUESIZE;
	mRdloc = (mWrloc + MAXQUEUESIZE - delaylength) % MAXQUEUESIZE;
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
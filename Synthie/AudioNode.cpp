#include "stdafx.h"
#include "AudioNode.h"


CAudioNode::CAudioNode()
{
	mFrame[0] = 0;
	mFrame[1] = 0;
	mSampleRate = 44100;
	mSamplePeriod = 1. / 44100.;
}


CAudioNode::~CAudioNode()
{
}

#include "stdafx.h"
#include "WavFilePlayer.h"


CWavFilePlayer::CWavFilePlayer()
{
	mNumSamples = 0;
	mSamplesLeft = nullptr;
	mSamplesRight = nullptr;
}


CWavFilePlayer::~CWavFilePlayer()
{
}

void CWavFilePlayer::Start()
{
	mPosition = 0;
}

bool CWavFilePlayer::Generate()
{
	if (mPosition < mNumSamples)
	{
		mFrame[0] = mSamplesLeft[mPosition] / 32768.;
		mFrame[1] = mSamplesRight[mPosition++] / 32768.;
		return true;
	}
	mFrame[1] = mFrame[0] = 0;
	return false;
}

void CWavFilePlayer::SetSamples(short* sL, short* sR, int n)
{
	mSamplesLeft = sL;
	mSamplesRight = sR;
	mNumSamples = n;
}
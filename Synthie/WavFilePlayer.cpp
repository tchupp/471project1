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
	mSampleNumber = 0;
	mSpeed = 1;
}

bool CWavFilePlayer::Generate()
{
	mFrame[0] = mSamplesLeft[mPosition] / 32768.;
	mFrame[1] = mSamplesRight[mPosition] / 32768.;

	mSampleNumber += mSpeed;
	mPosition = int(mSampleNumber + 0.5) % mNumSamples;
	if (mPosition < 0) mSampleNumber = mNumSamples;

	return true;
}

void CWavFilePlayer::SetSamples(short* sL, short* sR, int n)
{
	mSamplesLeft = sL;
	mSamplesRight = sR;
	mNumSamples = n;
}

#pragma once
#include "AudioNode.h"
class CWavFilePlayer :
	public CAudioNode
{
public:
	CWavFilePlayer();
	virtual ~CWavFilePlayer();

	virtual void Start() override;
	virtual bool Generate() override;

	void SetSamples(short* sL, short* sR, int n);

private:
	short* mSamplesLeft;
	short* mSamplesRight;
	int mNumSamples;
	int mPosition;
};


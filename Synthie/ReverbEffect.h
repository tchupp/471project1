#pragma once
#include "AudioEffect.h"
class CReverbEffect :
	public CAudioEffect
{
public:
	CReverbEffect();
	virtual ~CReverbEffect();

	virtual void Process(double *input, double *output, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;
};


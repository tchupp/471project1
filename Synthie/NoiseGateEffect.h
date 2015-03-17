#pragma once
#include "AudioEffect.h"
class CNoiseGateEffect :
	public CAudioEffect
{
public:
	CNoiseGateEffect();
	virtual ~CNoiseGateEffect();

	virtual void Process(double *input, double *output, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;
};


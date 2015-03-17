#pragma once
#include "AudioEffect.h"

class CChorusEffect :
	public CAudioEffect
{
public:
	CChorusEffect();
	virtual ~CChorusEffect();

	virtual void Process(double *input, double *output, double time) override;
	
	virtual void Start() override;

	virtual bool Generate() override;
};


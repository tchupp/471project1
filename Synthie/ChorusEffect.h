#pragma once
#include "AudioEffect.h"

class CChorusEffect :
	public CAudioEffect
{
public:
	CChorusEffect();
	virtual ~CChorusEffect();

	virtual void Process(double *input, double *output) override;
	
	virtual void Start() override;

	virtual bool Generate() override;

private:
	//! The speed the delay is varied
	double	mRate;
	//! The amplitude of the delay variation
	double	mRange;
};


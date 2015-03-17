#pragma once
#include "AudioEffect.h"

class CFlangeEffect :
	public CAudioEffect
{
public:
	CFlangeEffect();
	virtual ~CFlangeEffect();

	virtual void Process(double *input, double *output, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;

};


#pragma once
#include "Filter.h"

class CAmplitudeFilter : public CFilter
{
public:
	CAmplitudeFilter();
	virtual ~CAmplitudeFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;
};

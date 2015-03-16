#pragma once
#include "Filter.h"

class CPitchFilter : public CFilter
{
public:
	CPitchFilter();
	virtual ~CPitchFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;
};

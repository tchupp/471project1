#pragma once
#include "Filter.h"
#include <vector>

class CPitchFilter : public CFilter
{
public:
	CPitchFilter();
	virtual ~CPitchFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

private:
	//! actual position of the queue
	double mPosition;
	//! rounded position of the queue
	int mSampleNum;

	std::vector<double> mQueueL;
	std::vector<double> mQueueR;
};

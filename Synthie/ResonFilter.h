#pragma once
#include "AudioNode.h"
#include <vector>

class CResonFilter : public CAudioNode
{
public:
	CResonFilter();
	virtual ~CResonFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }
	void SetDuration(double duration) { mDuration = duration; }

	//! Set attack length
	void SetBandwidth(double bandwidth) { mBandwidth = bandwidth; }
	void SetFrequency(double frequency) { mFrequency = frequency; }

	void SetResonParameters();

	struct FilterTerm
	{
		int m_delay;
		double m_weight;
	};

private:
	double mFrequency;
	double mBandwidth;
	double mDuration;
	double mTime;
	double mGain;

	int mWrLoc;
	CAudioNode* mSource;

	std::vector<double> mQueueX;
	std::vector<double> mQueueY;

	std::vector<FilterTerm> mFilterXTerms;
	std::vector<FilterTerm> mFilterYTerms;

};
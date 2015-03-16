#pragma once
#include "AudioNode.h"
#include "FilterEnvelope.h"

class CFilterEnvelope;

class CFilter : public CAudioNode
{
public:
	CFilter();
	virtual ~CFilter();

	void SetEnvelope(CFilterEnvelope envelope) { mEnvelope = envelope; }

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }
	void SetDuration(double duration) { mDuration = duration; }

protected:
	CAudioNode* mSource;
	CFilterEnvelope mEnvelope;

	double mDuration;
	double mTime;
};

/**
 * \file Filter.h
 *
 * \author Theo Chupp
 *
 * \brief base class for Filters
 */

#pragma once
#include "AudioNode.h"

class CEnvelope;

class CFilter : public CAudioNode
{
public:
	CFilter();
	virtual ~CFilter();

	void SetEnvelope(CEnvelope* envelope) { mEnvelope = envelope; }

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }
	void SetDuration(double duration) { mDuration = duration; }

protected:
	CAudioNode* mSource;
	CEnvelope* mEnvelope;

	double mDuration;
	double mTime;
};

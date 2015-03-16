/**
 * \file Envelope.h
 *
 * \author Theo Chupp
 *
 * \brief Base class for Envelopes
 */

#pragma once
#include "AudioNode.h"

//! Base class for every envelope
class CEnvelope : public CAudioNode
{
public:
	CEnvelope();
	virtual ~CEnvelope();

	//! Start the node generation
	virtual void Start() override {};

	//! Cause one sample to be generated
	virtual bool Generate() override { return false; }

	//! Set the envelope duration
	void SetDuration(double duration) { mDuration = duration; }

	//! Gets Envelope Level
	double GetEnvelopeLevel() { return mEnvelopeLevel; }

protected:
	double mEnvelopeLevel;
	double mDuration;
	double mTime;
};

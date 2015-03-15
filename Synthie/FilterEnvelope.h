#pragma once
#include "AudioNode.h"

class CFilterEnvelope : public CAudioNode
{
public:
	CFilterEnvelope();
	virtual ~CFilterEnvelope();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set the envelope duration
	void SetDuration(double duration) { mDuration = duration; }
	//! Set attack length
	void SetAttack(double attack) { mAttack = attack; }
	//! Set Decay length
	void SetDecay(double decay) { mDecay = decay; }
	//! Set Sustain level
	void SetSustainLevel(double susLevel) { mSustainLevel = susLevel; }
	//! Set Release length
	void SetRelease(double release) { mRelease = release; }

	double GetEnvelopeLevel() { return mEnvelopeLevel; }

private:
	double mDuration;
	double mAttack;
	double mDecay;
	double mSustainLevel;
	double mRelease;

	double mTime;
	double mEnvelopeLevel;
};


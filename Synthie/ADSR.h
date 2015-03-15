#pragma once
#include "AudioNode.h"

class CADSR :
	public CAudioNode
{
public:
	CADSR();
	virtual ~CADSR();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }
	void SetDuration(double duration) { mDuration = duration; }

	//! Set attack length
	void SetAttack(double attack) { mAttack = attack; }
	void SetDecay(double decay) { mDecay = decay; }
	void SetDecayTo(double decayTo) { mDecayTo = decayTo; }
	void SetRelease(double release) { mRelease = release; }

private:
	double mAttack;
	double mDecay;
	double mDecayTo;
	double mRelease;
	double mDuration;
	double mTime;

	CAudioNode* mSource;
};

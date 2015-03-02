#pragma once
#include "AudioNode.h"

class CAR :
	public CAudioNode
{
public:
	CAR();
	virtual ~CAR();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }

	void SetDuration(double duration) { mDuration = duration; }

private:
	double mAttack;
	double mRelease;
	double mDuration;
	double mTime;

	CAudioNode* mSource;
};

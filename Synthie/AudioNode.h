#pragma once
class CAudioNode
{
public:
	CAudioNode();
	virtual ~CAudioNode();

	//! Start the node generation
	virtual void Start() = 0;

	//! Cause one sample to be generated
	virtual bool Generate() = 0;

	//! Get the sample rate in samples per second
	double GetSampleRate() { return mSampleRate; }

	//! Get the sample period in seconds
	double GetSamplePeriod() { return mSamplePeriod; }

	//! Set the sample rate
	void SetSampleRate(double s) { mSampleRate = s;  mSamplePeriod = 1 / s; }

	//! Access a generated audio frame
	const double* Frame() { return mFrame; }

	//! Access one channel of a generated audio frame
	double Frame(int c) { return mFrame[c]; }

protected:
	double mSampleRate;
	double mSamplePeriod;
	double mFrame[2];
};

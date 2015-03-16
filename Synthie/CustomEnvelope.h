/**
 * \file CustomEnvelope.h
 *
 * \author Su Adanali
 *
 * \brief Envelope that can be loaded with points to create a custom shape
 */

#pragma once
#include "Envelope.h"

#include <vector>

class CCustomEnvelope : public CEnvelope
{
public:
	CCustomEnvelope();
	virtual ~CCustomEnvelope();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	struct EnvelopePoint
	{
		double mTime;
		double mLevel;

		inline bool operator==(EnvelopePoint p)
		{
			if (p.mTime == mTime) return true;
			return false;
		}

		inline bool operator<(EnvelopePoint p)
		{
			if (mTime < p.mTime) return true;
			return false;
		}

		inline bool operator>(EnvelopePoint p)
		{
			if (mTime > p.mTime) return true;
			return false;
		}
	};

	void AddPoint(double level, double time);

	double GenerateLevelValue();

	void SetEnvelopePoints();

private:
	std::vector<EnvelopePoint> mEnvelopePoints;
	EnvelopePoint mPrevPoint;
	EnvelopePoint mNextPoint;
};

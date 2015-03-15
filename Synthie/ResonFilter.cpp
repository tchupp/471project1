#include "stdafx.h"
#include "ResonFilter.h"

using namespace std;

CResonFilter::CResonFilter()
{
	mBandwidth = 0.01;
	mFrequency = 0.02;
}


CResonFilter::~CResonFilter()
{
}

void CResonFilter::Start()
{
	mTime = 0;
}

bool CResonFilter::Generate()
{
	// percentage for the ramp
	double fac = 1;

	mFrame[0] = fac * mSource->Frame(0);
	mFrame[1] = fac * mSource->Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return mTime < mDuration;
}

void CResonFilter::SetResonParameters()
{
	double R = 1 - mBandwidth / 2;
	double costheta = (2 * R * cos(2 * PI * mFrequency)) / (1 + pow(R, 2));
	double sintheta = sqrt(1 - pow(costheta, 2));
	double A = (1 - pow(R, 2)) * sintheta;

	A = A * mGain;

	mFilterXTerms.clear();
	mFilterYTerms.clear();

	mNumXFilters = 1;

	FilterTerm term;
	term.m_delay = 0;
	term.m_weight = A;

	mFilterXTerms.push_back(term);

	term.m_delay = 1;
	term.m_weight = 2 * R * costheta;
	mFilterYTerms.push_back(term);

	term.m_delay = 2;
	term.m_weight = -pow(R, 2);
	mFilterYTerms.push_back(term);

}
#include "stdafx.h"
#include "ResonFilter.h"
#include <algorithm>

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
	double audio[2];

	const int QUEUESIZE = 2 * GetSampleRate();

	std::vector<double> queue_x;
	std::vector<double> queue_y;
	queue_x.resize(QUEUESIZE);
	queue_y.resize(QUEUESIZE);

	int wrloc = 0;
	int rdloc = 0;

	double time = 0;
	int delaylength;
	double weight;

	audio[0] = mSource->Frame(0);
	audio[1] = mSource->Frame(1);

	wrloc = (wrloc + 2) % QUEUESIZE;
	queue_x[wrloc] = audio[0];
	queue_x[wrloc + 1] = audio[1];
	audio[0] = 0;
	audio[1] = 0;
	//int delaylength = int((DELAY * SampleRate() + 0.5)) * 2;

	if (mNumXFilters > 0)
	{
		for (auto j = mFilterXTerms.cbegin(); j != mFilterXTerms.cend(); ++j)
		{
			FilterTerm term = *j;
			//delaylength = int((term.m_delay * SampleRate() + 0.5)) * 2;
			delaylength = term.m_delay * 2;;
			weight = term.m_weight;

			rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;
			audio[0] = audio[0] + queue_x[rdloc] * weight;
			rdloc = (rdloc + 1) % QUEUESIZE;
			audio[1] = audio[1] + queue_x[rdloc] * weight;
		}
	}
	if (mNumYFilters > 0)
	{
		for (auto j = mFilterYTerms.cbegin(); j != mFilterYTerms.cend(); ++j)
		{
			FilterTerm term = *j;
			//delaylength = int((term.m_delay * SampleRate() + 0.5)) * 2;
			delaylength = term.m_delay * 2;
			weight = term.m_weight;

			rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;
			audio[0] = audio[0] + queue_y[rdloc] * weight;
			rdloc = (rdloc + 1) % QUEUESIZE;
			audio[1] = audio[1] + queue_y[rdloc] * weight;
		}

		queue_y[wrloc] = audio[0];
		queue_y[wrloc + 1] = audio[1];

		//mFrame[0] = fac * mSource->Frame(0);
		//mFrame[1] = fac * mSource->Frame(1);

		// Update time
		mTime += GetSamplePeriod();
		// We return true until the time reaches the duration.
		return mTime < mDuration;
	}
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

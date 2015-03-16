#pragma once

#include "BaseWave.h"

using namespace std;

class CCustomWave : public BaseWave
{
public:
	CCustomWave();
	virtual ~CCustomWave();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetWavetables();

	vector<double> GetHarmonics() { return mHarmonics; }
	void AddHarmonic(double harmonic) { mHarmonics.push_back(harmonic); }

	void UseCrossFade(bool flag) { mCrossFade = flag; }

private:
	// Any harmonics we have (index is the harmonic, value is the amplitude)
	vector<double> mHarmonics;

	// Flags designating if we should apply playback effects
	bool mCrossFade = false;
};


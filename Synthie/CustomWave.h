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
	virtual void SetWavetables() override;

	vector<double> GetHarmonics() { return mHarmonics; }
	void AddHarmonic(double harmonic) { mHarmonics.push_back(harmonic); }
	void ImplementHarmonics(double* sample, double time);
	void ImplementVibrato(double* sineRadians, double* vibratoRadians);
	void GenerateCrossfade(double time, double crossfadeDuration);	// In prog

	bool GetCrossfadeFlag() { return mUseCrossfade; }
	double GetCrossfadeBeginTime() { return mCrossfadeBeginTime; }

	void SetCrossfadeBeginTime(double time) { mCrossfadeBeginTime = time; }
	void SetVibratoFlag(bool flag) { mUseVibrato = flag; }
	void SetCrossfadeFlag(bool flag) { mUseCrossfade = flag; }
	void SetVibrato(double vibrato) { mVibratoEffect.vibrato = vibrato; }
	void SetVibratoRate(double vibratoRate) { mVibratoEffect.vibratoRate = vibratoRate; }
	void SetPartnerWave(CCustomWave* partner) { mPartnerWave = partner; }

	struct VibratoEffect
	{
		// Default values 
		double vibrato = 0;
		double vibratoRate = 0;
	};

private:
	// Any harmonics we have (index is the harmonic, value is the amplitude)
	vector<double> mHarmonics;
	double mTime;

	VibratoEffect mVibratoEffect;
	bool mUseVibrato = false;

	// >???
	CCustomWave* mPartnerWave = nullptr;
	bool mUseCrossfade = false;
	double mCrossfadeBeginTime;
};


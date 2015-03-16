#pragma once

#include "BaseWave.h"

class CSineWave : public BaseWave
{
public:
	CSineWave();
	virtual ~CSineWave();
	//! Start audio generation
	virtual void Start() override;

	//! Generate one frame of audio
	virtual bool Generate() override;
	virtual void SetWavetables() override;
};

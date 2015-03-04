//! Abstract base class that audio effects
//! will be derived from

#pragma once
#include <vector>
class CAudioEffect
{
public:
	virtual ~CAudioEffect();

	virtual void Process(double *frameIn, double *frameOut) = 0;

	virtual void XmlLoad(IXMLDOMNode * xml) = 0;

protected:
	CAudioEffect();

private:

	// Left & Right queues for stereo audio
	std::vector<double>		mLeftQueue;
	std::vector<double>		mRightQueue;

};


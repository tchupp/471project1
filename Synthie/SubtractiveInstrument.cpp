#include "stdafx.h"
#include "SubtractiveInstrument.h"
#include "Note.h"
#include "Notes.h"

double const RESONGAIN = 10;
double const RESONBANDWIDTH = 0.01;
double const RESONFREQUENCY = 0.02;

CSubtractiveInstrument::CSubtractiveInstrument(std::wstring feature, std::wstring waveform)
{
	mDuration = 0.1;
	StringToFeature(feature);
	StringToWaveform(waveform);
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}

void CSubtractiveInstrument::Start()
{
	//mSinewave.SetSampleRate(GetSampleRate());
	//mSinewave.Start();

	mTime = 0;

	// Tell the AR object it gets its samples from 
	// the sine wave object.

	if (mWaveform == Sawtooth)
	{
		mSawtooth.SetSampleRate(GetSampleRate());
		mSawtooth.Start();
		mADSR.SetSource(&mSawtooth);
	}
	else if (mWaveform == Triangle)
	{
		mTriangle.SetSampleRate(GetSampleRate());
		mTriangle.Start();
		mADSR.SetSource(&mTriangle);
	}
	else if (mWaveform == Square)
	{
		mSquare.SetSampleRate(GetSampleRate());
		mSquare.Start();
		mADSR.SetSource(&mSquare);
	}
	else
	{
		mADSR.SetSource(&mSinewave);
	}
	mADSR.SetSampleRate(GetSampleRate());
	mADSR.SetDuration(mDuration);
	mADSR.Start();
}

bool CSubtractiveInstrument::Generate()
{
	if (mWaveform == Sawtooth)
	{
		mSawtooth.Generate();
	}
	else if (mWaveform == Triangle)
	{
		mTriangle.Generate();
	}
	else if (mWaveform == Square)
	{
		mSquare.Generate();
	}
	else
	{
		mSinewave.Generate();
	}

	auto valid = mADSR.Generate();

	// Read the component's sample and make it our resulting frame.
	mFrame[0] = mADSR.Frame(0);
	mFrame[1] = mADSR.Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return valid;
}

void CSubtractiveInstrument::SetNote(CNote* note, double secPerBeat)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);


		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// number of beats * seconds per beat = seconds for note
			SetDuration(value.dblVal * secPerBeat);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
	}
}

void CSubtractiveInstrument::StringToWaveform(std::wstring waveform)
{
	if (waveform == L"sawtooth")
	{
		mWaveform = Sawtooth;
	}
	else if (waveform == L"triangle")
	{
		mWaveform = Triangle;
	}
	else if (waveform == L"square")
	{
		mWaveform = Square;
	}
}

void CSubtractiveInstrument::StringToFeature(std::wstring feature)
{
	if (feature == L"Reson")
	{
		mFeature = Reson;
	}
	else if (feature == L"Polyphony")
	{
		mFeature = Polyphony;
	}
	else if (feature == L"FilterEnvelope")
	{
		mFeature = FilterEnvelope;
	}
	else if (feature == L"Envelope")
	{
		mFeature = Envelope;
	}
}

void CSubtractiveInstrument::SetFreq(double f)
{
	mSinewave.SetFreq(f);
	mSawtooth.SetFreq(f);
	mTriangle.SetFreq(f);
	mSquare.SetFreq(f);
}

void CSubtractiveInstrument::SetAmplitude(double a)
{
	mSinewave.SetAmplitude(a);
	mSawtooth.SetAmplitude(a);
	mTriangle.SetAmplitude(a);
	mSquare.SetAmplitude(a);
}

void CSubtractiveInstrument::ResonFilter()
{
	double R = 1 - RESONBANDWIDTH / 2;
	double costheta = (2 * R * cos(2 * PI * RESONFREQUENCY)) / (1 + pow(R, 2));
	double sintheta = sqrt(1 - pow(costheta, 2));
	double A = (1 - pow(R, 2)) * sintheta;
	A = A * RESONGAIN;

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

	ProcessFilter();
}

void CSubtractiveInstrument::ProcessFilter()
{
	short audio[2];

	const int QUEUESIZE = 200000;


	std::vector<short> queue_x;
	std::vector<short> queue_y;
	queue_x.resize(QUEUESIZE);
	queue_y.resize(QUEUESIZE);

	int wrloc = 0;
	int rdloc = 0;

	double time = 0;
	int delaylength;
	double weight;

	auto sampleFrames = mDuration * GetSampleRate();
	for (int i = 0; i < sampleFrames; i++ , time += 1. / GetSampleRate())
	{
		//audio[0] = (i + 1) * 10;
		//audio[1] = (i + 1) * 10 + 1;

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
		}
		queue_y[wrloc] = audio[0];
		queue_y[wrloc + 1] = audio[1];
	}
}

/**
 * \file CustomEnvelope.h
 *
 * \author Su Adanali
 *
 * \brief Envelope that can be loaded with points to create a custom shape
 */

#pragma once
#include "Envelope.h"

class CCustomEnvelope :
	public CEnvelope
{
public:
	CCustomEnvelope();
	virtual ~CCustomEnvelope();
};

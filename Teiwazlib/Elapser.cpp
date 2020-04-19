#include "tyrpch.h"
#include "Elapser.h"

tyr::Elapser::Elapser()
	: m_Max(0.f)
	, m_Current(0.f)
	, m_HasElapsed(true)
{
}

tyr::Elapser::Elapser(float elapseTime)
	: m_Max(elapseTime)
	, m_Current(0.f)
	, m_HasElapsed(false)
{
}

bool tyr::Elapser::Update(float deltaTime)
{
	if (m_HasElapsed) return false;
	m_Current += deltaTime;
	if(m_Current >= m_Max)
	{
		m_HasElapsed = true;
		return true;
	}
	
	return false;
}

void tyr::Elapser::Reset()
{
	m_HasElapsed = false;
	m_Current = 0.f;
}

void tyr::Elapser::Reset(float newElapseTime)
{
	m_Max = newElapseTime;
	Reset();
}

void tyr::Elapser::SetMax(float newElapseTime)
{
	if (newElapseTime >= m_Current)
		Reset(newElapseTime);
	else
		m_Max = newElapseTime;
	
}

bool tyr::Elapser::HasElapsed() const
{
	return m_HasElapsed;
}

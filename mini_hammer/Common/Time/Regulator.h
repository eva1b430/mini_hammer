#ifndef REGULATOR_H
#define REGULATOR_H
#include <time.h>
#include <sys/timeb.h>
#include "misc/utils.h"

// ��Ƶ�������������AI���������CDʱ�䣩
class Regulator
{
private:
	// ʱ����
	double m_dUpdatePeriod;

	// 
	unsigned long long m_dwNextUpdateTime;

public:
	Regulator(double NumUpdatesPerSecondRqd)
	{
		unsigned long long t = currentMSecsSinceEpoch();

		// ׷��һ������� 0 ~ 1 ���ƫ�ƿ��Է�ֹCPU����ﵽһ����ֵ
		m_dwNextUpdateTime = t + RandFloat() * 1000;

		// �����ʱ����
		if (NumUpdatesPerSecondRqd > 0)
		{
			m_dUpdatePeriod = 1000.0 / NumUpdatesPerSecondRqd;
		}
		else if (isEqual(0.0, NumUpdatesPerSecondRqd))
		{
			m_dUpdatePeriod = 0.0;
		}
		else if (NumUpdatesPerSecondRqd < 0)
		{
			m_dUpdatePeriod = -1;
		}
	}

	~Regulator();

	bool isReady()
	{
		if (isEqual(0.0, m_dUpdatePeriod)) 
		{
			return true;
		}

		if (m_dUpdatePeriod < 0) 
		{
			return false;
		}

		unsigned long long CurrentTime = currentMSecsSinceEpoch();

		static const double UpdatePeriodVariator = 10.0;
		if (CurrentTime >= m_dwNextUpdateTime)
		{
			m_dwNextUpdateTime = unsigned long long(CurrentTime + m_dUpdatePeriod + RandInRange(-UpdatePeriodVariator, UpdatePeriodVariator));

			return true;
		}

		return false;
	}

private:
	unsigned long long currentMSecsSinceEpoch()
	{
		timeb timebuffer;
		ftime(&timebuffer);
		time_t time = timebuffer.time;
		int millisecond = timebuffer.millitm;
		unsigned long long t = (unsigned long long)time * 1000 + millisecond;

		return t;
	}
};



#endif // REGULATOR_H
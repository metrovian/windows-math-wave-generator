#pragma once
#include "WaveField.h"

typedef std::vector<WaveField> DataFDTD;
class FDTD
{
protected: /* data */
	DataFDTD wave;
	MODE mode;

protected: /* config */
	double lenx;
	double leny;
	double period;
	unsigned long long numx;
	unsigned long long numy;
	unsigned long long numt;
	
protected: /* derived */
	double dx;
	double dy;
	double dt;
	double courant;

public: /* condition */
	bool setBasicCondition(const WaveField& _init, double _period);
	bool setBasicCondition(const WaveField& _init, double _period, unsigned long long _numt);

public: /* source */
	static WaveField generateImpulseCondition(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy, double _posx, double _posy, double _sqrl, double _famp);

protected: /* parts */
	WaveField calcNextStepField(const WaveField& _now, const std::function<Eigen::Vector3d(const WaveField& _field, unsigned long long _idx, unsigned long long _jdx)>& _inspect) const;

protected: /* virtual */
	virtual bool solve(MODE _mode, double _lenx, double _leny, unsigned long long _numx, unsigned long long _numy) = 0;
};
#pragma once
#include "WaveFunction.h"

typedef std::vector<std::vector<double>> DataFDTD;

class FDTD
{
private: /* data */
	DataFDTD wave;

private: /* parameters */
	double length;
	double period;
	double wspeed;
	unsigned long long numx;
	unsigned long long numt;

private: /* derived */
	double dx;
	double dt;
	double courant;

protected: /* condition */
	bool setBasicCondition(double _length, double _period, double _wspeed, unsigned long long _numx, unsigned long long _numt);

public: /* virtual */
	virtual bool solve(double _time) = 0;
};
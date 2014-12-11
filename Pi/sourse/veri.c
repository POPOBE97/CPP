#include "../header/header.h"

bool veri(double _x, double _y) {
	double _rr = 0.0;
	_rr = (_x-50)*(_x-50) + (_y-50)*(_y-50);
	if (_rr <= 2500) return true;
	else return false;
}

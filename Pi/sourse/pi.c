#include "../header/header.h"

double pi(int _loopTimes) {
	double _result = 0.0;
	int _hit_sum = 0;
	double _x, _y;
	
	srand(time(NULL));
	
	for (int i=0; i<_loopTimes; i++) {
		_x = (rand()%100000000)/1000000.0;				//得到一个100以内的7位小数
		_y = (rand()%100000000)/1000000.0;
		if (veri(_x, _y)) _hit_sum++;
	}
	
	_result = (_hit_sum / (double)_loopTimes) * 4.0;
	return _result; 
}

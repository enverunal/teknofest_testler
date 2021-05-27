#include "FreeFall.h"
#include <iostream>

FreeFall::FreeFall(double maxExpected, double minExpected, double ikinciParasutHeight){
	this->maxExpected = maxExpected;
	this->minExpected = minExpected;
	this->ikinciParasutHeight = ikinciParasutHeight;
}

bool FreeFall::ikinciParasutAlgýla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min)) {
	if (!ilkparasut) {
		return false;
	}
	if (ikinciparasut) {
		return false;
	}

	if (!filterFunction(sensorValue, maxExpected, minExpected)) {
		return false;
	}

	if (sensorValue < ikinciParasutHeight) {
		ikinciParasutCount++;
	}
	else {
		if (ikinciParasutCount > 0) {
			ikinciParasutCount--;
		}
	}

	if (ikinciParasutCount > ikinciParasutMaxCount) {
		ikinciparasut = true;
		return true;
	}
	else {
		return false;
	}
}

bool FreeFall::birinciParasutAlgýla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min)) {
	if (ilkparasut) {
		return false;
	}
	if (ikinciparasut) {
		return false;
	}

	if (filterFunction(sensorValue,maxExpected,minExpected)) {
		son10++;
		ort += sensorValue;
	}

	if (son10 == 5) {
		ort /= 5.0;
		double last = hist.back();
		if (std::abs(last - ort) > 3) {
			if (ort > last) {
				if (incr_decr < 10) {
					incr_decr++;
				}
			}
			else {
				if (incr_decr > -10) {
					incr_decr--;
				}
			}
			hist.push_back(ort);
		}
		son10 = 0;
		ort = 0;
	}

	if (incr_decr <= -5) {
		ilkparasut = true;
		return true;
	}

	return false;

}
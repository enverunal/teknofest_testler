#pragma once
#include <vector>

class FreeFall
{
private:
	std::vector<double> hist{ 0 };
	int son10 = 0;
	double ort = 0;
	int incr_decr = 0;
	double maxExpected = 0;
	double minExpected = 0;
	bool ilkparasut = false;
	bool ikinciparasut = false;
	int ikinciParasutCount = 0;
	double ikinciParasutHeight = 0;
	const int ikinciParasutMaxCount = 10;
public:
	FreeFall(double maxExpected, double minExpected, double ikinciParasutHeight);
	/*
		birinci(sürüklenme) paraşütün açılmasını kontrol eder
		sürüklenme paraşütü apogee noktasına yakın açılmalıdır
		açılması gerektiğinde true döner
	*/
	bool birinciParasutAlgıla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
	/*
		ikinci(ana) paraşütün açılmasını kontrol eder
		ana paraşüt düşüşe 600 metre kaldığında açılmalıdır
		açılması gerektiğinde true döner
	*/
	bool ikinciParasutAlgıla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
};


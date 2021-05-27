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
		birinci(sürüklenme) paraþütün açýlmasýný kontrol eder
		sürüklenme paraþütü apogee noktasýna yakýn açýlmalýdýr
		açýlmasý gerektiðinde true döner
	*/
	bool birinciParasutAlgýla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
	/*
		ikinci(ana) paraþütün açýlmasýný kontrol eder
		ana paraþüt düþüþe 600 metre kaldýðýnda açýlmalýdýr
		açýlmasý gerektiðinde true döner
	*/
	bool ikinciParasutAlgýla(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
};


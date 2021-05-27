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
		birinci(s�r�klenme) para��t�n a��lmas�n� kontrol eder
		s�r�klenme para��t� apogee noktas�na yak�n a��lmal�d�r
		a��lmas� gerekti�inde true d�ner
	*/
	bool birinciParasutAlg�la(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
	/*
		ikinci(ana) para��t�n a��lmas�n� kontrol eder
		ana para��t d����e 600 metre kald���nda a��lmal�d�r
		a��lmas� gerekti�inde true d�ner
	*/
	bool ikinciParasutAlg�la(double sensorValue, bool (*filterFunction)(double sensorValue, double max, double min));
};


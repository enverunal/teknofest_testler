#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <random>
#include <windows.h>
#include "FreeFall.h"
#pragma execution_character_set( "utf-8" )


bool filtrele(double sensorValue, double max, double min);

double dalgalanma(double sensor_value, double bouncing_range);
void dalgalanma_testi(int test_sayısı, FreeFall detector);
void yukselme_testi(int apogee, FreeFall& detector, bool bad_sensor = false, bool bouncing_enabled = false, double (*bouncer)(double sensor_value, double bouncing_range) = nullptr);

int main()
{
	SetConsoleOutputCP(65001);
	//tahmin edilen maksimum yükseklik, minimum yükseklik, ikinci paraşüt açılma noktası
	FreeFall freefallDetector(3100,0,600);

	//dalgalanma_testi(10000, freefallDetector);


	//ilk true aniden yüksek veya düşük değerler vermesini sağlar
	//ikinci true yükselirken dalgalanan değerler verir
	yukselme_testi(3100, freefallDetector, true, false, dalgalanma);


}

bool filtrele(double sensorValue, double max, double min) {
	if (sensorValue > max || sensorValue < min) {
		return false;
	}
	else {
		return true;
	}
}

double dalgalanma(double sensor_value, double bouncing_range) {
	static std::mt19937 random_num(time(nullptr));
	double rastgele_deger = (random_num() % 10000) / 10000.0;
	if (rastgele_deger < 0.5) {
		rastgele_deger = -rastgele_deger;
	}
	double bounce = sensor_value + rastgele_deger * bouncing_range; // belirtilen aralıkta rastgele değer ekler yada çıkarır
	return bounce;
}

/*
	Bu test dalgalı gelen verilerin kurtarma sistemini devreye sokabilirliğini test eder
*/
void dalgalanma_testi(int test_sayısı, FreeFall detector){
	for (int i = 0; i < test_sayısı; i++) //bu kadar kere test et
	{
		double sensorValue = dalgalanma(0, 5);//metre cinsinden 0 ila 5 arası değer gönder
		std::cout << "Sensör Değeri: " << sensorValue << "\n";
		bool is_detected = detector.birinciParasutAlgıla(sensorValue, filtrele);//paraşüt açılması gerekiyor ise true döner. Roket kurtarma sistemi için kullanılacak algoritmadır.
		if (is_detected) {
			std::cout << "kurtarma sistemi devreye girdi test basarisiz i : " << i; // eğer paraşüt açılır ise test başarısızdır.
			return;//fonksiyon biter
		}
	}
	std::cout << "Test Basarili\n";//döngü bitti ama 
}

/*
	Bu test kurtarma sisteminin ne zaman devreye gireceğini test eder
	bad_sensor sensör hatalarını test etmek içindir
	bouncing_enabled sensör verilerinin dalgalı gelmesi içindir
*/
void yukselme_testi(int apogee, FreeFall& detector, bool bad_sensor, bool bouncing_enabled, double (*bouncer)(double sensor_value, double bouncing_range)){

	std::cout << "\n\n\n Yükseliş Başladı \n\n\n";//Yükselmenin başladığını belirt

	for (int i = 0; i < apogee; i++)
	{
		double sensorValue = static_cast<double>(i);

		if (bad_sensor) {
			if (i % 39 == 0) {//bir anda yüksek bir değer gelsin
				sensorValue *= 12;
			}

			if (i % 29 == 0) {//bir anda düşük bir değer gelsin
				sensorValue /= 7;
			}
		}

		if (bouncing_enabled) {//gelen değerler dalgalı bir şekilde gelsin
			sensorValue = bouncer(sensorValue, 5);
		}	

		//std::cout << "Gercek yukseklik : " << i << "*";
		//std::cout << "Sensorden gelen yukseklik : " << sensorValue << " ";

		if (detector.birinciParasutAlgıla(sensorValue, filtrele)) {//birinci paraşüt algoritması. Roket içinde kullanılacatır
			std::cout << "\n\nBirinci paraşüt açılış yüksekliği : " << i << "\n\n";
		}

		if (detector.ikinciParasutAlgıla(sensorValue,filtrele)) {//ikinci paraşüt algoritması. Roket içinde kullanılacaktır
			std::cout << "\n\nİkinci paraşüt açılış yüksekliği : " << i << "\n\n";
		}
	}
	std::cout << "\n\n\n Dusus Basladi \n\n\n";//Düşüşün başladığını belirt
	for (int i = apogee; i > 0; i--)
	{
		double sensorValue = static_cast<double>(i);


		if (bad_sensor) {
			if (i % 39 == 0) {//Bir anda yüksek bir değer
				sensorValue *= 12;
			}

			if (i % 29 == 0) {//Bir anda düşük bir değer
				sensorValue /= 7;
			}
		}

		if (bouncing_enabled) {//sensör verileri dalgalansın
			sensorValue = bouncer(sensorValue, 5);
		}

		//std::cout << "Gercek yukseklik : " << i << "*";
		//std::cout << "Sensorden gelen yukseklik : " << sensorValue << " ";

		if (detector.birinciParasutAlgıla(sensorValue, filtrele)) {//birinci paraşüt algoritması. Roket içinde kullanılacatır
			std::cout << "\n\nBirinci paraşüt açılış yüksekliği : " << i << "\n\n";
		}
		if (detector.ikinciParasutAlgıla(sensorValue,filtrele)) {//ikinci paraşüt algoritması. Roket içinde kullanılacaktır
			std::cout << "\n\nİkinci paraşüt açılış yüksekliği : " << i <<"\n\n";
		}
	}
}
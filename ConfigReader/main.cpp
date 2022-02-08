#include <iostream>
#include "ConfigReader.h"

using namespace std;

int main() {
	cout << "Start" << endl << endl;

	ConfigReader cr("config.json");

	cout << cr.get<int>("Peak_Detector/arr/0") << endl;
	cout << cr.get<int>("Peak_Detector/arr/1") << endl; 
	cout << cr.get<int>("Peak_Detector/arr/2") << endl;
	cout << cr.get<int>("Peak_Detector/arr/3/accel_threshold") << endl;
	cout << cr.get<int>("Peak_Detector/level1/level2") << endl;

	cout << cr.get<int>("MPU6050/SMPLRT_DIV") << endl;
	cout << cr.get<string>("I2C/Adapter") << endl;
	cout << cr.get<int>("Drop_Detector/threshold") << endl;
	cout << cr.get<float>("Drop_Detector/threshold") << endl;
	cout << cr.get<double>("Drop_Detector/threshold") << endl;
	cout << cr.get<unsigned long>("Drop_Detector/threshold") << endl;
	cout << cr.get<bool>("MPU6050/useFIFO") << endl;

	cout << cr.get<bool>("MPU6050/useFALSEFIFO", false) << endl;
	cout << cr.get<bool>("MPU6050/useFALSEFIFO", true) << endl;

	bool tmp;
	cout << cr.get<bool>("MPU6050/useFIFO", false, tmp);
	cout << tmp << " " << endl;
	cout << cr.get<bool>("MPU6050/useFALSEFIFO", false, tmp);
	cout << tmp << " " << endl;
	cout << cr.get<bool>("MPU6050/useFALSEFIFO", true, tmp);
	cout << tmp << " " << endl;


	cout << endl << "End" << endl;
	return 0;
}

#include <iostream>
#include <string>
#include <assert.h>
#include "ConfigReader.h"

using namespace std;

string relativePathToConfigFile = "config.json";

int main() {
	cout << "Started Main" << endl;
	ConfigReader::loadConfogfile(relativePathToConfigFile);

	cout << "get Value " << ConfigReader::get<int>("Adapter_INT") << endl;
	cout << "get Value " << ConfigReader::get<float>("Adapter_FLOAT") << endl;
	cout << "get Value " << ConfigReader::get<string>("Adapter_STR") << endl;
	cout << "get Value " << ConfigReader::get<bool>("Adapter_BOOL") << endl;
	cout << "get Value " << ConfigReader::get<int>("BMP280/Oversampling_Temperature") << endl;

	assert(ConfigReader::get<int>("Adapter_INT") == -12);
	assert(ConfigReader::get<int>("Adapter_INT_WRONG", -111) == -111);
	assert(ConfigReader::get<int>("Adapter_FLOAT") == 0);
	assert(ConfigReader::get<int>("MPU6050/GYRO_FS_SEL") == 0);
	assert(ConfigReader::get<int>("MPU6050/NOT/GYRO_FS_SEL", -111) == -111);
	assert(ConfigReader::get<int>("BMP280/IIR_Filter_Timeconstant/2", -111) == 1);
	//assert(ConfigReader::get<int>("I2C/ValuArray/2", -111) == 7);

	assert(ConfigReader::get<float>("Adapter_FLOAT") + 0.21 < 0.001);
	assert(ConfigReader::get<float>("Adapter_FLOAT_NOT", -111) + 111 < 0.001);
	assert(ConfigReader::get<float>("Adapter_INT") + 12.0 < 0.001);
	assert(ConfigReader::get<float>("MPU6050/GYRO_FS_SEL") + 0.0 < 0.001);
	assert(ConfigReader::get<float>("MPU6050/NOT/GYRO_FS_SEL", -111) + 111.0 < 0.001);

	assert(ConfigReader::get<bool>("Adapter_BOOL") == false);
	assert(ConfigReader::get<bool>("Adapter_FLOAT_NOT", true) == true);
	assert(ConfigReader::get<bool>("MPU6050/NOT/GYRO_FS_SEL", true) == true);
	assert(ConfigReader::get<bool>("MPU6050/GYRO_FS_SEL") == false);

	assert(ConfigReader::get<string>("Adapter_INT") == "-12");
	assert(ConfigReader::get<string>("Adapter_STR") == "TESTSTRING");
	assert(ConfigReader::get<string>("Adapter_FLOAT") == "-0.21");
	assert(ConfigReader::get<string>("Adapter_BOOL") == "false");
	assert(ConfigReader::get<string>("MPU6050/NOT/GYRO_FS_SEL", "nIO") == "nIO");

	cout << "Ended Main" << endl;
	return 0;
}
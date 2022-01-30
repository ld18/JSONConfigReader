
#include <iostream>
#include <string>
#include <assert.h>
#include "ConfigReader.h"

using namespace std;

string relativePathToConfigFile = "config.json";

int main() {
	cout << "Started Main" << endl;
	ConfigReader::loadConfogfile(relativePathToConfigFile);

	cout << "get Value " << ConfigReader::get_int("Adapter_INT") << endl;
	cout << "get Value " << ConfigReader::get_float("Adapter_FLOAT") << endl;
	cout << "get Value " << ConfigReader::get_string("Adapter_STR") << endl;
	cout << "get Value " << ConfigReader::get_bool("Adapter_BOOL") << endl;
	cout << "get Value " << ConfigReader::get_int("BMP280/Oversampling_Temperature") << endl;

	assert(ConfigReader::get_int("Adapter_INT") == -12);
	assert(ConfigReader::get_int("Adapter_INT_WRONG", -111) == -111);
	assert(ConfigReader::get_int("Adapter_FLOAT") == 0);
	assert(ConfigReader::get_int("MPU6050/GYRO_FS_SEL") == 0);
	assert(ConfigReader::get_int("MPU6050/NOT/GYRO_FS_SEL", -111) == -111);
	assert(ConfigReader::get_int("BMP280/IIR_Filter_Timeconstant/2", -111) == 1);
	//assert(ConfigReader::get_int>("I2C/ValuArray/2", -111) == 7);

	assert(ConfigReader::get_float("Adapter_FLOAT") + 0.21 < 0.001);
	assert(ConfigReader::get_float("Adapter_FLOAT_NOT", -111) + 111 < 0.001);
	assert(ConfigReader::get_float("Adapter_INT") + 12.0 < 0.001);
	assert(ConfigReader::get_float("MPU6050/GYRO_FS_SEL") + 0.0 < 0.001);
	assert(ConfigReader::get_float("MPU6050/NOT/GYRO_FS_SEL", -111) + 111.0 < 0.001);

	assert(ConfigReader::get_bool("Adapter_BOOL") == false);
	assert(ConfigReader::get_bool("Adapter_FLOAT_NOT", true) == true);
	assert(ConfigReader::get_bool("MPU6050/NOT/GYRO_FS_SEL", true) == true);
	assert(ConfigReader::get_bool("MPU6050/GYRO_FS_SEL") == false);

	assert(ConfigReader::get_string("Adapter_INT") == "-12");
	assert(ConfigReader::get_string("Adapter_STR") == "TESTSTRING");
	assert(ConfigReader::get_string("Adapter_FLOAT") == "-0.21");
	assert(ConfigReader::get_string("Adapter_BOOL") == "false");
	assert(ConfigReader::get_string("MPU6050/NOT/GYRO_FS_SEL", "nIO") == "nIO");

	cout << "Ended Main" << endl;
	return 0;
}
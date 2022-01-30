#ifndef __JSON_ConfigReader
#define __JSON_ConfigReader

#include <string>
#include <atomic>
#include <shared_mutex>
#include <vector>
#include "json.h"

#define regexExpression_KeySeperator "[^\/]+"

using std::string;
using std::atomic;
using std::shared_mutex;
using std::vector;

class ConfigReader {
public:
	ConfigReader() = delete;
	static bool loadConfogfile(const string& path);
	template<typename T> static T get(const string& Keys);
	template<typename T> static T get(const string& Keys, const T& defaultValue);
private:
	static void splitPath(const string& keyPath, vector<string>& keys);
	static json::jobject jsonDoc;
	static atomic<bool> dirty;
	static shared_mutex mutex;
};
template int ConfigReader::get<int>(const string& Keys);
template int ConfigReader::get<int>(const string& Keys, const int& defaultValue);
template float ConfigReader::get<float>(const string& Keys);
template float ConfigReader::get<float>(const string& Keys, const float& defaultValue);
template string ConfigReader::get<string>(const string& Keys);
template string ConfigReader::get<string>(const string& Keys, const string& defaultValue);
template bool ConfigReader::get<bool>(const string& Keys);
template bool ConfigReader::get<bool>(const string& Keys, const bool& defaultValue);


#endif
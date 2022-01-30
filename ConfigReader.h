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
	static int get_int(const string& Keys);
	static int get_int(const string& Keys, const int& defaultValue);
	static string get_string(const string& Keys);
	static string get_string(const string& Keys, const string& defaultValue);
	static float get_float(const string& Keys);
	static float get_float(const string& Keys, const float& defaultValue);
	static bool get_bool(const string& Keys);
	static bool get_bool(const string& Keys, const bool& defaultValue);
private:
	static void splitPath(const string& keyPath, vector<string>& keys);
	static json::jobject jsonDoc;
	static atomic<bool> dirty;
	static shared_mutex mutex;
};

#endif
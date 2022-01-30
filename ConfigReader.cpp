
#include "ConfigReader.h"
#include <fstream>
#include <stdexcept>
#include <regex>

using std::ifstream;
using std::invalid_argument;
using std::smatch;
using std::regex;

shared_mutex ConfigReader::mutex;
atomic<bool> ConfigReader::dirty(true);
json::jobject ConfigReader::jsonDoc;

bool ConfigReader::loadConfogfile(const string& path) {
	mutex.lock();
	dirty.store(true);
	ifstream file(path, ifstream::in);
	if (!file.is_open() || !file.good()) {
		mutex.unlock();
		throw new invalid_argument("ConfigReader::loadConfogfile cant open file, path: " + path);
	}
	string file_string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	try {
		jsonDoc = json::jobject::parse(file_string);
		dirty.store(false);
	}
	catch (const json::parsing_error& e) {
		return false;
	}
	mutex.unlock();
	return true;
}

template<typename T>
T ConfigReader::get(const string& Keys) {
	mutex.lock_shared();
	if (! dirty.load()) {
		vector<string> subKeys;
		ConfigReader::splitPath(Keys, subKeys);
		json::jobject obj = jsonDoc;
		for (unsigned int i = 0; i < subKeys.size() - 1; i++) {
			obj = obj[subKeys[i]].as_object();
		}
		auto value = (T)obj[subKeys.back()];
		mutex.unlock_shared();
		return value;
	}
	else {
		mutex.unlock_shared();
		throw new invalid_argument("ConfigReader::get cant open file because it is dirty");
	}
}

template<typename T>
T ConfigReader::get(const string& Keys, const T& defaultValue) {
	try {
		return ConfigReader::get<T>(Keys);
	}
	catch (const json::invalid_key) {
		return defaultValue;
	}
}

void ConfigReader::splitPath(const string& keyPath, vector<string>& keys) {
	string path(keyPath);
	smatch matches;
	while (regex_search(path, matches, regex(regexExpression_KeySeperator), std::regex_constants::match_not_null)) {
		if (matches.size() != 1) {
			throw new invalid_argument("splitPath found " + std::to_string(matches.size()) + " regex matches in keyPath : " + keyPath);
		}
		keys.push_back(matches[0]);
		path = matches.suffix().str();
	}
}
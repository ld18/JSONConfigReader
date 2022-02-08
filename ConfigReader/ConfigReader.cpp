
#include "ConfigReader.h"
#include <fstream>
#include <stdexcept>
#include <regex>

using std::ifstream;
using std::smatch;
using std::regex;

ConfigReader::ConfigReader(const string & path) {
	unique_lock<shared_mutex> uniqueLock(mutex);
	dirty.store(true);
	ifstream file(path, ifstream::in);
	if (!file.is_open() || !file.good()) {
		throw new parsing_error("ConfigReader cant open file, path: " + path);
	}
	string file_string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	try {
		jsonDoc = json::jobject::parse(file_string);
		dirty.store(false);
	}
	catch (const json::parsing_error&) {
		throw new parsing_error("ConfigReader encountered parsing error, path: " + path);
	}
}

void ConfigReader::splitPath(const string& keyPath, vector<string>& keys) const {
	string path(keyPath);
	smatch matches;
	while (regex_search(path, matches, regex(regexExpression_KeySeperator), std::regex_constants::match_not_null)) {
		if (matches.size() != 1) {
			throw new json::invalid_key("ConfigReader::splitPath found " + std::to_string(matches.size()) + " regex matches in keyPath : " + keyPath);
		}
		keys.push_back(matches[0]);
		path = matches.suffix().str();
	}
}
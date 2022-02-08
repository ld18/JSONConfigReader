#ifndef __JSON_ConfigReader
#define __JSON_ConfigReader

#include <string>
#include <shared_mutex>
#include <vector>
#include <type_traits>
#include "json.h"

#define regexExpression_KeySeperator "[^\/]+"

using std::string;
using std::stoi;
using std::shared_mutex;
using std::shared_lock;
using std::unique_lock;
using std::vector;
using json::parsing_error;
using std::enable_if;
using std::is_arithmetic;
using std::is_same;

class ConfigReader {
public:
	ConfigReader() = delete;
	ConfigReader(const string& path);

	template < typename T, class = typename enable_if<is_arithmetic<T>::value || is_same<string, T>::value>::type>
	T get(const string& Keys) const {
		shared_lock<shared_mutex> sharedLock(mutex);
		vector<string> subKeys;
		splitPath(Keys, subKeys);
		json::jobject obj = jsonDoc;
		for (unsigned int i = 0; i < subKeys.size() - 1; i++) {
			if (obj.is_array()) {
				try {
					obj = obj.array(stoi(subKeys[i]));
				} catch (...) {
					throw new json::invalid_key("ConfigReader::get cant get array value, key: " + subKeys.back());
				}
			} else {
				obj = obj[subKeys[i]].as_object();
			}
		}				
		T value;
		if (obj.is_array()) {
			try	{
				value = static_cast<T>(obj.array(stoi(subKeys.back())));
			} catch (...) {
				throw new json::invalid_key("ConfigReader::get cant get array value, key: " + subKeys.back());
			}
		} else {
			value = static_cast<T>(obj[subKeys.back()]);
		}
		return value;
	}

	template < typename T, class = typename enable_if<is_arithmetic<T>::value || is_same<string, T>::value>::type>
	T get(const string& Keys, const T& defaultValue, bool& foundKey) const {
		try {
			foundKey = true;
			return get<T>(Keys);
		} catch (const json::invalid_key) {
			foundKey = false;
			return defaultValue;
		}
	}

	template < typename T, class = typename enable_if<is_arithmetic<T>::value || is_same<string, T>::value>::type>
	T get(const string& Keys, const T& defaultValue) const {
		bool found;
		return get(Keys, defaultValue, found);
	}

private:
	void splitPath(const string&, vector<string>&) const;
	json::jobject jsonDoc;
	mutable shared_mutex mutex;
};
#endif
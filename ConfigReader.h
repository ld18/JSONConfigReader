#ifndef __JSON_ConfigReader
#define __JSON_ConfigReader

#include <string>
#include <atomic>
#include <shared_mutex>
#include <vector>
#include <type_traits>
#include "json.h"

#define regexExpression_KeySeperator "[^\/]+"

using std::string;
using std::stoi;
using std::atomic;
using std::shared_mutex;
using std::shared_lock;
using std::unique_lock;
using std::vector;
using json::parsing_error;

class ConfigReader {
public:
	ConfigReader() = delete;
	ConfigReader(const string& path);

	template < typename T, class = typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<std::string, T>::value>::type>
	T get(const string& Keys) const {
		shared_lock<shared_mutex> sharedLock(mutex);
		if (!dirty.load()) {
			vector<string> subKeys;
			splitPath(Keys, subKeys);
			json::jobject obj = jsonDoc;
			for (unsigned int i = 0; i < subKeys.size() - 1; i++) {
				if (obj.is_array()) {
					try {
						obj = obj.array(stoi(subKeys[i]));
					}
					catch (...) {
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
			}
			else {
				value = static_cast<T>(obj[subKeys.back()]);
			}
			return value;
		}
		else {
			throw new parsing_error("ConfigReader::get cant open file because it is dirty");
		}
	}

	template < typename T, class = typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<std::string, T>::value>::type>
	T get(const string& Keys, const T& defaultValue, bool& foundKey) const {
		try {
			foundKey = true;
			return get<T>(Keys);
		}
		catch (const json::invalid_key) {
			foundKey = false;
			return defaultValue;
		}
	}

	template < typename T, class = typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<std::string, T>::value>::type>
	T get(const string& Keys, const T& defaultValue) const {
		bool found;
		return get(Keys, defaultValue, found);
	}

private:
	void splitPath(const string& keyPath, vector<string>& keys) const;
	json::jobject jsonDoc;
	atomic<bool> dirty;
	mutable shared_mutex mutex;
};
#endif
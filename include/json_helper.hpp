#pragma once
#include "shared.hpp"
#include <json/json.h>
#include <string>
#include <vector>
#include <map>
#include "errors/interact_box_exceptions.hpp"
#include "string_helper.hpp"

class DllExport JsonHelper {
public:
	static std::string getJsonStringValue(Json::Value json, std::string key);
	static std::string getJsonStringValue(Json::Value json, std::wstring key);
	static std::wstring getJsonWideStringValue(Json::Value json, std::string key);
	static std::wstring getJsonWideStringValue(Json::Value json, std::wstring key);
	static int getJsonIntValue(Json::Value json, std::string key);
	static bool getJsonBoolValue(Json::Value json, std::string key);
	static std::vector<std::string> getJsonStringArray(Json::Value json, std::string key);

	template<typename T>
	static std::vector<T> getJsonArray(Json::Value json, std::string key) {
		const Json::Value valueJson = json.get(key.c_str(), false);
		if (!valueJson.isArray()) throw InteractBoxException(ErrorCodes::JSONNotAnArray, key);
		int size = valueJson.size();
		std::vector<T> result;
		result.reserve(size);
		std::transform(valueJson.begin(), valueJson.end(), std::back_inserter(result), [](const auto& e) {
			std::string stringVal = e.asString();
			return static_cast<T>(stringVal);
		});
		return result;
	}

	template <typename T>
	static std::vector<T> getJsonArray(Json::Value json) {
		if (!json.isArray()) throw InteractBoxException(ErrorCodes::JSONNotAnArray);
		int size = json.size();
		std::vector<T> result;
		result.reserve(size);
		std::transform(json.begin(), json.end(), std::back_inserter(result), [](const auto& e) {
			std::string stringVal = e.asString();
			return static_cast<T>(stringVal);
		});
		return result;
	}
	static Json::Value createJsonBody(std::string key, std::string value);
	static Json::Value createJsonBody(std::map<std::string, std::string> pairs);
	static Json::Value createJsonBody(std::map<std::string, int> pairs);
	static Json::Value parseJsonString(std::string jsonString);
};
#include "json_helper.hpp"

using namespace std;
string JsonHelper::getJsonStringValue(Json::Value json, string key) {
	const Json::Value valueJson = json.get(key.c_str(), false);
	if (!valueJson.isString()) throw InteractBoxException(ErrorCodes::JSONNotAString, key);
	return valueJson.asString();
}

string JsonHelper::getJsonStringValue(Json::Value json, wstring key) {
	const Json::Value valueJson = json.get(StringHelper::wideStringToString(key).c_str(), false);
	if (!valueJson.isString()) throw InteractBoxException(ErrorCodes::JSONNotAString, key);
	return valueJson.asString();
}

wstring JsonHelper::getJsonWideStringValue(Json::Value json, wstring key) {
	const Json::Value valueJson = json.get(StringHelper::wideStringToString(key).c_str(), false);
	if (!valueJson.isString()) throw InteractBoxException(ErrorCodes::JSONNotAString, key);
	return StringHelper::stringToWideString(valueJson.asString());
}

wstring JsonHelper::getJsonWideStringValue(Json::Value json, string key) {
	const Json::Value valueJson = json.get(key.c_str(), false);
	if (!valueJson.isString()) throw InteractBoxException(ErrorCodes::JSONNotAString, key);
	return StringHelper::stringToWideString(valueJson.asString());
}

int JsonHelper::getJsonIntValue(Json::Value json, string key) {
	const Json::Value valueJson = json.get(key, "");
	if (!valueJson.isInt()) throw InteractBoxException(ErrorCodes::JSONNotANumber, key);
	return valueJson.asInt();
}

bool JsonHelper::getJsonBoolValue(Json::Value json, string key) {
	const Json::Value valueJson = json.get(key.c_str(), "");
	if (!valueJson.isBool()) throw InteractBoxException(ErrorCodes::JSONNotABoolean, key);
	return valueJson.asBool();
}

vector<string> JsonHelper::getJsonStringArray(Json::Value json, string key) {
	const Json::Value valueJson = json.get(key.c_str(), false);
	if (!valueJson.isArray()) throw InteractBoxException(ErrorCodes::JSONNotAnArray, key);
	int size = valueJson.size();
	vector<string> result;
	result.reserve(size);
	std::transform(valueJson.begin(), valueJson.end(), std::back_inserter(result), [](const auto& e) {
		return e.asString();
	});
	return result;
}

Json::Value JsonHelper::createJsonBody(string key, string value) {
	Json::Value jsonBody;
	jsonBody[key] = value;
	return jsonBody;
}

Json::Value JsonHelper::createJsonBody(map<string, string> pairs) {
	Json::Value jsonBody;
	for (const auto& pair : pairs) {
		jsonBody[pair.first] = pair.second;
	}
	return jsonBody;
}

Json::Value JsonHelper::createJsonBody(map<string, int> pairs) {
	Json::Value jsonBody;
	for (const auto& pair : pairs) {
		jsonBody[pair.first] = pair.second;
	}
	return jsonBody;
}

Json::Value JsonHelper::parseJsonString(string jsonString) {
	Json::Value parsedBody;
	Json::Reader reader;
	bool success = reader.parse(jsonString, parsedBody);
	if (!success) throw InteractBoxException(ErrorCodes::InvalidJSON);
	return parsedBody;
}
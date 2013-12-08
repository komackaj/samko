#include <libsamko/serialization/jsonreader.h>
#include <stdexcept>
#include <libsamko/stringutils.h>

using namespace std;

namespace samko {

JsonReader::JsonReader() : Reader(false), _root( makeJsonPtr(json_null()) ) {
}

void JsonReader::parse(const string& data) {
    json_error_t error;
    json_t *parsed;
    parsed = json_loadb(data.c_str(), data.size(), JSON_REJECT_DUPLICATES, &error);
    if (!parsed) {
        stringstream ss;
        ss << "JsonReader::parse failed on line " << error.line << " column " << error.column;
        ss << " with message " << error.text;
        throw std::runtime_error(ss.str());
    }
    _root = makeJsonPtr(parsed);
}

const json_t* JsonReader::getCurrentObject() const {
    const json_t* current = _root.get();
    if (json_is_null(current))
        throw std::logic_error("JsonReader: Reading before parsed");

    vector<string> path = split(getObjPrefix(), getPrefixSeparator());
    for (const string& name : path) {
        //printf("Reading object %s\n", name.c_str());
        current = json_object_get(current, name.c_str());
        if (!current)
            throw std::logic_error("JsonWriter: json_object_get failed");
    }
    return current;
}

void JsonReader::throwBadType(const std::string& key, const std::string& expectedType) const{
    stringstream ss;
    ss << "JsonReader - key " << key << " is not a " << expectedType;
    throw std::runtime_error(ss.str());
}

string JsonReader::_readString(const string& name) {
    auto val = json_object_get(getCurrentObject(), name.c_str());
    if (!json_is_string(val))
        throwBadType(name, "string");
    return json_string_value(val);
}

int JsonReader::_readInt(const string& name){
    auto val = json_object_get(getCurrentObject(), name.c_str());
    if (!json_is_integer(val))
        throwBadType(name, "int");
    return json_integer_value(val);
}

double JsonReader::_readDouble(const string& name){
    auto val = json_object_get(getCurrentObject(), name.c_str());
    if (!json_is_real(val))
        throwBadType(name, "real");
    return json_real_value(val);
}

vector<string> JsonReader::_readStringArray(const string& name){
    return readArray<string>(name, [](json_t* val) {return json_string_value(val);} );
}

vector<int> JsonReader::_readIntArray(const string& name){
    return readArray<int>(name, [](json_t* val) {return json_integer_value(val);} );
}

vector<double> JsonReader::_readDoubleArray(const string& name){
    return readArray<double>(name, [](json_t* val) {return json_real_value(val);} );
}

} //namespace samko
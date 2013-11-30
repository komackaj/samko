#include <libsamko/serialization/jsonwriter.h>
#include <stdexcept>
#include <jansson.h>

using namespace std;

namespace samko {

void print(const char *fmt, const json_t *obj) {
/*
    char *data = json_dumps(obj, JSON_INDENT(4) | JSON_PRESERVE_ORDER);
    printf(fmt, data);
    free(data);
*/
}

JsonWriter::JsonWriter(): Writer(false)
    , Data( makeJsonPtr(json_object()) )
{}

json_t *JsonWriter::getCurrentObject() const {
    string prefix = getObjPrefix(),
            separator = getPrefixSeparator();
    json_t *current = Data.get();

    string::size_type pos = prefix.find(separator);
    while (pos != string::npos) {
        //printf("Parsing %s, pos %lu\n", prefix.c_str(), pos);
        //printf("Reading object %s\n\n", prefix.substr(0, pos).c_str());
        current = json_object_get(current, prefix.substr(0, pos).c_str());
        if (!current)
            throw std::logic_error("JsonWriter: json_object_get failed");
        prefix.erase(0, pos + separator.size());
        pos = prefix.find(separator);
    }

    if (!prefix.empty()) {
        //printf("Reading object %s\n", prefix.c_str());
        current = json_object_get(current, prefix.c_str());
        if (!current)
            throw std::logic_error("JsonWriter: json_object_get failed (final stage)");
    }

    return current;
}

string JsonWriter::data() const {
    json_t *current = getCurrentObject();
    char *data = json_dumps(current, JSON_INDENT(4) | JSON_PRESERVE_ORDER);
    string ret(data);
    free(data);
    return ret;
}

void JsonWriter::onBeforeObjPrefixChange(std::string name, std::string oldPrefix){
    //printf("Change, name '%s', old '%s'\n", name.c_str(), oldPrefix.c_str());
    if (oldPrefix.find(name) == string::npos){  // level down
        std::string relName(name);
        if (!oldPrefix.empty())
            relName.erase(0, oldPrefix.size() + getPrefixSeparator().size());
        const char *key = relName.c_str();
        //printf("Level down, adding key '%s'\n", key);
        json_t *current = getCurrentObject();
        json_object_set_new(current, key, json_object());
        //print("New obj '%s' added\n", Data.get());
    }else{
        //printf("Level up\n");
    }
}

void JsonWriter::_writeString(const string& name, const string& val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_string(val.c_str()));
    print( string("Added string '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::_writeInt(const string& name, int val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_integer(val));
    print( string("Added int '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::_writeFloat(const string& name, float val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_real(val));
    print( string("Added float '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::_writeDouble(const string& name, double val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_real(val));
    print( string("Added double '" + name + "', %s\n").c_str(), Data.get());
}

} //namespace samko
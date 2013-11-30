#include <libsamko/serialization/jsonwriter.h>
#include <stdexcept>
#include <jansson.h>
#include <libsamko/stringutils.h>

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
    json_t *current = Data.get();
    vector<string> path = split(getObjPrefix(), getPrefixSeparator());
    for (const string& name : path) {
        //printf("Reading object %s\n", name.c_str());
        current = json_object_get(current, name.c_str());
        if (!current)
            throw std::logic_error("JsonWriter: json_object_get failed");
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

void JsonWriter::writeString(const string& name, const string& val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_string(val.c_str()));
    print( string("Added string '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::writeInt(const string& name, int val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_integer(val));
    print( string("Added int '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::writeFloat(const string& name, float val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_real(val));
    print( string("Added float '" + name + "', %s\n").c_str(), Data.get());
}

void JsonWriter::writeDouble(const string& name, double val){
    json_t *current = getCurrentObject();
    json_object_set_new(current, name.c_str(), json_real(val));
    print( string("Added double '" + name + "', %s\n").c_str(), Data.get());
}

} //namespace samko
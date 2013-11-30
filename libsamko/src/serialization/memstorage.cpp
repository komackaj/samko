#include <libsamko/serialization/memstorage.h>

using namespace std;

namespace samko {

MemStorage::MemStorage() {
}

/* reading */

void MemStorage::parse(const string& data) {
}

std::string MemStorage::_readString(const std::string& name) {
    //printf("Reading string %s, value %s\n", name.c_str(), strMap[name].c_str());
    return strMap[name];
}

int MemStorage::_readInt(const std::string& name){
    //printf("Reading int %s, value %d\n", name.c_str(), intMap[name]);
    return intMap[name];
}

float MemStorage::_readFloat(const std::string& name){
    //printf("Reading float %s, value %f\n", name.c_str(), floatMap[name]);
    return floatMap[name];
}

double MemStorage::_readDouble(const std::string& name){
    //printf("Reading double %s, value %lf\n", name.c_str(), doubleMap[name]);
    return doubleMap[name];
}

/* writing */

string MemStorage::data() const {
    return string();
}

void MemStorage::_writeString(const std::string& name, const std::string& val){
    //printf("Writing string %s, value %s\n", name.c_str(), val.c_str());
    strMap.insert(make_pair(name, val));
}

void MemStorage::_writeInt(const std::string& name, int val){
    //printf("Writing int %s, value %d\n", name.c_str(), val);
    intMap.insert(make_pair(name, val));
}

void MemStorage::_writeFloat(const std::string& name, float val){
    //printf("Writing float %s, value %f\n", name.c_str(), val);
    floatMap.insert(make_pair(name, val));
}

void MemStorage::_writeDouble(const std::string& name, double val){
    //printf("Writing double %s, value %lf\n", name.c_str(), val);
    doubleMap.insert(make_pair(name, val));
}

} //namespace samko
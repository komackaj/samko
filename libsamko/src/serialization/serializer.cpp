#include <libsamko/serialization/serializer.h>

using namespace std;

namespace samko {

Serializer::Serializer(bool autoPrefix) : AutoPrefix(autoPrefix) {
}

string Serializer::getPrefixSeparator() const {
    return "/";
}

const string& Serializer::getObjPrefix() const {
    return ObjPrefix;
}

void Serializer::setObjPrefix(const string& prefix) {
    std::string old(ObjPrefix);
    onBeforeObjPrefixChange(prefix, old);
    ObjPrefix = prefix;
}

string Serializer::getPrefixedName(const string& name) {
    return ObjPrefix.empty() ? name : ObjPrefix + getPrefixSeparator() + name;
}

std::string Serializer::autoprefixName(const std::string& name){
    return AutoPrefix ? getPrefixedName(name) : name;
}

void Serializer::onBeforeObjPrefixChange(std::string name, std::string oldPrefix){
}

} //namespace samko
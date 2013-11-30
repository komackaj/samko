#include <libsamko/serialization/serializer.h>

using namespace std;

namespace samko {

const string& Serializer::getObjPrefix() const {
    return ObjPrefix;
}

void Serializer::setObjPrefix(const string& prefix) {
    ObjPrefix = prefix;
}

string Serializer::getPrefixedName(const string& name) {
    return ObjPrefix.empty() ? name : ObjPrefix + "/" + name;
}

} //namespace samko
#include <libsamko/serialization/reader.h>
#include <libsamko/serialization/serializable.h>
#include <libsamko/serialization/adapters/matserializableadapter.h>

namespace samko {

Reader::Reader(bool autoPrefix) : Serializer(autoPrefix) {
}

void Reader::readObject(const std::string& name, Serializable& obj){
    std::string scope = getObjPrefix();
    setObjPrefix(getPrefixedName(name));
    obj.readFrom(*this);
    setObjPrefix(scope);
}

/* simple data */
std::string Reader::readString(const std::string& name) {
    return _readString(autoprefixName(name));
}

int Reader::readInt(const std::string& name) {
    return _readInt(autoprefixName(name));
}

double Reader::readDouble(const std::string& name) {
    return _readDouble(autoprefixName(name));
}

/* arrays */

std::vector<std::string> Reader::readStringArray(const std::string& name){
    return _readStringArray(autoprefixName(name));
}

std::vector<int> Reader::readIntArray(const std::string& name){
    return _readIntArray(autoprefixName(name));
}

std::vector<double> Reader::readDoubleArray(const std::string& name){
    return _readDoubleArray(autoprefixName(name));
}

/* common objects */

void Reader::readMat(const std::string name, cv::Mat& mat){
    MatSerializableAdapter serAdapt(mat);
    readObject(name, serAdapt);
}

} //namespace samko
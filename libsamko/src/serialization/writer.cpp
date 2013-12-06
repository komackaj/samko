#include <libsamko/serialization/writer.h>
#include <libsamko/serialization/serializable.h>
#include <libsamko/serialization/adapters/matserializableadapter.h>

namespace samko {

Writer::Writer(bool autoPrefix) : Serializer(autoPrefix) {
}

void Writer::write(const std::string& name, const Serializable& obj){
    std::string scope = getObjPrefix();
    setObjPrefix(getPrefixedName(name));
    obj.writeTo(*this);
    setObjPrefix(scope);
}

/* simple types */

void Writer::write(const std::string& name, const std::string& val){
    writeString(autoprefixName(name), val);
}

void Writer::write(const std::string& name, int val) {
    writeInt(autoprefixName(name), val);
}

void Writer::write(const std::string& name, double val) {
    writeDouble(autoprefixName(name), val);
}

/* arrays */

void Writer::write(const std::string& name, const std::vector<std::string>& vals) {
    writeStringArray(autoprefixName(name), vals);
}

void Writer::write(const std::string& name, const std::vector<int>& vals) {
    writeIntArray(autoprefixName(name), vals);
}

void Writer::write(const std::string& name, const std::vector<double>& vals) {
    writeDoubleArray(autoprefixName(name), vals);
}

/* common objects */

void Writer::write(const std::string& name, const cv::Mat& mat) {
    MatSerializableAdapter serAdapt(mat);
    write(name, serAdapt);
}

} //namespace samko
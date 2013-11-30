#include <libsamko/serialization/writer.h>
#include <libsamko/serialization/serializable.h>

namespace samko {

Writer::Writer(bool autoPrefix) : Serializer(autoPrefix) {
}

void Writer::write(const std::string& name, const Serializable& obj){
    std::string scope = getObjPrefix();
    setObjPrefix(getPrefixedName(name));
    obj.writeTo(*this);
    setObjPrefix(scope);
}

void Writer::write(const std::string& name, const std::string& val){
    writeString(autoprefixName(name), val);
}

void Writer::write(const std::string& name, int val) {
    writeInt(autoprefixName(name), val);
}

void Writer::write(const std::string& name, double val) {
    writeDouble(autoprefixName(name), val);
}

void Writer::write(const std::string& name, const cv::Mat& mat) {
    write(name + "-type", mat.type());
    write(name + "-cols", mat.cols);
    write(name + "-rows", mat.rows);
    const double *data = mat.ptr<double>();
    int elems = mat.size().area();
    for (int i = 0; i < elems; ++i, ++data)
         write(name + std::to_string(i), *data);
}

} //namespace samko
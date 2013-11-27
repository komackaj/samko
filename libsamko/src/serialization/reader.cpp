#include <libsamko/serialization/reader.h>
#include <libsamko/serialization/serializable.h>

namespace samko {

void Reader::readObject(const std::string& name, Serializable& obj){
    std::string scope = getObjPrefix();
    setObjPrefix(getPrefixedName(name));
    obj.readFrom(*this);
    setObjPrefix(scope);
}

std::string Reader::readString(const std::string& name) {
    return _readString(getPrefixedName(name));
}

int Reader::readInt(const std::string& name) {
    return _readInt(getPrefixedName(name));
}

float Reader::readFloat(const std::string& name) {
    return _readFloat(getPrefixedName(name));
}

double Reader::readDouble(const std::string& name) {
    return _readDouble(getPrefixedName(name));
}

void Reader::readMat(const std::string name, cv::Mat& mat){
    cv::Size size;
    int type = readInt(name + "-type");
    size.width = readInt(name + "-cols");
    size.height = readInt(name + "-rows");
    mat.create(size, type);

    double *data = mat.ptr<double>();
    int elems = mat.size().area();
    for (int i = 0; i < elems; ++i, ++data)
        *data = readDouble(name + std::to_string(i));
}

} //namespace samko
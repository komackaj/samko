#include <libsamko/serialization/reader.h>
#include <libsamko/serialization/serializable.h>

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
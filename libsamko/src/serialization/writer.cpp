#include <libsamko/serialization/writer.h>

namespace samko {

void Writer::writeString(const std::string& name, const std::string& val){
    _writeString(getPrefixedName(name), val);
}

void Writer::writeInt(const std::string& name, int val) {
    _writeInt(getPrefixedName(name), val);
}

void Writer::writeFloat(const std::string& name, float val) {
    _writeFloat(getPrefixedName(name), val);
}

void Writer::writeDouble(const std::string& name, double val) {
    _writeDouble(getPrefixedName(name), val);
}

void Writer::writeMat(const std::string& name, const cv::Mat& mat) {
    writeInt(name + "-type", mat.type());
    writeInt(name + "-cols", mat.cols);
    writeInt(name + "-rows", mat.rows);
    const double *data = mat.ptr<double>();
    int elems = mat.size().area();
    for (int i = 0; i < elems; ++i, ++data)
         writeDouble(name + std::to_string(i), *data);
}

} //namespace samko
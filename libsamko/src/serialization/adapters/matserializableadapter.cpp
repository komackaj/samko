#include <libsamko/serialization/adapters/matserializableadapter.h>

namespace samko {

MatSerializableAdapter::MatSerializableAdapter(cv::Mat& mat) : _mat(&mat), _cmat(nullptr)
{}

MatSerializableAdapter::MatSerializableAdapter(const cv::Mat& mat) : _mat(nullptr), _cmat(&mat)
{}

void MatSerializableAdapter::readFrom(Reader& reader){
    assert(_mat);
    cv::Size size;
    int type = reader.readInt("type");
    size.width = reader.readInt("cols");
    size.height = reader.readInt("rows");
    std::vector<double> data = reader.readDoubleArray("data");
    *_mat = cv::Mat(size, type);
    std::copy(begin(data), end(data), _mat->begin<double>());
}

void MatSerializableAdapter::writeTo(Writer& writer) const {
    assert(_cmat);
    writer.write("type", _cmat->type());
    writer.write("cols", _cmat->cols);
    writer.write("rows", _cmat->rows);
    std::vector<double> data(_cmat->begin<double>(), _cmat->end<double>());
    writer.write("data", data);
}

} //namespace samko
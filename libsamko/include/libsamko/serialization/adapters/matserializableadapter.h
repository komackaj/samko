#ifndef SAMKO_MATSERIALIZABLEADAPTER_H
#define SAMKO_MATSERIALIZABLEADAPTER_H

#include <libsamko/serialization/serializable.h>
#include <opencv2/core/core.hpp>

namespace samko {

/// Internal serialization adapter for OpenCV matrix.
/// TODO: handle different data types
class MatSerializableAdapter : public Serializable
{
public:
    MatSerializableAdapter(cv::Mat& mat);
    MatSerializableAdapter(const cv::Mat& mat);
    
    virtual void readFrom(Reader& reader);
    
    virtual void writeTo(Writer& writer) const;
    
private:
    cv::Mat         *_mat;
    const cv::Mat   *_cmat;
};

} //namespace samko
#endif // SAMKO_MATSERIALIZABLEADAPTER_H

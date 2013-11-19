#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "serializer.h"
#include <opencv2/core/core.hpp>

namespace samko {

/// Abstract interface for object deserialization
class Reader : public Serializer {
public:

    std::string readString(const std::string& name);
    int readInt(const std::string& name);
    float readFloat(const std::string& name);
    double readDouble(const std::string& name);

    void readMat(const std::string name, cv::Mat& mat);

protected:
    virtual std::string _readString(const std::string& name) = 0;
    virtual int _readInt(const std::string& name) = 0;
    virtual float _readFloat(const std::string& name) = 0;
    virtual double _readDouble(const std::string& name) = 0;
};

} // namespace samko

#endif // READER_H_INCLUDED

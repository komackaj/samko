#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include "serializer.h"
#include <opencv2/core/core.hpp>

namespace samko {

class Serializable;

/** Abstract interface for object serialization
 *  When serializing objects with same attribute names, you should use object prefix */
class Writer : public Serializer {
public:
    void writeObject(const std::string& name, const Serializable *obj);

    void writeString(const std::string& name, const std::string& val);
    void writeInt(const std::string& name, int val);
    void writeFloat(const std::string& name, float val);
    void writeDouble(const std::string& name, double val);

    void writeMat(const std::string& name, const cv::Mat& mat);

protected:
    virtual void _writeString(const std::string& name, const std::string& val) = 0;
    virtual void _writeInt(const std::string& name, int val) = 0;
    virtual void _writeFloat(const std::string& name, float val) = 0;
    virtual void _writeDouble(const std::string& name, double val) = 0;
};

} // namespace samko

#endif // WRITER_H_INCLUDED

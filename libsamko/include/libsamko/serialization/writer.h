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
    /** standard constructor
     *  @param autoPrefix   send prefixed names to _read* methods */
    Writer(bool autoPrefix = true);

    void write(const std::string& name, const Serializable& obj);

/* simple types */
    void write(const std::string& name, const std::string& val);
    void write(const std::string& name, int val);
    void write(const std::string& name, double val);

/* arrays */
    void write(const std::string& name, const std::vector<std::string>& val);
    void write(const std::string& name, const std::vector<int>& val);
    void write(const std::string& name, const std::vector<double>& val);

/* common objects */
    void write(const std::string& name, const cv::Mat& mat);

    /// Get current data
    virtual std::string data() const = 0;

protected:
    virtual void writeString(const std::string& name, const std::string& val) = 0;
    virtual void writeInt(const std::string& name, int val) = 0;
    virtual void writeDouble(const std::string& name, double val) = 0;
    virtual void writeStringArray(const std::string& name, const std::vector<std::string>& vals) = 0;
    virtual void writeIntArray(const std::string& name, const std::vector<int>& vals) = 0;
    virtual void writeDoubleArray(const std::string& name, const std::vector<double>& vals) = 0;
};

} // namespace samko

#endif // WRITER_H_INCLUDED

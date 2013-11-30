#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "serializer.h"
#include <opencv2/core/core.hpp>

namespace samko {

class Serializable;

/// Abstract interface for object deserialization
class Reader : public Serializer {
public:

    /** standard constructor
     *  @param autoPrefix   send prefixed names to _read* methods */
    Reader(bool autoPrefix = true);

    /// parse data from string
    /// @warning must be called previous to read* method
    /// @throws std::runtime error on failure
    virtual void parse(const std::string& data) = 0;

    /** reads Serializable from parsed data
     *  @pre  successful call to parse */
    void readObject(const std::string& name, Serializable& obj);

    /** reads std::string from parsed data
     *  @pre  successful call to parse */
    std::string readString(const std::string& name);

    /** reads int from parsed data
     *  @pre  successful call to parse */
    int readInt(const std::string& name);

    /** reads double from parsed data
     *  @pre  successful call to parse */
    double readDouble(const std::string& name);

    /** reads cv::Mat from parsed data
     *  @pre  successful call to parse */
    void readMat(const std::string name, cv::Mat& mat);

protected:
    virtual std::string _readString(const std::string& name) = 0;
    virtual int _readInt(const std::string& name) = 0;
    virtual double _readDouble(const std::string& name) = 0;
};

} // namespace samko

#endif // READER_H_INCLUDED

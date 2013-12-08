#ifndef SAMKO_JSONWRITER_H
#define SAMKO_JSONWRITER_H

#include <libsamko/serialization/writer.h>
#include "json_common.h"

namespace samko {

/** Writer for JSON format */
class JsonWriter : public Writer {
public:

    JsonWriter();
    JsonWriter(JsonWriter &&rhs) = default;

    ///@returns written data as JSON text
    virtual std::string data() const;

protected:
    virtual void writeString(const std::string& name, const std::string& val);
    virtual void writeInt(const std::string& name, int val);
    virtual void writeDouble(const std::string& name, double val);
    virtual void writeStringArray(const std::string& name, const std::vector<std::string>& vals);
    virtual void writeIntArray(const std::string& name, const std::vector<int>& vals);
    virtual void writeDoubleArray(const std::string& name, const std::vector<double>& vals);

    virtual void onBeforeObjPrefixChange(std::string name, std::string oldPrefix);

private:

    JsonPtr     Data;     ///<written data

    json_t*     getCurrentObject() const;

    template<typename T>
    json_t* buildArray(const std::vector<T>& vals, std::function<json_t*(T)> convFunc) {
        json_t *a = json_array();
        for (const T& val : vals)
           json_array_append_new(a, convFunc(val));
        return a;
    }
};

} //namespace samko
#endif // SAMKO_JSONWRITER_H
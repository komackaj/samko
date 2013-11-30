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
    virtual void _writeString(const std::string& name, const std::string& val);
    virtual void _writeInt(const std::string& name, int val);
    virtual void _writeFloat(const std::string& name, float val);
    virtual void _writeDouble(const std::string& name, double val);

    virtual void onBeforeObjPrefixChange(std::string name, std::string oldPrefix);

private:

    JsonPtr     Data;     ///<written data

    /// @todo: extract prefix parser (see JsonReader::getCurrentObj)
    json_t* getCurrentObject() const;
};

} //namespace samko
#endif // SAMKO_JSONWRITER_H
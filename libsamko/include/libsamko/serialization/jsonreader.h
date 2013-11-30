#ifndef SAMKO_JSONREADER_H
#define SAMKO_JSONREADER_H

#include "reader.h"
#include "json_common.h"

namespace samko {
class JsonReader : public Reader
{
public:

    /// standard constructor
    JsonReader();

    /// parse JSON data
    virtual void parse(const std::string& data);

protected:
    virtual std::string _readString(const std::string& name);
    virtual int _readInt(const std::string& name);
    virtual float _readFloat(const std::string& name);
    virtual double _readDouble(const std::string& name);

private:
    JsonPtr     _root;

    /// @todo: extract prefix parser (see JsonWriter::getCurrentObj)
    const json_t* getCurrentObject() const;

    void throwBadType(const std::string& key, const std::string& expectedType) const;
};

} //namespace samko
#endif // SAMKO_JSONREADER_H
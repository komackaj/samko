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
    virtual double _readDouble(const std::string& name);

    virtual std::vector<std::string> _readStringArray(const std::string& name);
    virtual std::vector<int> _readIntArray(const std::string& name);
    virtual std::vector<double> _readDoubleArray(const std::string& name);

private:
    JsonPtr     _root;

    const json_t* getCurrentObject() const;
    void throwBadType(const std::string& key, const std::string& expectedType) const;

    template<typename T>
    std::vector<T> readArray(const std::string& name, std::function<T(json_t*)> convFunc){
        std::vector<T> ret;
        auto val = json_object_get(getCurrentObject(), name.c_str());
        if (!json_is_array(val))
            throwBadType(name, "array");

        size_t index;
        json_t *value;
        json_array_foreach(val, index, value)
            ret.push_back(convFunc(value));
        return ret;
    }
};

} //namespace samko
#endif // SAMKO_JSONREADER_H
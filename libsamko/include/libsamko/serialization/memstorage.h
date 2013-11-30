#ifndef MEMREADER_H_INCLUDED
#define MEMREADER_H_INCLUDED

#include "reader.h"
#include "writer.h"
#include <map>

namespace samko {

/** Memory reader/writer. Stores object attributes in maps
 * @note Mainly for debug purposes only */
class MemStorage: public Reader, public Writer {
public:

    MemStorage();
    virtual void parse(const std::string& data);

    ///@warning not implemented
    ///@returns empty data
    virtual std::string data() const;

protected:
    virtual std::string _readString(const std::string& name);
    virtual int _readInt(const std::string& name);
    virtual float _readFloat(const std::string& name);
    virtual double _readDouble(const std::string& name);

    virtual void _writeString(const std::string& name, const std::string& val);
    virtual void _writeInt(const std::string& name, int val);
    virtual void _writeFloat(const std::string& name, float val);
    virtual void _writeDouble(const std::string& name, double val);

private:
    std::map<std::string, std::string>   strMap;
    std::map<std::string, int>           intMap;
    std::map<std::string, float>         floatMap;
    std::map<std::string, double>        doubleMap;
};

} //namespace samko

#endif // MEMREADER_H_INCLUDED
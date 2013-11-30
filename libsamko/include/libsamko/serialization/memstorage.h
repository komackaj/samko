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
    virtual double _readDouble(const std::string& name);
    virtual std::vector<std::string> _readStringArray(const std::string& name);
    virtual std::vector<int> _readIntArray(const std::string& name);
    virtual std::vector<double> _readDoubleArray(const std::string& name);

    virtual void writeString(const std::string& name, const std::string& val);
    virtual void writeInt(const std::string& name, int val);
    virtual void writeDouble(const std::string& name, double val);
    virtual void writeStringArray(const std::string& name, const std::vector<std::string>& vals);
    virtual void writeIntArray(const std::string& name, const std::vector<int>& vals);
    virtual void writeDoubleArray(const std::string& name, const std::vector<double>& vals);

private:
    std::map<std::string, std::string>   strMap;
    std::map<std::string, int>           intMap;
    std::map<std::string, double>        doubleMap;

    std::map<std::string, std::vector<std::string>>   strVecMap;
    std::map<std::string, std::vector<int>>           intVecMap;
    std::map<std::string, std::vector<double>>        doubleVecMap;
};

} //namespace samko

#endif // MEMREADER_H_INCLUDED
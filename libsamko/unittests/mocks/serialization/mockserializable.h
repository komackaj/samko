#ifndef MOCKSERIALIZABLE_H_INCLUDED
#define MOCKSERIALIZABLE_H_INCLUDED

#include <gmock/gmock.h>
#include <libsamko/serialization/serializable.h>

class MockSerializable : public samko::Serializable {
public:

    struct Data{
        std::string str;
        int      i;
        double   d;
        std::vector<std::string>   vecStr;
        std::vector<int>            vecInt;
        std::vector<double>         vecDbl;
    };

    virtual void readFrom(samko::Reader& reader) {
        Data d;
        _data.str = reader.readString("string");
        _data.i = reader.readInt("int");
        _data.d = reader.readDouble("dbl");
        _data.vecStr = reader.readStringArray("vecStr");
        _data.vecInt = reader.readIntArray("vecInt");
        _data.vecDbl = reader.readDoubleArray("vecDbl");
    }

    virtual void writeTo(samko::Writer& writer) const {
        Data d = defineData();
        writer.write("string", d.str);
        writer.write("int", d.i);
        writer.write("dbl", d.d);
        writer.write("vecStr", d.vecStr);
        writer.write("vecInt", d.vecInt);
        writer.write("vecDbl", d.vecDbl);
    };

    MOCK_CONST_METHOD0(defineData, Data(void));

    Data getReadData() const {
        return _data;
    }

private:
    Data    _data;
};

#endif // MOCKSERIALIZABLE_H_INCLUDED

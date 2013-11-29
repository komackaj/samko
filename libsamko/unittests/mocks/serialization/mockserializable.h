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
        float    f;
    };

    virtual void readFrom(samko::Reader& reader) {
        Data d;
        _data.str = reader.readString("string");
        _data.i = reader.readInt("int");
        _data.f = reader.readFloat("float");
        _data.d = reader.readDouble("dbl");
    }

    virtual void writeTo(samko::Writer& writer) const {
        Data d = defineData();
        writer.writeString("string", d.str);
        writer.writeInt("int", d.i);
        writer.writeFloat("float", d.f);
        writer.writeDouble("dbl", d.d);
    };

    MOCK_CONST_METHOD0(defineData, Data(void));

    Data getReadData() const {
        return _data;
    }

private:
    Data    _data;
};

#endif // MOCKSERIALIZABLE_H_INCLUDED

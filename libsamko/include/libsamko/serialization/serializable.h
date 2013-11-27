#ifndef SERIALIZABLE_H_INCLUDED
#define SERIALIZABLE_H_INCLUDED

#include "reader.h"
#include "writer.h"

namespace samko {

/// Abstract serializable object
class Serializable {
public:
    virtual void readFrom(Reader& reader) = 0;
    virtual void writeTo(Writer& reader) const = 0;
};

} // namespace samko

#endif // SERIALIZABLE_H_INCLUDED

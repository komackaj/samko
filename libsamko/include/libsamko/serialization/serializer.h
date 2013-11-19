#ifndef SERIALIZER_H_INCLUDED
#define SERIALIZER_H_INCLUDED

#include <string>

namespace samko {

/// Ancestor for Reader and Writer
/// Handles attribute names uniqueness.
class Serializer {

public:
    /// ObjPrefix member getter
    /// @see ObjPrefix
    const std::string& getObjPrefix();

    /// ObjPrefix member setter
    /// @see ObjPrefix
    void setObjPrefix(const std::string& prefix);

protected:
    std::string     ObjPrefix;

    /// Ensures attribute name uniqueness for multiple objects of same class
    /// @returns ObjPrefix + separator + name
    std::string getPrefixedName(const std::string& name);
};

}

#endif // SERIALIZER_H_INCLUDED

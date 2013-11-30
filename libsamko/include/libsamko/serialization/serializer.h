#ifndef SERIALIZER_H_INCLUDED
#define SERIALIZER_H_INCLUDED

#include <string>

namespace samko {

/// Ancestor for Reader and Writer
/// Handles attribute names uniqueness.
class Serializer {

public:

    /** standard constructor
     *  @param autoPrefix   enable autoprefix in autoprefixName*/
    Serializer(bool autoPrefix = true);

    /// ObjPrefix member getter
    /// @see ObjPrefix
    const std::string& getObjPrefix() const;

    /// ObjPrefix member setter
    /// @see ObjPrefix
    void setObjPrefix(const std::string& prefix);

protected:
    std::string     ObjPrefix;

    std::string getPrefixSeparator() const;

    /// Ensures attribute name uniqueness for multiple objects of same class
    /// @returns ObjPrefix + separator + name
    std::string getPrefixedName(const std::string& name);

    /// Generates name according to AutoPrefix
    std::string autoprefixName(const std::string& name);

    virtual void onBeforeObjPrefixChange(std::string name, std::string oldPrefix);

private:
    bool    AutoPrefix;
};

}

#endif // SERIALIZER_H_INCLUDED

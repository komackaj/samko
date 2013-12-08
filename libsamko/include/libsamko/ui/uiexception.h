#ifndef UIEXCEPTION_H_INCLUDED
#define UIEXCEPTION_H_INCLUDED

#include <stdexcept>
namespace samko{

class UIException : public std::runtime_error{
public:
    explicit UIException(const std::string& __arg)
        : std::runtime_error(__arg)
    {};
};

} //namespace
#endif // UIEXCEPTION_H_INCLUDED

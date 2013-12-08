#ifndef SAMKO_JSON_COMMON_H_INCLUDED
#define SAMKO_JSON_COMMON_H_INCLUDED

#include <memory>
#include <jansson.h>

namespace samko {
///unique_ptr with custom deleter (free)
typedef std::unique_ptr<json_t, void(*)(json_t *)> JsonPtr;

JsonPtr makeJsonPtr(json_t *p);

} //namespace samko
#endif // SAMKO_JSON_COMMON_H_INCLUDED

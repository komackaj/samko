#include <libsamko/serialization/json_common.h>
#include <jansson.h>

namespace samko {

JsonPtr makeJsonPtr(json_t *p) {
    return JsonPtr(p, [](json_t *p){ json_decref(p); });
}

} //namespace samko
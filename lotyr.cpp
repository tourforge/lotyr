#include <boost/property_tree/ptree.hpp>
#include <valhalla/tyr/actor.h>

extern "C" int hello(void) {
    valhalla::tyr::actor_t actor{boost::property_tree::ptree()};
    return 2;
}
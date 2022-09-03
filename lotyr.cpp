#include <boost/property_tree/ptree.hpp>

#include <valhalla/baldr/rapidjson_utils.h>
#include <valhalla/tyr/actor.h>

#include "lotyr.h"

thread_local valhalla::tyr::actor_t * actor;

extern "C" void init(char * config_path) {
  // Load the configuration
  std::string config_file(config_path);
  boost::property_tree::ptree config;
  rapidjson::read_json(config_file, config);

  // Delete the actor in case of repeated initialization
  if (actor) {
    delete actor;
    actor = nullptr;
  }

  // Initialize the actor
  actor = new valhalla::tyr::actor_t(config);
}

extern "C" void deinit(void) {
  if (actor) {
    delete actor;
    actor = nullptr;
  }
}
#include <exception>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include <valhalla/baldr/rapidjson_utils.h>
#include <valhalla/tyr/actor.h>
#include <valhalla/worker.h>

#include "lotyr.h"

thread_local std::unique_ptr<valhalla::tyr::actor_t> actor;
thread_local std::unique_ptr<std::string> response_str;
thread_local std::unique_ptr<std::string> error_str;

extern "C" int lotyr_init(char *config_path) {
  try {
    // Load the configuration
    std::string config_file(config_path);
    boost::property_tree::ptree config;
    rapidjson::read_json(config_file, config);

    // Initialize the actor
    actor = std::make_unique<valhalla::tyr::actor_t>(
        valhalla::tyr::actor_t(config));

    return 1;
  } catch (valhalla::valhalla_exception_t e) {
    error_str = std::make_unique<std::string>(e.message);
    return 0;
  } catch (...) {
    error_str = nullptr;
    return 0;
  }
}

extern "C" int lotyr_deinit(void) {
  try {
    actor = nullptr;

    return 1;
  } catch (valhalla::valhalla_exception_t e) {
    error_str = std::make_unique<std::string>(e.message);
    return 0;
  } catch (...) {
    error_str = nullptr;
    return 0;
  }
}

extern "C" const char *lotyr_route(char *request) {
  try {
    std::string request_str(request);
    response_str = std::make_unique<std::string>(actor->route(request_str));
    return response_str->c_str();
  } catch (valhalla::valhalla_exception_t e) {
    error_str = std::make_unique<std::string>(e.message);
    return NULL;
  } catch (...) {
    error_str = nullptr;
    return NULL;
  }
}

extern "C" const char *lotyr_error(void) {
  if (error_str)
    return error_str->c_str();
  else
    return NULL;
}
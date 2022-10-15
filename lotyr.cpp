#include <cstring>
#include <exception>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include <valhalla/baldr/rapidjson_utils.h>
#include <valhalla/tyr/actor.h>
#include <valhalla/worker.h>

#define _LOTYR_DLL_EXPORT
#include "lotyr.h"
#undef _LOTYR_DLL_EXPORT

struct lotyr_t {
  std::unique_ptr<valhalla::tyr::actor_t> actor;
};

struct lotyr_error_t {
  std::string message;
};

lotyr_error_t *lotyr_unknown_error() {
  lotyr_error_t *error = new lotyr_error_t;
  error->message = std::string("Unknown error");
  return error;
}

lotyr_error_t *
lotyr_valhalla_error(valhalla::valhalla_exception_t valhalla_error) {
  lotyr_error_t *error = new lotyr_error_t;
  error->message = valhalla_error.message;
  return error;
}

// TODO: make sure there are no memory leaks in the case of errors

extern "C" lotyr_error_t *lotyr_new(lotyr_t **lotyr_dest,
                                    const char *config_path) {
  try {
    // Load the configuration
    std::string config_file(config_path);
    boost::property_tree::ptree config;
    rapidjson::read_json(config_file, config);

    lotyr_t *lotyr = new lotyr_t;
    lotyr->actor = std::make_unique<valhalla::tyr::actor_t>(
        valhalla::tyr::actor_t(config));
    *lotyr_dest = lotyr;

    return nullptr;
  } catch (valhalla::valhalla_exception_t e) {
    lotyr_error_t *error = new lotyr_error_t;
    error->message = e.message;
    return error;
  } catch (...) { // TODO: better rapidjson error handling
    return lotyr_unknown_error();
  }
}

extern "C" lotyr_error_t *lotyr_free(lotyr_t *lotyr) {
  delete lotyr;

  return nullptr;
}

extern "C" lotyr_error_t *lotyr_route(lotyr_t *lotyr, const char *request,
                                      char **response) {
  try {
    std::string request_str(request);
    std::string response_str = lotyr->actor->route(request_str);
    *response = strdup(response_str.c_str());

    return nullptr;
  } catch (valhalla::valhalla_exception_t e) {
    return lotyr_valhalla_error(e);
  } catch (...) {
    return lotyr_unknown_error();
  }
}

extern "C" const char *lotyr_error_message(const lotyr_error_t *error) {
  if (error == nullptr)
    return "No error";

  return error->message.c_str();
}

extern "C" void lotyr_error_free(lotyr_error_t *error) { delete error; }
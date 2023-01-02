#include <cstring>
#include <exception>
#include <memory>
#include <string>

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

lotyr_error_t *lotyr_error(std::string message) {
  lotyr_error_t *error = new lotyr_error_t;
  error->message = message;
  return error;
}

lotyr_error_t *lotyr_unknown_error(std::exception &e) {
  std::string message("Unknown error (");
  message.append(typeid(e).name());
  message.append("): ");
  message.append(e.what());
  return lotyr_error(message);
}

lotyr_error_t *
lotyr_valhalla_error(valhalla::valhalla_exception_t &valhalla_error) {
  std::string message("Valhalla error: ");
  message.append(valhalla_error.message);
  return lotyr_error(message);
}

// TODO: make sure there are no memory leaks in the case of errors

extern "C" lotyr_error_t *lotyr_new(lotyr_t **lotyr_dest, const char *config) {
  try {
    // Parse the configuration
    boost::property_tree::ptree config_pt;
    rapidjson::Document config_doc;
    config_doc.Parse(config);

    if (config_doc.HasParseError()) {
      std::string message(
          "Failed to parse configuration: RapidJSON error code ");
      message.append(std::to_string(config_doc.GetParseError()));
      return lotyr_error(message);
    }

    if (config_doc.IsObject()) {
      rapidjson::add_object(
          const_cast<const rapidjson::Document *>(&config_doc)->GetObject(),
          config_pt);
    } else {
      return lotyr_error(std::string(
          "Failed to parse configuration: Configuration must be an object"));
    }

    lotyr_t *lotyr = new lotyr_t;
    lotyr->actor = std::make_unique<valhalla::tyr::actor_t>(
        valhalla::tyr::actor_t(config_pt));
    *lotyr_dest = lotyr;

    return nullptr;
  } catch (valhalla::valhalla_exception_t e) {
    return lotyr_valhalla_error(e);
  } catch (std::exception &e) {
    return lotyr_unknown_error(e);
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
  } catch (std::exception &e) {
    return lotyr_unknown_error(e);
  }
}

extern "C" const char *lotyr_error_message(const lotyr_error_t *error) {
  if (error == nullptr)
    return "No error";

  return error->message.c_str();
}

extern "C" void lotyr_error_free(lotyr_error_t *error) { delete error; }

#ifndef LOTYR_LOTYR_H_
#define LOTYR_LOTYR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lotyr_t lotyr_t;
typedef struct lotyr_error_t lotyr_error_t;

/// Creates a new routing engine context with the Valhalla configuration loaded
/// from` config_path`. Stores a pointer to the context in `lotyr`.
lotyr_error_t *lotyr_new(lotyr_t **lotyr, const char *config_path);

/// Frees the memory and resources associated with the given routing engine
/// context.
lotyr_error_t *lotyr_free(lotyr_t *lotyr);

/// Calculates a route described by `request`. It is the responsibility of the
/// library user to free the returned response string, which is stored into
/// `response` after a route has been found.
///
/// See the Valhalla API reference (linked below) for documentation on the
/// format of `request`.
/// https://valhalla.readthedocs.io/en/latest/api/turn-by-turn/api-reference/
lotyr_error_t *lotyr_route(lotyr_t *lotyr, const char *request, char **response);

/// Gets a human-readable error message representing the given error.
///
/// The returned string points to internal data of the given error; don't free
/// or modify it unless you want bad things to happen.
const char *lotyr_error_message(const lotyr_error_t *error);

/// Frees the memory associated with the given Lotyr error.
void lotyr_error_free(lotyr_error_t *error);

#ifdef __cplusplus
}
#endif

#endif // LOTYR_LOTYR_H_
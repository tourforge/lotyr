#ifndef LOTYR_LOTYR_H_
#define LOTYR_LOTYR_H_

#ifdef __cplusplus
extern "C" {
#endif

/// Initializes the library, loading the Valhalla configuration from
/// `config_path`.
///
/// Returns 0 on failue, and a nonzero value otherwise.
int lotyr_init(char *config_path);

/// Deinitializes the library.
///
/// Returns 0 on failure, and a nonzero value otherwise.
int lotyr_deinit(void);

/// Calculates a route described by `request`. DO NOT attempt to free the
/// returned string. The returned string will be kept alive until `route` is
/// called again, at which point the memory will be freed by the library.
///
/// Returns a `NULL` pointer on failure.
///
/// See the Valhalla API reference (linked below) for documentation on the
/// format of `request`.
/// https://valhalla.readthedocs.io/en/latest/api/turn-by-turn/api-reference/
const char *lotyr_route(char *request);

/// Gets the most recent error message, if any. The pointer returned by this function
/// will only be valid until another error occurs, so copy it before use.
const char *lotyr_error(void);

#ifdef __cplusplus
}
#endif

#endif // LOTYR_LOTYR_H_
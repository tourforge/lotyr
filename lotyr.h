#ifndef LOTYR_LOTYR_H_
#define LOTYR_LOTYR_H_

#ifdef __cplusplus
extern "C" {
#endif

/// Initializes the library, loading the Valhalla configuration from
/// `config_path`.
void init(char * config_path);

/// Deinitializes the library.
void deinit(void);

#ifdef __cplusplus
}
#endif

#endif  // LOTYR_LOTYR_H_
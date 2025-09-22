#include "s21_errno.h"
#include "s21_sprintf.h"
#include "s21_std.h"

char *s21_strerror(int errnum) {
  static const char *error_matrix[] = ERRORS;
  static char error_message[128];

  if (errnum < 0 || errnum > ERROR_COUNT) {
#if (defined(__linux__) && defined(__GLIBC__)) || defined(__APPLE__)
    s21_sprintf(error_message, "%s %d", UNKNOWN_ERROR, errnum);
#else
    s21_sprintf(error_message, "%s", UNKNOWN_ERROR);
#endif
  } else {
    s21_sprintf(error_message, "%s", error_matrix[errnum]);
  }

  return error_message;
}

#include "../include/s21_errno.h"
#include "../include/s21_sprintf.h"
#include "../include/s21_std.h"

char *s21_strerror(int errnum) {
  static const char *error_matrix[] = ERRORS;
  static char error_message[128];

  if (errnum < 0 || errnum > ERROR_COUNT) {
    s21_sprintf(error_message, "%s %d", UNKNOWN_ERROR, errnum);
  } else {
    s21_sprintf(error_message, "%s", error_matrix[errnum]);
  }

  return error_message;
}

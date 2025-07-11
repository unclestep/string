#ifndef S21_ERRNO_H
#define S21_ERRNO_H

#if defined(__APPLE__)
#define ERROR_COUNT 107
#define UNKNOWN_ERROR "Unknown error:"
#endif

#if defined(__linux__)
#define ERROR_COUNT 133
#define UNKNOWN_ERROR "Unknown error"
#endif

#endif

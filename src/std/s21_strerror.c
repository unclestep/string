#include "s21_sprintf.h"
#include "s21_std.h"

#if defined(__APPLE__)
#define ERROR_COUNT 107
#define UNKNOWN_ERROR "Unknown error:"
#define ERRORS                                                                 \
  {                                                                            \
    [0] = "Undefined error: 0", [1] = "Operation not permitted",               \
    [2] = "No such file or directory", [3] = "No such process",                \
    [4] = "Interrupted system call", [5] = "Input/output error",               \
    [6] = "Device not configured", [7] = "Argument list too long",             \
    [8] = "Exec format error", [9] = "Bad file descriptor",                    \
    [10] = "No child processes", [11] = "Resource deadlock avoided",           \
    [12] = "Cannot allocate memory", [13] = "Permission denied",               \
    [14] = "Bad address", [15] = "Block device required",                      \
    [16] = "Resource busy", [17] = "File exists", [18] = "Cross-device link",  \
    [19] = "Operation not supported by device", [20] = "Not a directory",      \
    [21] = "Is a directory", [22] = "Invalid argument",                        \
    [23] = "Too many open files in system", [24] = "Too many open files",      \
    [25] = "Inappropriate ioctl for device", [26] = "Text file busy",          \
    [27] = "File too large", [28] = "No space left on device",                 \
    [29] = "Illegal seek", [30] = "Read-only file system",                     \
    [31] = "Too many links", [32] = "Broken pipe",                             \
    [33] = "Numerical argument out of domain", [34] = "Result too large",      \
    [35] = "Resource temporarily unavailable",                                 \
    [36] = "Operation now in progress",                                        \
    [37] = "Operation already in progress",                                    \
    [38] = "Socket operation on non-socket",                                   \
    [39] = "Destination address required", [40] = "Message too long",          \
    [41] = "Protocol wrong type for socket", [42] = "Protocol not available",  \
    [43] = "Protocol not supported", [44] = "Socket type not supported",       \
    [45] = "Operation not supported", [46] = "Protocol family not supported",  \
    [47] = "Address family not supported by protocol family",                  \
    [48] = "Address already in use", [49] = "Can't assign requested address",  \
    [50] = "Network is down", [51] = "Network is unreachable",                 \
    [52] = "Network dropped connection on reset",                              \
    [53] = "Software caused connection abort",                                 \
    [54] = "Connection reset by peer", [55] = "No buffer space available",     \
    [56] = "Socket is already connected", [57] = "Socket is not connected",    \
    [58] = "Can't send after socket shutdown",                                 \
    [59] = "Too many references: can't splice", [60] = "Operation timed out",  \
    [61] = "Connection refused", [62] = "Too many levels of symbolic links",   \
    [63] = "File name too long", [64] = "Host is down",                        \
    [65] = "No route to host", [66] = "Directory not empty",                   \
    [67] = "Too many processes", [68] = "Too many users",                      \
    [69] = "Disc quota exceeded", [70] = "Stale NFS file handle",              \
    [71] = "Too many levels of remote in path", [72] = "RPC struct is bad",    \
    [73] = "RPC version wrong", [74] = "RPC prog. not avail",                  \
    [75] = "Program version wrong", [76] = "Bad procedure for program",        \
    [77] = "No locks available", [78] = "Function not implemented",            \
    [79] = "Inappropriate file type or format", [80] = "Authentication error", \
    [81] = "Need authenticator", [82] = "Device power is off",                 \
    [83] = "Device error", [84] = "Value too large to be stored in data type", \
    [85] = "Bad executable (or shared library)",                               \
    [86] = "Bad CPU type in executable",                                       \
    [87] = "Shared library version mismatch", [88] = "Malformed Mach-o file",  \
    [89] = "Operation canceled", [90] = "Identifier removed",                  \
    [91] = "No message of desired type", [92] = "Illegal byte sequence",       \
    [93] = "Attribute not found", [94] = "Bad message",                        \
    [95] = "EMULTIHOP (Reserved)", [96] = "No message available on STREAM",    \
    [97] = "ENOLINK (Reserved)", [98] = "No STREAM resources",                 \
    [99] = "Not a STREAM", [100] = "Protocol error",                           \
    [101] = "STREAM ioctl timeout",                                            \
    [102] = "Operation not supported on socket", [103] = "Policy not found",   \
    [104] = "State not recoverable", [105] = "Previous owner died",            \
    [106] = "Interface output queue is full",                                  \
    [107] = "Capabilities insufficient"                                        \
  }
#elif defined(__linux__) && defined(__GLIBC__)
#define ERROR_COUNT 133
#define UNKNOWN_ERROR "Unknown error"
#define ERRORS                                                                 \
  {                                                                            \
    [0] = "Success", [1] = "Operation not permitted",                          \
    [2] = "No such file or directory", [3] = "No such process",                \
    [4] = "Interrupted system call", [5] = "Input/output error",               \
    [6] = "No such device or address", [7] = "Argument list too long",         \
    [8] = "Exec format error", [9] = "Bad file descriptor",                    \
    [10] = "No child processes", [11] = "Resource temporarily unavailable",    \
    [12] = "Cannot allocate memory", [13] = "Permission denied",               \
    [14] = "Bad address", [15] = "Block device required",                      \
    [16] = "Device or resource busy", [17] = "File exists",                    \
    [18] = "Invalid cross-device link", [19] = "No such device",               \
    [20] = "Not a directory", [21] = "Is a directory",                         \
    [22] = "Invalid argument", [23] = "Too many open files in system",         \
    [24] = "Too many open files", [25] = "Inappropriate ioctl for device",     \
    [26] = "Text file busy", [27] = "File too large",                          \
    [28] = "No space left on device", [29] = "Illegal seek",                   \
    [30] = "Read-only file system", [31] = "Too many links",                   \
    [32] = "Broken pipe", [33] = "Numerical argument out of domain",           \
    [34] = "Numerical result out of range",                                    \
    [35] = "Resource deadlock avoided", [36] = "File name too long",           \
    [37] = "No locks available", [38] = "Function not implemented",            \
    [39] = "Directory not empty", [40] = "Too many levels of symbolic links",  \
    [41] = "Unknown error 41", [42] = "No message of desired type",            \
    [43] = "Identifier removed", [44] = "Channel number out of range",         \
    [45] = "Level 2 not synchronized", [46] = "Level 3 halted",                \
    [47] = "Level 3 reset", [48] = "Link number out of range",                 \
    [49] = "Protocol driver not attached",                                     \
    [50] = "No CSI structure available", [51] = "Level 2 halted",              \
    [52] = "Invalid exchange", [53] = "Invalid request descriptor",            \
    [54] = "Exchange full", [55] = "No anode", [56] = "Invalid request code",  \
    [57] = "Invalid slot", [58] = "Unknown error 58",                          \
    [59] = "Bad font file format", [60] = "Device not a stream",               \
    [61] = "No data available", [62] = "Timer expired",                        \
    [63] = "Out of streams resources", [64] = "Machine is not on the network", \
    [65] = "Package not installed", [66] = "Object is remote",                 \
    [67] = "Link has been severed", [68] = "Advertise error",                  \
    [69] = "Srmount error", [70] = "Communication error on send",              \
    [71] = "Protocol error", [72] = "Multihop attempted",                      \
    [73] = "RFS specific error", [74] = "Bad message",                         \
    [75] = "Value too large for defined data type",                            \
    [76] = "Name not unique on network",                                       \
    [77] = "File descriptor in bad state", [78] = "Remote address changed",    \
    [79] = "Can not access a needed shared library",                           \
    [80] = "Accessing a corrupted shared library",                             \
    [81] = ".lib section in a.out corrupted",                                  \
    [82] = "Attempting to link in too many shared libraries",                  \
    [83] = "Cannot exec a shared library directly",                            \
    [84] = "Invalid or incomplete multibyte or wide character",                \
    [85] = "Interrupted system call should be restarted",                      \
    [86] = "Streams pipe error", [87] = "Too many users",                      \
    [88] = "Socket operation on non-socket",                                   \
    [89] = "Destination address required", [90] = "Message too long",          \
    [91] = "Protocol wrong type for socket", [92] = "Protocol not available",  \
    [93] = "Protocol not supported", [94] = "Socket type not supported",       \
    [95] = "Operation not supported", [96] = "Protocol family not supported",  \
    [97] = "Address family not supported by protocol",                         \
    [98] = "Address already in use", [99] = "Cannot assign requested address", \
    [100] = "Network is down", [101] = "Network is unreachable",               \
    [102] = "Network dropped connection on reset",                             \
    [103] = "Software caused connection abort",                                \
    [104] = "Connection reset by peer", [105] = "No buffer space available",   \
    [106] = "Transport endpoint is already connected",                         \
    [107] = "Transport endpoint is not connected",                             \
    [108] = "Cannot send after transport endpoint shutdown",                   \
    [109] = "Too many references: cannot splice",                              \
    [110] = "Connection timed out", [111] = "Connection refused",              \
    [112] = "Host is down", [113] = "No route to host",                        \
    [114] = "Operation already in progress",                                   \
    [115] = "Operation now in progress", [116] = "Stale file handle",          \
    [117] = "Structure needs cleaning", [118] = "Not a XENIX named type file", \
    [119] = "No XENIX semaphores available", [120] = "Is a named type file",   \
    [121] = "Remote I/O error", [122] = "Disk quota exceeded",                 \
    [123] = "No medium found", [124] = "Wrong medium type",                    \
    [125] = "Operation canceled", [126] = "Required key not available",        \
    [127] = "Key has expired", [128] = "Key has been revoked",                 \
    [129] = "Key was rejected by service", [130] = "Owner died",               \
    [131] = "State not recoverable",                                           \
    [132] = "Operation not possible due to RF-kill",                           \
    [133] = "Memory page has hardware error"                                   \
  }
#else
#define ERROR_COUNT 131
#define UNKNOWN_ERROR "No error information"
#define ERRORS                                                                 \
  {                                                                            \
    [0] = "No error information", [1] = "Operation not permitted",             \
    [2] = "No such file or directory", [3] = "No such process",                \
    [4] = "Interrupted system call", [5] = "I/O error",                        \
    [6] = "No such device or address", [7] = "Argument list too long",         \
    [8] = "Exec format error", [9] = "Bad file descriptor",                    \
    [10] = "No child process", [11] = "Resource temporarily unavailable",      \
    [12] = "Out of memory", [13] = "Permission denied", [14] = "Bad address",  \
    [15] = "Block device required", [16] = "Resource busy",                    \
    [17] = "File exists", [18] = "Cross-device link", [19] = "No such device", \
    [20] = "Not a directory", [21] = "Is a directory",                         \
    [22] = "Invalid argument", [23] = "Too many open files in system",         \
    [24] = "No file descriptors available", [25] = "Not a tty",                \
    [26] = "Text file busy", [27] = "File too large",                          \
    [28] = "No space left on device", [29] = "Invalid seek",                   \
    [30] = "Read-only file system", [31] = "Too many links",                   \
    [32] = "Broken pipe", [33] = "Domain error",                               \
    [34] = "Result not representable", [35] = "Resource deadlock would occur", \
    [36] = "Filename too long", [37] = "No locks available",                   \
    [38] = "Function not implemented", [39] = "Directory not empty",           \
    [40] = "Symbolic link loop", [41] = "No error information",                \
    [42] = "No message of desired type", [43] = "Identifier removed",          \
    [44] = "No error information", [45] = "No error information",              \
    [46] = "No error information", [47] = "No error information",              \
    [48] = "No error information", [49] = "No error information",              \
    [50] = "No error information", [51] = "No error information",              \
    [52] = "No error information", [53] = "No error information",              \
    [54] = "No error information", [55] = "No error information",              \
    [56] = "No error information", [57] = "No error information",              \
    [58] = "No error information", [59] = "No error information",              \
    [60] = "Device not a stream", [61] = "No data available",                  \
    [62] = "Device timeout", [63] = "Out of streams resources",                \
    [64] = "No error information", [65] = "No error information",              \
    [66] = "No error information", [67] = "Link has been severed",             \
    [68] = "No error information", [69] = "No error information",              \
    [70] = "No error information", [71] = "Protocol error",                    \
    [72] = "Multihop attempted", [73] = "No error information",                \
    [74] = "Bad message", [75] = "Value too large for data type",              \
    [76] = "No error information", [77] = "File descriptor in bad state",      \
    [78] = "No error information", [79] = "No error information",              \
    [80] = "No error information", [81] = "No error information",              \
    [82] = "No error information", [83] = "No error information",              \
    [84] = "Illegal byte sequence", [85] = "No error information",             \
    [86] = "No error information", [87] = "No error information",              \
    [88] = "Not a socket", [89] = "Destination address required",              \
    [90] = "Message too large", [91] = "Protocol wrong type for socket",       \
    [92] = "Protocol not available", [93] = "Protocol not supported",          \
    [94] = "Socket type not supported", [95] = "Not supported",                \
    [96] = "Protocol family not supported",                                    \
    [97] = "Address family not supported by protocol",                         \
    [98] = "Address in use", [99] = "Address not available",                   \
    [100] = "Network is down", [101] = "Network unreachable",                  \
    [102] = "Connection reset by network", [103] = "Connection aborted",       \
    [104] = "Connection reset by peer", [105] = "No buffer space available",   \
    [106] = "Socket is connected", [107] = "Socket not connected",             \
    [108] = "Cannot send after socket shutdown",                               \
    [109] = "No error information", [110] = "Operation timed out",             \
    [111] = "Connection refused", [112] = "Host is down",                      \
    [113] = "Host is unreachable", [114] = "Operation already in progress",    \
    [115] = "Operation in progress", [116] = "Stale file handle",              \
    [117] = "No error information", [118] = "No error information",            \
    [119] = "No error information", [120] = "No error information",            \
    [121] = "Remote I/O error", [122] = "Quota exceeded",                      \
    [123] = "No medium found", [124] = "Wrong medium type",                    \
    [125] = "Operation canceled", [126] = "Required key not available",        \
    [127] = "Key has expired", [128] = "Key has been revoked",                 \
    [129] = "Key was rejected by service", [130] = "Previous owner died",      \
    [131] = "State not recoverable"                                            \
  }
#endif

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

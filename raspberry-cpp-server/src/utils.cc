#include <iostream>
#include "utils.h"

namespace utils {

void err(const char* err_msg) {
  perror(err_msg);
  exit(EXIT_FAILURE);
}

}

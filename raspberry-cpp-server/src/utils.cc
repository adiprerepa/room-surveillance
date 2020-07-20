//
// Created by aditya on 7/19/20.
//

#include <iostream>
#include <wait.h>
#include "utils.h"

namespace utils {

    void err(const char* err_msg) {
        perror(err_msg);
        exit(EXIT_FAILURE);
    }

    void sigchld_handler(int s) {
        while(waitpid(-1, nullptr, WNOHANG) > 0);
    }

}

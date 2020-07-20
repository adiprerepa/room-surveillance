//
// Created by aditya on 7/19/20.
//
#pragma once
#ifndef RPICPPSERVER_UTILS_H
#define RPICPPSERVER_UTILS_H

namespace utils {

    void err(const char* err_msg);

    void sigchld_handler(int s);

} // namespace utils

#endif //RPICPPSERVER_UTILS_H

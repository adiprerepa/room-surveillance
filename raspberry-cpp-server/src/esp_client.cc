//
// Created by aditya on 7/19/20.
//

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include "utils.h"

namespace esp {

    // returns the fd for the socket listener
    int listen_esp8266(int port, int queue_conns) {
        int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
        if (fd_listen == -1) {
            utils::err("unable to create socket fd");
        }
        int sock_opt = SO_REUSEADDR;
        if (setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(sock_opt)) == -1) {
            utils::err("unable to set socket opts");
        }
        struct sockaddr_in server{};
        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = htons(INADDR_ANY);
        if (bind(fd_listen, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
            utils::err("unable to bind");
        }
        if (listen(fd_listen, queue_conns) == -1) {
            utils::err("unable to start listening");
        }
        // collect dead processes
        struct sigaction sig_action{};
        sig_action.sa_handler = utils::sigchld_handler;
        sigemptyset(&sig_action.sa_mask);
        sig_action.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sig_action, nullptr) == -1) {
            utils::err("unable to set action for sig");
        }
        return fd_listen;
    }

}

//
// Created by aditya on 7/19/20.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "proto/activity_interface.pb.h"
#include "esp_client.h"

const int port = 3570;
const int max_data_recv = 4096;

using std::cout;
using std::endl;
using std::string;

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    int fd_listen = esp::listen_esp8266(port, 10);
    cout << "listening on port " << port << " for connections..." << endl;
    while(true) {
        struct sockaddr_in client{};
        char buf[max_data_recv];
        socklen_t sin_size = sizeof(struct sockaddr_in);
        int fd_connect = accept(fd_listen, (struct sockaddr *)&client, &sin_size);
        int num_bytes = recv(fd_connect, buf, max_data_recv, 0);
        buf[num_bytes] = '\0';
        string recv_str = buf;
        cout << "got connection & message from " << inet_ntoa(client.sin_addr) << endl;
        Esp8266Alert::AlertThresholdCross alert;
        alert.ParseFromString(recv_str);
        cout << alert.crossed_thresh() << endl;
    }
}

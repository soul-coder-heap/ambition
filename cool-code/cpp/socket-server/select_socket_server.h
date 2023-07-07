#ifndef SELECT_SOCKET_SERVER_H
#define SELECT_SOCKET_SERVER_H
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const int MAX_CLIENTS = 5;

int select_run() {
    int serverSocket, clientSockets[MAX_CLIENTS], maxClientSocket, activity, i, valread, sd;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    fd_set readfds;

    // 创建服务器套接字
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器套接字选项
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(3000);

    // 绑定服务器套接字到指定地址和端口
    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(serverSocket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // 初始化客户端套接字集合和最大套接字值
    for (i = 0; i < MAX_CLIENTS; i++) {
        clientSockets[i] = 0;
    }
    maxClientSocket = serverSocket;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);

        // 添加客户端套接字到集合
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = clientSockets[i];
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }
            if (sd > maxClientSocket) {
                maxClientSocket = sd;
            }
        }

        // 监听套接字集合的活动
        activity = select(maxClientSocket + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            perror("select error");
        }

        // 处理连接请求
        if (FD_ISSET(serverSocket, &readfds)) {
            int newSocket;
            socklen_t clientaddrlen = sizeof(address);;
            if ((newSocket = accept(serverSocket, (struct sockaddr *)&address, &clientaddrlen)) < 0) {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }
            struct sockaddr_in clientAddress;
            socklen_t clientAddressLength = sizeof(clientAddress);

            if (getpeername(newSocket, (struct sockaddr*)&clientAddress, &clientAddressLength) == 0) {
                char clientIP[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
                int clientPort = ntohs(clientAddress.sin_port);

                printf("Client IP: %s\n", clientIP);
                printf("Client Port: %d\n", clientPort);
            } else {
                perror("getpeername failed");
                exit(EXIT_FAILURE);
            }
            // 将新客户端套接字添加到数组中
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (clientSockets[i] == 0) {
                    clientSockets[i] = newSocket;
                    break;
                }
            }
        }

        // 处理客户端消息
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = clientSockets[i];
            if (FD_ISSET(sd, &readfds)) {
                if ((valread = read(sd, buffer, 1024)) == 0) {
                    // 客户端关闭连接
                    std::cout <<"valread : "<<valread<< std::endl;
                    close(sd);
                    clientSockets[i] = 0;
                }
                else {
                    // 回复客户端消息
                    std::cout <<"valread : "<<valread<<", info : "<<buffer<<std::endl;
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }

    return 0;
}

#endif // SELECT_SOCKET_SERVER_H

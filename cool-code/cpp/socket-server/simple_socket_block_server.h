#ifndef SIMPLE_SOCKET_BLOCK_SERVER_H
#define SIMPLE_SOCKET_BLOCK_SERVER_H
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int block_server() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket failed");
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(3000);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("bind failed");
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("listen failed");
        close(serverSocket);
        return 1;
    }

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            perror("accept failed");
            continue;
        }

        // 阻塞IO，在此处等待读取数据，直到客户端发送数据后才会继续执行
        char buffer[1024];
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read failed");
            close(clientSocket);
            continue;
        }
        buffer[bytesRead - 1] = '\0';
        // 处理接收到的数据
        std::cout << "Received message: " << buffer << ", len size : "<<strlen(buffer)<<", byteRead : "<<bytesRead<< std::endl;
        send(clientSocket, buffer, bytesRead, 0);
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}

#endif // SIMPLE_SOCKET_BLOCK_SERVER_H

#ifndef SIMPLE_SOCKET_NOBLOCK_SERVER_H
#define SIMPLE_SOCKET_NOBLOCK_SERVER_H
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int noblock_server() {
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

    // 将服务器套接字设置为非阻塞模式
    int flags = fcntl(serverSocket, F_GETFL, 0);
    fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

    std::cout <<"wait client..."<< std::endl;
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        //std::cout <<"client socket : "<<clientSocket<< std::endl;
        if (clientSocket == -1) {
            // 非阻塞IO，如果没有新的客户端连接，accept函数会立即返回-1
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            } else {
                perror("accept failed");
                break;
            }
        }

        // 非阻塞IO，在此处读取数据，如果没有数据可读，read函数会立即返回-1
        char buffer[1024];
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // 没有数据可读，继续处理其他任务
                close(clientSocket);
                continue;
            } else {
                perror("read failed");
                close(clientSocket);
                break;
            }
        }

        // 处理接收到的数据
        std::cout << "Received message: " << buffer << std::endl;

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}

#endif // SIMPLE_SOCKET_NOBLOCK_SERVER_H

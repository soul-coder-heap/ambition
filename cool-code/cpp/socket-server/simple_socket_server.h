#ifndef SIMPLE_SOCKET_SERVER_H
#define SIMPLE_SOCKET_SERVER_H
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>

int simple_run(int argc, char *argv[])
{

    std::cout <<"server *:3000 start."<< std::endl;
    //1.创建监听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        std::cerr <<"reate listen socket error."<< std::endl;
        return -1;
    }
    //2.初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if(bind(listenfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) == -1){
        std::cerr <<"bind listen socket error."<< std::endl;
        return -1;
    }
    //3.启动监听
    if(listen(listenfd, SOMAXCONN) == -1){
        std::cerr <<"listen error."<< std::endl;
        return -1;
    }
    while(true){
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        //4.接受客户端的连接
        int clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientaddrlen);
        if(clientfd != -1){
            char recvbuf[1025] = {0};
#if 1
            bool clientConnected = true;
            int count = 0;
            while (clientConnected) {
                // 5. 从客户端获取数据
                std::cout <<"block recv..."<< std::endl;
                int ret = recv(clientfd, recvbuf, 1024, 0);
                if (ret > 0) {
                    count++;
                    std::cout << "Recv data from client, data size: " << ret << std::endl;
                    // 6. 将收到的数据返回给客户端
                    int clientState = 0;
                    socklen_t stateLen = sizeof(clientState);
                    if (getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &clientState, &stateLen) < 0) {
                        std::cerr << "Get client state failed." << std::endl;
                        clientConnected = false;
                    } else if (clientState != 0) {
                        std::cout << "Client disconnected." << std::endl;
                        clientConnected = false;
                    } else {
                        ret = send(clientfd, recvbuf, strlen(recvbuf), 0);
                        if (ret != strlen(recvbuf)) {
                            std::cerr << "Send data error." << std::endl;
                            clientConnected = false;
                        } else {
                            std::cout << "Send data to client successfully, data size: " << ret << std::endl;
                        }
                    }
                } else if (ret == 0) {
                    std::cout << "Client disconnected." << std::endl;
                    clientConnected = false;
                } else {
                    std::cerr << "Recv data error. " <<ret<< std::endl;
                    clientConnected = false;
                }
                memset(recvbuf, 0, sizeof(recvbuf));
            }

#else
            //5.从客户端获取数据
            int ret = recv(clientfd, recvbuf, 32, 0);
            if(ret > 0){
                std::cout <<"recv data from client, data : "<<recvbuf<<std::endl;
                //6.将收到的数据返回给客户端
                ret = send(clientfd, recvbuf, strlen(recvbuf), 0);
                if(ret != strlen(recvbuf)){
                    std::cerr <<"send data error."<< std::endl;
                }else{
                    std::cout <<"send data to client cuccessfully, data : "<<recvbuf<<std::endl;
                }
            }else{
                std::cerr <<"recv data error."<< std::endl;
            }
#endif
            std::cout <<"收发 count : "<< count<<std::endl;
            close(clientfd);
        }
    }
    // 7.关闭监听
    close(listenfd);
    return 0;
}

#endif // SIMPLE_SOCKET_SERVER_H

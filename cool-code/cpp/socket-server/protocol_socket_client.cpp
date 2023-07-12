#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

// 示例结构体
typedef struct {
    int id;
    char name[20];
    float score;
} Student;


typedef struct {
    int frameNumber;       // 帧号
    size_t frameSize;      // 帧数据大小
    unsigned char* frameData; // 帧数据
} VideoFrame;


// 定义协议的消息类型
enum MessageType {
    TYPE_STUDENT = 1, // 学生类型
    TYPE_VIDEO = 2,   // 视频类型
    // 可以定义其他类型...
};

// 协议的消息头结构
typedef struct {
    enum MessageType type;
    size_t dataSize;
} MessageHeader;

// 序列化结构体到字节流
void serializeStruct(const void* data, size_t dataSize, char* buffer, enum MessageType type) {
    MessageHeader header;
    header.type = type;
    header.dataSize = dataSize;

    // 将消息头拷贝到缓冲区
    memcpy(buffer, &header, sizeof(MessageHeader));

    // 将结构体数据拷贝到缓冲区
    memcpy(buffer + sizeof(MessageHeader), data, dataSize);
}

// 反序列化字节流到结构体
void deserializeHeaderStruct(const char* buffer, size_t *dataSize, enum MessageType* type) {
    MessageHeader header;
    memcpy(&header, buffer, sizeof(MessageHeader));

    // 提取消息类型和数据大小
    *type = header.type;
    *dataSize = header.dataSize; 
}

// 反序列化字节流到结构体
void deserializeStudentStruct(const char* buffer, void* data, size_t dataSize, size_t recvSize) {
    
    // 检查数据大小是否一致
    std::cout <<"recv size : "<<recvSize<<", datasize : "<< dataSize<<std::endl;

    if (recvSize != dataSize) {
        fprintf(stderr, "Received data size doesn't match the expected size.\n");
        return;
    }

    // 将数据拷贝到结构体
    memcpy(data, buffer, dataSize);
}

// 创建TCP服务器
int createServer(int port) {
    int serverSocket;
    struct sockaddr_in serverAddress;

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // 绑定套接字到指定端口
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(serverSocket, 1) == -1) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    return serverSocket;
}

// 创建TCP客户端
int createClient(const char* serverIP, int port) {
    int clientSocket;
    struct sockaddr_in serverAddress;

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);
    serverAddress.sin_port = htons(port);

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }

    return clientSocket;
}

// 服务器接收数据
void receiveData(int clientSocket) {
    char buffer[sizeof(MessageHeader) + sizeof(Student)];

    // 接收消息头
    if (recv(clientSocket, buffer, sizeof(MessageHeader), 0) == -1) {
        perror("Failed to receive message header");
        return;
    }

    enum MessageType type;
    size_t dataSize;
    deserializeHeaderStruct(buffer, &dataSize, &type);

    // 根据消息类型处理数据
    if (type == TYPE_STUDENT) {
        // 接收学生结构体数据
        size_t recv_size =  recv(clientSocket, buffer, dataSize, 0);
        if ( recv_size == -1) {
            perror("Failed to receive student data");
            return;
        }

        Student student;
        deserializeStudentStruct(buffer, &student, sizeof(Student), recv_size);

        // 处理接收到的学生数据
        printf("Received student data:\n");
        printf("ID: %d\n", student.id);
        printf("Name: %s\n", student.name);
        printf("Score: %.2f\n", student.score);
    } else {
        printf("Received unknown data type.\n");
    }
}

// 客户端发送数据
void sendData(int serverSocket, const void* data, size_t dataSize, enum MessageType type) {
    char buffer[sizeof(MessageHeader) + dataSize];

    // 序列化数据
    serializeStruct(data, dataSize, buffer, type);

    // 发送数据到服务器
    if (send(serverSocket, buffer, sizeof(MessageHeader) + dataSize, 0) == -1) {
        perror("Failed to send data");
        return;
    }
}
int main() {
    int port = 12345;
    const char* serverIP = "127.0.0.1";

    // 创建客户端
    int clientSocket = createClient(serverIP, port);

    // 准备要发送的结构体数据
    Student student = { 1, "John Doe", 95.5 };

    // 客户端发送数据
    std::cout <<"sizeof(Student) : "<<sizeof(student)<< std::endl;
    printf("Send student data:\n");
    printf("ID: %d\n", student.id);
    printf("Name: %s\n", student.name);
    printf("Score: %.2f\n", student.score);
    sendData(clientSocket, &student, sizeof(Student), TYPE_STUDENT);

    // 关闭套接字
    close(clientSocket);

    return 0;
}


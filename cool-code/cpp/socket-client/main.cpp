#include <iostream>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3000
#define TEST_COUNT 100

void testNetworkLatency() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    // 获取发送缓冲区大小限制
    int sendBufferSize;
    socklen_t bufferSizeLen = sizeof(sendBufferSize);
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendBufferSize, &bufferSizeLen) == -1) {
        std::cerr << "Failed to get send buffer size" << std::endl;
        close(sock);
        return;
    }

    std::cout << "Send Buffer Size: " << sendBufferSize << " bytes" << std::endl;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        close(sock);
        return;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return;
    }

    char message[BUFFER_SIZE];
    memset(message, 'A', BUFFER_SIZE);  // 填充消息
    std::vector<double> latencies;

    for (int i = 0; i < TEST_COUNT; ++i) {
        // 记录发送时间
        auto startTime = std::chrono::system_clock::now();
        if (send(sock, message, BUFFER_SIZE, 0) < 0) {
            std::cerr << "Send failed" << std::endl;
            close(sock);
            return;
        }

        // 接收响应消息及记录接收时间
        char response[BUFFER_SIZE];
        if (recv(sock, response, BUFFER_SIZE, 0) < 0) {
            std::cerr << "Receive failed" << std::endl;
            close(sock);
            return;
        }
        auto endTime = std::chrono::system_clock::now();

        // 计算延迟时间
        std::chrono::duration<double> elapsedSeconds = endTime - startTime;
        double latency = elapsedSeconds.count() * 1000;  // 转换为毫秒

        std::cout << "Test " << i+1 << ": Network Latency: " << latency << " ms" << std::endl;

        latencies.push_back(latency);
    }

    double averageLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
    double minLatency = *std::min_element(latencies.begin(), latencies.end());
    double maxLatency = *std::max_element(latencies.begin(), latencies.end());
    double speed = TEST_COUNT * BUFFER_SIZE / std::accumulate(latencies.begin(), latencies.end(), 0.0);
    std::cout << "Average Latency: " << averageLatency << " ms" << std::endl;
    std::cout << "Min Latency: " << minLatency << " ms" << std::endl;
    std::cout << "Max Latency: " << maxLatency << " ms" << std::endl;

    std::cout << "Average Transmission Speed: " << speed << " bytes/second" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    close(sock);
}

int main() {
    testNetworkLatency();
    return 0;
}


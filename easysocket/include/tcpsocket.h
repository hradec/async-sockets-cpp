#ifndef FDR_TCPSOCKET_H
#define FDR_TCPSOCKET_H

#include <DllHelper.h>

#include <basesocket.h>
#include <string>
#include <functional>
#include <thread>

constexpr uint16_t BUFFER_SIZE = 0xFFFF;

class EASYSOCKET_API TCPSocket : public BaseSocket
{
public:
    // Event Listeners:
    #ifdef EASYSOCKET_RECV_BIN
        std::function<void(char *msg,unsigned long long s)> onMessageReceived = [](char *msg, unsigned long long s) { (void)(msg);s=0;  };
    #else
        std::function<void(std::string)> onMessageReceived = [](std::string msg) { FDR_UNUSED(msg) };
    #endif
    std::function<void()> onSocketClosed = [](){};

    explicit TCPSocket(FDR_ON_ERROR, int socketId = -1);

    int Send(std::string message);
    int Send(const char *bytes, size_t byteslength);

    void Connect(std::string ipv4, uint16_t port, std::function<void()> onConnected = [](){}, FDR_ON_ERROR);
    void Connect(uint32_t IPv4, uint16_t port, std::function<void()> onConnected = [](){}, FDR_ON_ERROR);

    void Listen();

    void setAddressStruct(sockaddr_in addr);

private:
    static void Receive(TCPSocket *socket);
};

#endif

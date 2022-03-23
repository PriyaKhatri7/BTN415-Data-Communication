#include <iostream>
#include <string>
#include <istream>
#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Could not start DLLs" << std::endl;
        return 0;
    }

    SOCKET ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    //Part A: to connect to server
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(27030); //server port (other ones is it doesn't work is 27020 or 2010
    //SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    SvrAddr.sin_addr.s_addr = inet_addr("159.203.26.94");
    if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
        std::cout << "Failed to connect to server" << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

    //Part B: client to transmit messages with spaces
    while (ClientSocket) //Part C: to keep trasmiting messages to the server and receiving feedback
    {
        std::string TxBuffer = {}; //128[] take out and changed to string
        std::cout << "Enter a String to transmit" << std::endl;
        std::getline(std::cin, TxBuffer); //added getline to extract message
        send(ClientSocket, TxBuffer.c_str(), sizeof(TxBuffer), 0); // added c_str()

        char RxBuffer[128] = {};
        recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
        std::cout << "Response: " << RxBuffer << std::endl;

        if (TxBuffer == "[q]")
        {
            return 0; //exit the program
        }
    }
        closesocket(ClientSocket);
        WSACleanup();
    
    return 0;
    
}
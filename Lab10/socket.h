#pragma once
#include "socket.h"
#include <string>
#include <iostream>
#include <windows.networking.sockets.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER_SIZE 512


struct new_packet {
    char number;
    unsigned char urg : 1;
    unsigned char ack : 1;
    unsigned char psh : 1;
    unsigned char rst : 1;
    unsigned char syn : 1;
    unsigned char fin : 1;
    unsigned char : 2; //padding
    unsigned int size;
    char* data;
    unsigned char crc;
    unsigned int checksum;
};

struct serialized_packet {
    char* data;
    int length;
};

//void display(unsigned char byte);
unsigned char calculate_new_packet_crc(new_packet my_packet);
unsigned int calculate_new_packet_checksum(new_packet my_packet);

//packet create_packet();
serialized_packet new_packet_serializer(new_packet); //make new
new_packet new_packet_deserializer(char* serialized_packet); //make new

class Node {
public:
    static bool dlls_started;
    static int num_nodes;
    std::string ip;
    std::string role;
    std::string protocol;
    int port;
    SOCKET active_socket;
public:
    Node();
    Node(std::string ip, int port);
    ~Node();
    void start_dlls() const;
    bool create_socket();
    void display_info() const;
};

class Server_TCP : public Node {
private:
    SOCKET client_socket;
public:
    Server_TCP();
    Server_TCP(std::string ip, int port);
    ~Server_TCP();
    bool bind_socket();
    bool listen_for_connections();
    bool accept_connection();
    int send_message(std::string message);
    int send_new_packet(new_packet message); //new for client to server
    int receive_message(std::string& message);
    int receive_new_packet(new_packet& my_packet); //new_packet
    void close_connection();
};

class Client_TCP : public Node {
public:
    Client_TCP();
    bool connect_socket(std::string ip, int port);
    int send_message(std::string message);
    int send_new_packet(new_packet message);
    int receive_message(std::string& message);
    int receive_new_packet(new_packet& my_packet);
};

class Client_UDP : public Node {
public:
    Client_UDP();
    int send_message(std::string message, std::string ip, int port);
    struct sockaddr_in receive_message(std::string& message);
};

class Server_UDP : public Node {
public:
    Server_UDP();
    Server_UDP(std::string ip, int port);
    bool bind_socket();
    int send_message(std::string message, std::string ip, int port);
    struct sockaddr_in receive_message(std::string& message);
};
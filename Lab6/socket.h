//Name: Priya Khatri | Stu#: 110149176 | Email: pkhatri4@myseneca.ca
#include <string>
#include <iostream>
#include <windows.networking.sockets.h>

class Node
{
public:
	static bool dlls_started;
	static int num_nodes;
	std::string ip;
	std::string role;
	std::string protocol;
	int port;
	SOCKET active_socket;

	Node();
	Node(std::string ip, int port);
	~Node();
	void start_dlls() const;
	bool create_socket();
	void display_info() const;
};

class Server_TCP : public Node
{
	SOCKET client_socket;
public:
	Server_TCP();
	Server_TCP(std::string ip, int port);
	~Server_TCP();
	bool bind_socket();
	bool listen_for_connections();
	bool accept_connection();
	int send_message(std::string message);
	int receive_message(std::string& message);
	void close_connection();
};

class Client_TCP : public Node
{
public:
	Client_TCP();
	bool connect_socket(std::string ip, int port);
	int send_message(std::string message);
	int receive_message(std::string& message);
};

class Server_UDP : public Node
{
public:
	Server_UDP();
	Server_UDP(std::string ip, int port);
	bool bind_socket();
	int send_message(std::string message, std::string ip, int port);
	struct sockaddr_in recieve_message(std::string& message);
};

class Client_UDP : public Node
{
public:
	Client_UDP();
	int send_message(std::string message, std::string ip, int port);
	struct sockaddr_in recieve_message(std::string& message);
};
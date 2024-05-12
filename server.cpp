#define _WINSOCK_DEPRECATED_NO_WARNINGS
// #pragma comment(lib, "ws2_32.lib") // won't work for non visual compilers
#include <iostream>
#include <winsock2.h>
#include <string>
#include <fstream>

using namespace std;

string getHtmlCode()
{
	ifstream file("index.html");
	cout << "Reading index file" << endl;
	if (!file.is_open())
	{
		cerr << "Unable to open file" << endl;
		return "<html><head><title>Failed</title></head><body><h1>Failed to parse html</h1></body></html>";
	}

	string content;
	string line;

	while (getline(file, line))
	{
		content += line; // Append current line to the content string
		content += '\n'; // Append newline character
	}

	file.close(); // Close the file
	cout << "Reading file complete: " << content << endl;
	return content;
};

int main()
{
	cout << "Attempting to create a webserver" << endl;

	SOCKET wsocket;
	SOCKET new_wsocket;
	WSADATA wsaData;
	struct sockaddr_in server;
	int server_len;
	int BUFFER_SIZE = 37020;

	// initialize
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Couldn't start socket" << endl;
	}

	// create socket
	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET)
	{
		cerr << "Couldn't create socket" << endl;
	}

	// bind socket to address

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8080);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR *)&server, server_len) != 0)
	{
		cout << "Couldn't bind to address" << endl;
	}

	// listen to address

	if (listen(wsocket, 20) != 0)
	{
		cout << "Couldn't listen to address" << endl;
	}

	cout << "Listen to address 127.0.0.1:8080" << endl;

	int bytes = 0;
	while (true)
	{

		new_wsocket = accept(wsocket, (SOCKADDR *)&server, &server_len);
		if (new_wsocket == INVALID_SOCKET)
		{
			cout << "Couldn't connect to server";
		}

		// read  connection
		char buff[30720] = {0};
		bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
		if (bytes < 0)
		{
			cout << "Couldn't read connection";
		}

		// response received
		string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
		string response = getHtmlCode();
		serverMessage.append(to_string(response.size()));
		serverMessage.append("\n\n");
		serverMessage.append(response);

		int bytesSent = 0;
		int totalBytesSent = 0;

		while (totalBytesSent < serverMessage.size())
		{
			bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
			if (bytesSent < 0)
			{
				cout << "Couldn't send " << totalBytesSent << endl;
			}

			totalBytesSent += bytesSent;
		}

		cout << "Total bytes sent: " << totalBytesSent << endl;

		closesocket(new_wsocket);
	}
	closesocket(wsocket);
	WSACleanup();
	return 0;
}
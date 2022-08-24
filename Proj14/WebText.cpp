#include "WebText.h"

#include <iostream>
#include <string>

WebText::WebText(std::string siteLink)
{
	link = siteLink;

	char ln[1024];
	strcpy_s(ln, siteLink.c_str());

	connected = true;

	if (SDLNet_ResolveHost(&ip, ln, 80) < 0)
	{
		std::cout << "Failed to net_resolveHost() : " << SDLNet_GetError() << "\n";

		connected = false;
	}
}

std::string WebText::get(std::string linkPath)
{
	std::string full;

	char cmd[1024];

	strcpy_s(cmd, "GET ");
	strcat_s(cmd, linkPath.c_str());
	strcat_s(cmd, " HTTP/1.1\r\nHost: ");
	strcat_s(cmd, link.c_str());
	strcat_s(cmd, "\r\n\r\n");

	if (connected)
	{
		client = SDLNet_TCP_Open(&ip);

		SDLNet_SocketSet sSet;
		sSet = SDLNet_AllocSocketSet(3);
		SDLNet_TCP_AddSocket(sSet, client);
		SDLNet_TCP_Send(client, cmd, strlen(cmd));

		char text[1024];
		char oldText[1024];

		int count = 1;
		while (count > 0)
		{
			count = 0;

			// recv causes blocking if timeout not closed
			if (SDLNet_CheckSockets(sSet, 5000) > 0)
			{
				count = SDLNet_TCP_Recv(client, text, 1024);
				if (count <= 0)
				{
					std::cout << "Possible error detected...\n";
					break;
				}
				else full += text + '\n';
			}

		}

		SDLNet_TCP_Close(client);
	}
	else
	{
		return "Could not connect.\n";
	}

	return full;
}

WebText::~WebText()
{

}

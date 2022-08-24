#pragma once

#include "item.h"

class WebText : public Item
{
public:
	WebText(std::string siteLink);
	~WebText();

	std::string get(std::string wholeLink);

private:
	std::string link, cmd;

	IPaddress ip;
	TCPsocket client;

	bool connected;
};

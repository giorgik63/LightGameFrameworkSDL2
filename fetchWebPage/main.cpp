//-------------------------------------------------
//
//   Demo: fetchWebPage
//
//-------------------------------------------------

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_net.h"

#include "item.h"

#include <iostream>

int main(int argc, char* argv[]) 
{
	if (!itemInit())
	{
		std::cout << "Error to init!" << std::endl;
		return 1;
	}

	webText cppFetch("cplusplus.com");
	std::string content = cppFetch.get("/reference/string/string/");

	webText fetch("www.google.com");
	content = fetch.get("/");

	// this defaults to an https page, which seems to be a problem for SDL2_net
	// maybe it's my configuration?
	//fetch("gutenberg.org");
	//content = fetch.get("/");

	webText ducky("duckduckgo.com");
	content = ducky.get("/");
	std::cout << content;
	std::cout << std::endl;

	itemQuit();

	return 0;
}

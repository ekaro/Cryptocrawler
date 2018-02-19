#include <Windows.h>
#include <iostream>
#include "Bitfinex.hpp"

int main()
{
	std::cout << "Cryptocrawler started" << std::endl;

	std::string accessKey = "hRgrdHeJbA0aLGe484BK9ZwSEfEZylReKOpi1o5SL1M";
	std::string	secretKey = "opZIISUg3kKh0FSgWqwS1kjSYnmrIvzHwH33D9tuAVr";

	Bitfinex conn(accessKey, secretKey);
	std::string response;
	int errCode;

	errCode = conn.getTicker(response, "btcusd");
	
	std::cout << "Response: " << response << std::endl;
	std::cout << "Error code: " << errCode << std::endl;

	Sleep(10000);

	return 0;
}
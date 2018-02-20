#include <Windows.h>
#include <iostream>
#include "Bitfinex.hpp"

int main()
{
	std::cout << "Cryptocrawler started" << std::endl;

	std::string accessKey = "hRgrdHeJbA0aLGe484BK9ZwSEfEZylReKOpi1o5SL1M";
	std::string	secretKey = "opZIISUg3kKh0FSgWqwS1kjSYnmrIvzHwH33D9tuAVr";

	Bitfinex Bfx(accessKey, secretKey);
	int errCode;

	errCode = Bfx.getTicker("btcusd");
	
	std::cout << "Ticker: " << Bfx.Ticker() << std::endl;
	std::cout << "Error code: " << errCode << std::endl;
	std::cout << "Bid: " << Bfx.getQuote(Bfx.Ticker()).first << std::endl;
	std::cout << "Ask: " << Bfx.getQuote(Bfx.Ticker()).second << std::endl;

	Sleep(10000);

	return 0;
}
#include <Windows.h>
#include <iostream>
#include "Bitfinex.hpp"

int main()
{
	std::cout << "CryptoCrawler started." << std::endl;

	std::string accessKey = "hRgrdHeJbA0aLGe484BK9ZwSEfEZylReKOpi1o5SL1M";
	std::string	secretKey = "opZIISUg3kKh0FSgWqwS1kjSYnmrIvzHwH33D9tuAVr";

	Bitfinex Bfx(accessKey, secretKey);
	
	std::string pair = "btcusd";
	std::cout << pair << std::endl;
	std::pair<std::string, std::string> Quotes = Bfx.getQuote(pair);

	//std::cout << "Bid: " << Quotes.first << std::endl;
	//std::cout << "Ask: " << Quotes.second << std::endl;

	Sleep(1000000);

	return 0;
}
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

	std::map<std::string, std::string> Ticker = Bfx.getTicker(pair);

	std::cout << Ticker.find("bid")->first << " => " << Ticker.find("bid")->second << std::endl;
	std::cout << Ticker.find("ask")->first << " => " << Ticker.find("ask")->second << std::endl;
	
	Sleep(1000000);

	return 0;
}
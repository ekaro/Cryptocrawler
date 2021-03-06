#include <Windows.h>
#include <iostream>
#include "Bitfinex.hpp"
#include "Binance.hpp"

int main()
{
	std::cout << "CryptoCrawler started." << std::endl;

	/* Bitfinex stuff
	std::string accessKey = "hRgrdHeJbA0aLGe484BK9ZwSEfEZylReKOpi1o5SL1M";
	std::string	secretKey = "opZIISUg3kKh0FSgWqwS1kjSYnmrIvzHwH33D9tuAVr";

	Bitfinex Bfx(accessKey, secretKey);
	
	std::string pair = "btcusd";
	std::cout << pair << std::endl;

	std::map<std::string, std::string> Ticker = Bfx.getTicker(pair);

	std::cout << Ticker.find("bid")->first << " => " << Ticker.find("bid")->second << std::endl;
	std::cout << Ticker.find("ask")->first << " => " << Ticker.find("ask")->second << std::endl;

	std::cout << "Stats: " << Bfx.getStats(pair) << std::endl;
	std::cout << "FundingBook: " << Bfx.getFundingBook(pair) << std::endl;
	std::cout << "OrderBook: " << Bfx.getOrderBook(pair) << std::endl;
	std::cout << "Trades: " << Bfx.getTrades(pair) << std::endl;
	std::cout << "Lends: " << Bfx.getLends(pair) << std::endl;
	std::cout << "Symbols: " << Bfx.getSymbols(pair) << std::endl;
	std::cout << "SymbolDetails: " << Bfx.getSymbolDetails(pair) << std::endl;
	*/

	Binance Bnc;
	//std::cout << "Test ping: " << Bnc.getPing() << std::endl;
	//std::cout << "Time: " << Bnc.getTime() << std::endl;
	std::cout << "Current exchange trading rules and symbol information:" << Bnc.getExchangeInfo() << std::endl;

	Sleep(1000000);

	return 0;
}
#include "Bitfinex.hpp"

Bitfinex::Bitfinex(const std::string& accessKey, const std::string& secretKey) :
	accessKey(accessKey),
	secretKey(secretKey),
	curl(NULL)
{
	curl = curl_easy_init();
	APIurl = "https://api.bitfinex.com/v1";

	symbols =
	{
		"btcusd", "ltcusd", "ltcbtc",
		"ethusd", "ethbtc", "etcbtc",
		"etcusd", "bfxusd", "bfxbtc",
		"rrtusd", "rrtbtc", "zecusd",
		"zecbtc", "xmrusd", "xmrbtc"
	};

	currencies =
	{
		"USD", "BTC", "ETH", "ETC", "BFX", "ZEC", "LTC"
	};
}

Bitfinex::~Bitfinex()
{
	curl_easy_cleanup(curl);
}
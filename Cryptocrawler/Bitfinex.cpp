#include "Bitfinex.hpp"

/*
#include <cryptopp/hmac.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>*/

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

bool Bitfinex::inSymbols(const std::string &value, const std::vector<std::string> &symbols)
{
	return std::find(symbols.begin(), symbols.end(), value) != symbols.end();
}

int Bitfinex::getTicker(std::string &result, const std::string &symbol)
{
	if (!inSymbols(symbol, symbols))
	{
		return -40;
	}
	std::string endPoint = "/pubticker/" + symbol;
	std::string params = "";
	return GETrequest(endPoint, params, result);
}

size_t Bitfinex::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int Bitfinex::GETrequest(const std::string &UrlEnd, const std::string &params, std::string &result)
{
	if (curl) 
	{

		std::string fullurl = APIurl + UrlEnd + params;
		
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, fullurl.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			std::cout << "Libcurl error in GET request, code:\n";
			return res;
		}
		return res;
	}
	else
	{
		return -50;
	}
}
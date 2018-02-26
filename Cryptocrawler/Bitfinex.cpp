#include "Bitfinex.hpp"

#include <cryptopp/hmac.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>

Bitfinex::Bitfinex(const std::string& accessKey, const std::string& secretKey) :
	accessKey(accessKey),
	secretKey(secretKey),
	curl(NULL)
{
	curl = curl_easy_init();
	APIurl = "https://api.bitfinex.com/v1";

	allsymbols =
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


// Split string by delimiter (can be a string)
std::vector<std::string> Bitfinex::SplitString(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(s.substr(pos_start));
	return res;
}

// Search in vector of strings
bool Bitfinex::inSymbols(const std::string &value, const std::vector<std::string> &symbols)
{
	return std::find(symbols.begin(), symbols.end(), value) != symbols.end();
}

std::map<std::string, std::string> Bitfinex::getTicker(const std::string &symbol)
{
	if (!inSymbols(symbol, allsymbols))
	{
		std::cout << "Symbol is not in supported symbols " << std::endl;
	}

	std::string endPoint = "/pubticker/" + symbol;
	std::string params = "";
	int errCode = GETrequest(endPoint, params, ticker);
	if (errCode != 0)
	{
		std::cout << "Connection problem. Error code: " << errCode << std::endl;
	}

	std::map<std::string, std::string> TickerMap = Map(ticker);  // creates std::map from ticker string

	return TickerMap;
}

std::map<std::string, std::string> Bitfinex::Map(std::string &response)
{
	std::string delimiter = "\"";
	std::vector<std::string> data = SplitString(response, delimiter); // splits string into vector by delimiter "

	std::vector<std::string> cleared;
	for (auto i : data)               // cleares data string from chars of length 1
	{
		if (i.length() > 1)
		{
			cleared.push_back(i);
		}
	}

	std::map<std::string, std::string> mapka;

	for (size_t i = 0; i <= cleared.size() - 1; i += 2)
	{
		mapka.emplace(cleared[i], cleared[i + 1]);   // creates a map from cleared string
	}

	return mapka;
}

// Curl write callback function. Appends fetched *content to *userp pointer.
// *userp pointer is set up by curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result) line.
// In this case *userp will point to result.
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
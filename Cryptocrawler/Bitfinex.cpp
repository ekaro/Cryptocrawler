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

int Bitfinex::getTicker(const std::string &symbol)
{
	if (!inSymbols(symbol, symbols))
	{
		return -40;
	}
	std::string endPoint = "/pubticker/" + symbol;
	std::string params = "";
	return GETrequest(endPoint, params, ticker);
}

std::pair<std::string, std::string> Bitfinex::getQuote(const std::string &res)
{
	int errCode;
	errCode = getTicker(res);
	if (errCode != 0)
	{
		std::cout << "Connection problem. Error code: " << errCode << std::endl;
	}

	std::string delimiter = "\"";

	//std::cout << ticker << std::endl;

	std::vector<std::string> quotes = SplitString(ticker, delimiter);
	
	std::vector<std::string> cleared;
	for (auto i : quotes)
	{
		if (i.length() > 1)
		{
			cleared.push_back(i);
		}
	}

	for (auto s : cleared)
	{
		//std::cout << s << std::endl;
	}

	std::map<std::string, std::string> mapka;

	for (int i = 0; i <= cleared.size() - 1; i += 2)
	{
		mapka.emplace(cleared[i], cleared[i+1]);
	}

	for (const auto &p : mapka) {
		std::cout << p.first << " => " << p.second << '\n';
	}

	return { quotes[4], quotes[6] };
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
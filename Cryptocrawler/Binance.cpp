#include "Binance.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

Binance::Binance():
	curl(NULL)
{
	curl = curl_easy_init();
	APIurl = "https://api.binance.com/api/v1";
}

Binance::~Binance()
{
	curl_easy_cleanup(curl);
}

std::string Binance::getPing()
{
	std::string endPoint = "/ping";
	std::string params = "";

	int errCode = GETrequest(endPoint, params, ping);
	if (errCode != 0)
	{
		std::cout << "Connection problem. Error code: " << errCode << std::endl;
	}

	return ping;
}

std::string Binance::getTime()
{
	std::string endPoint = "/time";
	std::string params = "";

	int errCode = GETrequest(endPoint, params, time);
	if (errCode != 0)
	{
		std::cout << "Connection problem. Error code: " << errCode << std::endl;
	}

	return time;
}

std::string Binance::getExchangeInfo()
{
	std::string endPoint = "/exchangeInfo";
	std::string params = "";

	int errCode = GETrequest(endPoint, params, exchangeInfo);
	if (errCode != 0)
	{
		std::cout << "Connection problem. Error code: " << errCode << std::endl;
	}

	return exchangeInfo;
}

// Curl write callback function. Appends fetched *content to *userp pointer.
// *userp pointer is set up by curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result) line.
// In this case *userp will point to result.
size_t Binance::WriteCallback(void * contents, size_t size, size_t nmemb, void * userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int Binance::GETrequest(const std::string & UrlEndPoint, const std::string & params, std::string & result)
{
	if (curl)
	{

		std::string fullurl = APIurl + UrlEndPoint + params;

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

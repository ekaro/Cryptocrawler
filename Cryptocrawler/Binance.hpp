#pragma once
#include <string>
#include <iostream>
#include <curl/curl.h>

class Binance
{
public:
	explicit Binance();
	~Binance();
	std::string getPing();
	std::string getTime();
	std::string getExchangeInfo();
private:
	CURL * curl;
	std::string APIurl;
	CURLcode res;
	std::string ping;
	std::string time;
	std::string exchangeInfo;
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	int GETrequest(const std::string &UrlEndPoint, const std::string &params, std::string &result);
};
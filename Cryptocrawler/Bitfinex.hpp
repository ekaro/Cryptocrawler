#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <curl/curl.h>

class Bitfinex
{
public:

	explicit Bitfinex(const std::string &accessKey, const std::string &secretKey);
	~Bitfinex();

	int getTicker(const std::string &symbol);
	std::string Ticker();
	std::pair<std::string, std::string> getQuote(const std::string &result);

private:
	std::string accessKey, secretKey;
	CURL *curl;
	CURLcode res;
	std::string APIurl;
	std::string ticker;
	std::vector<std::string> symbols; 
	std::vector<std::string> currencies; 
	static bool inSymbols(const std::string &value, const std::vector<std::string> &symbols);
	int GETrequest(const std::string &UrlEndPoint, const std::string &params, std::string &result);
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
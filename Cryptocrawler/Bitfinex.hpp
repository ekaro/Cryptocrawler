#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <curl/curl.h>

class Bitfinex
{
public:

	explicit Bitfinex(const std::string &accessKey, const std::string &secretKey);
	~Bitfinex();

	std::map<std::string, std::string> getTicker(const std::string &symbol);
	
	std::string getStats(const std::string &symbol);
	std::string getFundingBook(const std::string &symbol);
	std::string getOrderBook(const std::string &symbol);
	std::string getTrades(const std::string &symbol);
	std::string getLends(const std::string &symbol);
	std::string getSymbols(const std::string &symbol);
	std::string getSymbolDetails(const std::string &symbol);
	
private:
	std::string accessKey, secretKey;
	CURL *curl;
	CURLcode res;
	std::string APIurl;
	std::string ticker;
	std::string stats;
	std::string fundingbook;
	std::string orderbook;
	std::string trades;
	std::string lends;
	std::string symbols;
	std::string symboldetails;
	std::vector<std::string> allsymbols; 
	std::vector<std::string> currencies; 
	std::map<std::string, std::string> Map(std::string &response);
	std::vector<std::string> SplitString(std::string s, std::string delimiter);
	static bool inSymbols(const std::string &value, const std::vector<std::string> &symbols);
	int GETrequest(const std::string &UrlEndPoint, const std::string &params, std::string &result);
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
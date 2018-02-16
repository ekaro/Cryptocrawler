#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>

class Bitfinex
{
public:

	explicit Bitfinex(const std::string &accessKey, const std::string &secretKey);
	~Bitfinex();

private:
	std::string accessKey, secretKey;
	CURL* curl;
	std::string APIurl;
	std::vector<std::string> symbols; 
	std::vector<std::string> currencies; 
};
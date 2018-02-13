#pragma once

#include <fstream>
#include <time.h>
#include <string>
#include <vector>
//#include <jansson.h>
//#include <curl/curl.h>

struct Parameters {

	std::vector<std::string> exchName;
	std::vector<double> fees;
	std::vector<bool> canShort;
	std::vector<bool> isImplemented;
	std::vector<std::string> tickerUrl;

	//CURL* curl;
	double spreadEntry;
	double spreadTarget;
	unsigned maxLength;
	double priceDeltaLim;
	bool aggressiveVolume;
	double trailingLim;
	double orderBookFactor;
	bool demoMode;
	bool verbose;
	std::ofstream* logFile;
	unsigned gapSec;
	unsigned debugMaxIteration;
	bool useFullCash;
	double untouchedCash;
	double cashForTesting;
	double maxExposure;

	std::string bitfinexApi;
	std::string bitfinexSecret;
	double bitfinexFees;
	bool bitfinexCanShort;

	bool sendEmail;
	std::string senderAddress;
	std::string senderUsername;
	std::string senderPassword;
	std::string smtpServerAddress;
	std::string receiverAddress;

	Parameters(std::string fileName);

	void addExchange(std::string n, double f, bool h, bool m);

	int nbExch() const;

};

std::string getParameter(std::string parameter, std::ifstream& configFile);

bool getBool(std::string value);

double getDouble(std::string value);

unsigned getUnsigned(std::string value);
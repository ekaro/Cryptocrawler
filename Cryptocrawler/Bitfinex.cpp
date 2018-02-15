#include "bitfinex.h"
#include "parameters.h"
#include "restapi.h"
//#include "utils/base64.h"
//#include "hex_str.hpp"
#include "unique_json.hpp"

//#include "openssl/sha.h"
//#include "openssl/hmac.h"
#include <sstream>
#include <iomanip>
#include <array>
#include <cmath>
#include <ctime>

namespace Bitfinex {

	static RestApi& queryHandle(Parameters &params)
	{
		static RestApi query("https://api.bitfinex.com",
			params.cacert.c_str(), *params.logFile);
		return query;
	}
	
	quote_t getQuote(Parameters &params)
	{
		auto &exchange = queryHandle(params);

		std::string url;
		url = "/v1/ticker/btcusd";

		unique_json root{ exchange.getRequest(url) };

		const char *quote = json_string_value(json_object_get(root.get(), "bid"));
		double bidValue = quote ? std::stod(quote) : 0.0;

		quote = json_string_value(json_object_get(root.get(), "ask"));
		double askValue = quote ? std::stod(quote) : 0.0;

		return std::make_pair(bidValue, askValue);
	}
}
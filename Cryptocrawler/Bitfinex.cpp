#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <time.h>
#include "bitfinex.h"

namespace Bitfinex {
	/*
	double getQuote(Parameters& params, bool isBid) {
		json_t* root = getJsonFromUrl(params, "https://api.bitfinex.com/v1/ticker/btcusd", "");
		const char* quote;
		double quoteValue;
		if (isBid) {
			quote = json_string_value(json_object_get(root, "bid"));
		}
		else {
			quote = json_string_value(json_object_get(root, "ask"));
		}
		if (quote != NULL) {
			quoteValue = atof(quote);
		}
		else {
			quoteValue = 0.0;
		}
		json_decref(root);
		return quoteValue;
	}*/
}
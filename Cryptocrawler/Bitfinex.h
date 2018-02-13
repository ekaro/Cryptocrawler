#pragma once

//#include <curl/curl.h>
#include <string>
#include "parameters.h"

namespace Bitfinex {

	// get quote
	double getQuote(Parameters& params, bool isBid);

}
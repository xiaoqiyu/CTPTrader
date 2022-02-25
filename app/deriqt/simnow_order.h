#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <cassert>
#include <utility>
#include <string.h>
#include <algorithm>
#include "ThostFtdcMdApi.h"
#include "INIReader.h"
#include "UserStruct.h"
#include "define.h"
#include "CTPTraderHandler.h"
// #include "helper.h"
#include "recordio.h"
#include "recordio_range.h"
#include <glog/logging.h>

typedef CTPTraderHandler *trader_util_ptr;
typedef bool order_signal;
int nRequestID = 0;
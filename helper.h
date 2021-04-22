#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>


std::vector<std::string> split_str(std::string s, char c)
{
    // std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
    std::vector<std::string> v;
	std::stringstream sstr(s);
	std::string token;
	int cnt = 0;
    while (getline(sstr, token, c))
    {
       v.push_back(token);
    }
    return v;
}


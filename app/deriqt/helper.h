#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "UserStruct.h"

//TODO check multiple definition errors
// std::vector<std::string> split_str(std::string s, char c)
// {
    // std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
    // std::vector<std::string> v;
	// std::stringstream sstr(s);
	// std::string token;
	// int cnt = 0;
    // while (getline(sstr, token, c))
    // {
    //    v.push_back(token);
    // }
    // return v;
// }

template <typename... Args>
static std::string formatString(const std::string &format, Args... args)
{
    auto size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template <typename... Args>
static std::wstring formatString(const std::wstring &format, Args... args)
{
    auto size = std::swprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
    std::swprintf(buf.get(), size, format.c_str(), args...);
    return std::wstring(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template <typename... Args>
static void formatStringEx(std::string &dst, const std::string &format, Args... args)
{
    auto size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    dst = {buf.get(), buf.get() + size - 1};
}

template <typename... Args>
static void formatStringEx(std::wstring &dst, const std::wstring &format, Args... args)
{
    auto size = std::swprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
    std::swprintf(buf.get(), size, format.c_str(), args...);
    dst = {buf.get(), buf.get() + size - 1};
}

// std::string str;
// std::wstring wstr;

// std::string str_1 = formatString("%s, %d, %f, %.2lf", "today", 2, 2.1, 0.1);
// formatStringEx(str, "%s, %d, %f, %.2lf", "today", 2, 2.1, 0.1);

// std::wstring wstr_1 = formatString(L"%s, %d, %f, %.2lf", L"today", 2, 2.1, 0.1);
// formatStringEx(wstr, L"%s, %d, %f, %.2lf", L"today", 2, 2.1, 0.1);

//TODO refactor
// std::string get_exchange_id_order(int mode=1, std::string product_id="eg"){
    // if(mode == 1){
        //  if(product_id == "eg"){
            //  return "DCE";
        //  }
        // 
    // }else if(mode == 2){
        // return "mode 2";
    // }else{
        // return "invalid mode";
    // }
    // return "invalid mode";
    // 
// }






//
// Created by leo on 2023/7/27.
//

#ifndef UTIL_STRING_STRINGUTIL_H_
#define UTIL_STRING_STRINGUTIL_H_

#include <string>
#include <locale>
#include <codecvt>
#include <filesystem>

namespace mao {
namespace util {
std::string wstring2utf8string(const std::wstring &str) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> strCnv;
  return strCnv.to_bytes(str);
}

std::wstring utf8string2wstring(const std::string &str) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> strCnv;
  return strCnv.from_bytes(str);
}

std::string wstring2string(const std::wstring &wstr) {
  std::string str = std::filesystem::path(wstr).string();
  return str;
}

std::wstring string2wstring(const std::string &str) {
  std::wstring wstr = std::filesystem::path(str).wstring();
  return wstr;
}

std::string ansi2utf8(const std::string &ansi) {
  std::wstring wtxt = string2wstring(ansi);
  std::string txt_uft8 = wstring2utf8string(wtxt);
  return txt_uft8;
}

std::string utf82ansi(const std::string &utf8) {
  std::wstring wtxt = utf8string2wstring(utf8);
  std::string txt_ansi = wstring2string(wtxt);
  return txt_ansi;
}
}
}
#endif //UTIL_STRING_STRINGUTIL_H_

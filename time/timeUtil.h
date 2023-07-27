//
// Created by leo on 2023/7/27.
//

#ifndef MAOUTIL_TIME_TIMEUTIL_H_
#define MAOUTIL_TIME_TIMEUTIL_H_

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
namespace mao {
namespace util {

long long GetTimeSampS() {
  auto tp = std::chrono::system_clock::now();
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  return seconds.count();
}

long long GetTimeSampM() {
  auto tp = std::chrono::system_clock::now();
  auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
  return seconds.count();
}

std::string TimeSampS2Str(long samp, const std::string &fmt = "%Y-%m-%d %H:%M:%S") {
  std::stringstream ss;
  ss << std::put_time(std::localtime(&samp), fmt.c_str());
  return ss.str();
}

std::string TimeSampM2Str(long long samp, const std::string &fmt = "%Y-%m-%d %H:%M:%S") {
  long samps = samp / 1000;
  std::stringstream ss;
  ss << std::put_time(std::localtime(&samps), fmt.c_str());
  ss << "." << std::setfill('0') << std::setw(3) << samps % 1000;
  return ss.str();
}

long Str2TimeSampS(const std::string &str, const std::string &fmt = "%Y-%m-%d %H:%M:%S") {
  std::stringstream ss;
  ss << str;

  std::tm tm{};
  ss >> std::get_time(&tm, fmt.c_str());
  auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  auto second = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  return second.count();
}

}
}
#endif //MAOUTIL_TIME_TIMEUTIL_H_

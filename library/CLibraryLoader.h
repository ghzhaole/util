//
// Created by leo on 2023/7/27.
//

#ifndef UTIL_LIBRARY_CLIBRARYLOADER_H_
#define UTIL_LIBRARY_CLIBRARYLOADER_H_

#include "../string/StringUtil.h"

#include <type_traits>
#include <utility>

#ifdef WIN32
#include <windows.h>
#include <codecvt>
#include <locale>
#else
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

namespace mao {
namespace util {

class CLibraryLoader {
 public:
  explicit inline CLibraryLoader() : libHandle_(nullptr) {};

  ~CLibraryLoader() { Free(); };

 public:
  inline bool Load(const std::string &libPath) {
#ifdef WIN32
    std::wstring strpath = utf8string2wstring(libPath);
    libHandle_ =
        LoadLibraryExW(strpath.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (libHandle_ == nullptr) {
      return false;
    }
    return true;
#else
    libHandle_ = dlopen(libPath.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (!libHandle_) {
      printf("error msg:%s", dlerror());
      return false;
    }
    return true;
#endif
  };

  inline void* GetAddress(const std::string& symbol){
#ifdef WIN32
    auto address = GetProcAddress((HMODULE)libHandle_, symbol.c_str());
#else
    void * address = dlsym(libHandle_, symbol.c_str());
#endif
    return address;
  }

  inline void Free() {
#ifdef WIN32
    if (libHandle_ != nullptr) {
    ::FreeLibrary((HMODULE)libHandle_);
    libHandle_ = nullptr;
  }
#else
    if (libHandle_ != nullptr) {
      dlclose(libHandle_);
      libHandle_ = nullptr;
    }
#endif
  };

 private:
  void *libHandle_;
};

} // mao
} // util

#endif //UTIL_LIBRARY_CLIBRARYLOADER_H_

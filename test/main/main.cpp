//
// Created by leo on 2023/7/27.
//

#include <iostream>
#include <iomanip>
#include "string/StringUtil.h"
#include "library/CLibraryLoader.h"
#include "file/CFileUtil.h"

struct MyStruct {
  int i{1};

  int j{2};

  MyStruct(int _i, int _j) : i(_i), j(_j) {};

  friend std::ostream &operator<<(std::ostream &os, const MyStruct &s) {
    os << s.i << "\t" << s.j;
    return os;
  }

  friend std::istream &operator>>(std::istream &os, MyStruct &s) {
    os >> s.i >> s.j;
    return os;
  }
};

using addfunc = int(int, int);
int main() {
  std::string s = "你好";
  std::cout << mao::util::utf82ansi(s) << std::endl;

  std::string path = "/Users/leo/git/util/bin/Debug/lib/libmaoTestLib_d.dylib";
  mao::util::CLibraryLoader *libl = new mao::util::CLibraryLoader();
  if (libl->Load(path)) {
    addfunc *add = (addfunc *)libl->GetAddress("add");
    if (add) {
      std::cout << add(1, 2) << std::endl;
    }
  }

  mao::util::CFileUtil fileUtil;
  fileUtil.open("MyStruct.txt", std::ios::out | std::ios::binary);
  fileUtil.write(MyStruct(3, 4));

  fileUtil.open("MyStruct.txt", std::ios::in | std::ios::binary);
  MyStruct myStruct(1, 2);
  fileUtil.Read(myStruct);

  std::cout << myStruct;

  return 0;
}
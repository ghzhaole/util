//
// Created by leo on 2023/7/27.
//

#include <iostream>
#include <iomanip>
#include "string/StringUtil.h"
#include "library/CLibraryLoader.h"

using addfunc = int(int,int);
int main()
{
  std::string s = "你好";
  std::cout<<mao::util::utf82ansi(s)<<std::endl;

  std::string path = "/Users/leo/git/util/bin/Debug/lib/libmaoTestLib_d.dylib";
  mao::util::CLibraryLoader* libl = new mao::util::CLibraryLoader();
  bool _if = libl->Load(path);
  if(_if){
    addfunc* add = (addfunc*)libl->GetAddress("add");
    if(add){
      std::cout<<add(1,2)<<std::endl;
    }
  }
  return 0;
}
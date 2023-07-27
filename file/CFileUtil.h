//
// Created by leo on 2023/7/27.
//
#include <string>
#include <fstream>
#include <filesystem>
#ifndef MAOUTIL_FILE_FILEUTIL_H_
#define MAOUTIL_FILE_FILEUTIL_H_
namespace mao {
namespace util {
class CFileUtil {
  enum class OpenState {
    NOT_OPEN = 0, ERROR, WRITE, READ
  };

 public:
  explicit CFileUtil() : state_(OpenState::NOT_OPEN) {};
  ~CFileUtil() {}

  //打开文件
  inline void open(const std::string &filePath, std::ios_base::openmode mode = std::ios::in) {
    if (this->state_ == OpenState::WRITE) {
      this->ofstream_.close();
    } else if (this->state_ == OpenState::READ) {
      this->ifstream_.close();
    }
    if (mode & std::ios::in) {
      this->ifstream_ = std::ifstream(std::filesystem::path(filePath), mode);
      if (this->ifstream_.is_open()) {
        this->state_ = OpenState::READ;
      } else {
        this->state_ = OpenState::ERROR;
      }
    } else if (mode & std::ios::out) {
      this->ofstream_ = std::ofstream(std::filesystem::path(filePath), mode);
      if (this->ofstream_.is_open()) {
        this->state_ = OpenState::WRITE;
      } else {
        this->state_ = OpenState::ERROR;
      }
    }

    mode_ = mode;
  }

  //二进制读取
  inline bool Read(char *buf, size_t len) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (!this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    memset(buf, 0, len);
    if (len <= 0) {
      return true;
    }

    this->ifstream_.read(buf, len);
    if (!this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    return true;
  }

  //二进制读取
  inline bool Read(std::string &str, size_t len) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    str = "";
    if (len <= 0) {
      return true;
    }

    char *buf = new char[len + 1];
    memset(buf, 0, len + 1);
    this->ifstream_.read(buf, len);
    str = buf;
    delete[] buf;
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    return true;
  }

  //二进制读取
  template <class T>
  inline bool Read(T &t, int len) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }

    if (len < 0) {
      len = sizeof(t);
    }
    if (len <= 0) {
      return true;
    }

    this->ifstream_.read((char *)&t, len);
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    return true;
  }

  //二进制和文本读取，文本读取时仅支持重载 '>>' 运算符的数据类型
  template <class T>
  inline bool Read(T &t) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }

    if (this->mode_ & std::ios::binary) {
      return this->Read(t, -1);
    }

    this->ifstream_ >> t;
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    return true;
  }

  //文本读取，读取一个单词，仅支持重载 '>>' 运算符的数据类型
  template <class T>
  inline bool ReadWord(T &t) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    this->ifstream_ >> t;
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    return true;
  }

  //文本读取，读取一行字符串
  inline bool ReadLine(std::string &str) {
    if (this->state_ != OpenState::READ) {
      return false;
    }
    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }
    str = "";
    if (getline(this->ifstream_, str)) {
      return true;
    }

    if (this->ifstream_.fail() || !this->ifstream_.good()) {
      return false;
    }

    return true;
  }

  // 支持二进制输出和文本输出，二进制输出仅支持POD数据类型，文本输出仅支持重载了 '<<' 运算符的数据类型
  template <class T>
  inline bool write(const T &t) {
    if (this->state_ != OpenState::WRITE) {
      return false;
    }
    if (this->ofstream_.fail() || !this->ofstream_.good()) {
      return false;
    }

    if (this->mode_ & std::ios::binary) {
      this->ofstream_.write((char *)&t, sizeof(t));
    } else {
      this->ofstream_ << t;
    }

    return true;
  }

  //支持二进制和文本输出，输出buf中的数据或字符串
  inline bool write(char *buf, size_t len) {
    if (this->state_ != OpenState::WRITE) {
      return false;
    }
    if (this->ofstream_.fail() || !this->ofstream_.good()) {
      return false;
    }

    if (len <= 0) {
      return true;
    }

    if (this->mode_ & std::ios::binary) {
      this->ofstream_.write(buf, len);
    } else {
      this->ofstream_ << buf;
    }

    return true;
  }

  //文本输出，输出字符串
  inline bool write(const std::string &str) {
    if (this->state_ != OpenState::WRITE) {
      return false;
    }
    if (this->ofstream_.fail() || !this->ofstream_.good()) {
      return false;
    }

    if (str.empty()) {
      return true;
    }

    if (this->mode_ & std::ios::binary) {
      this->ofstream_.write(str.c_str(), strlen(str.c_str()));
    } else {
      this->ofstream_ << str;
    }

    return true;
  }

  // 仅支持重载了 '<<' 运算符的数据类型
  template <class T>
  inline bool writeLine(const T &t) {
    if (this->state_ != OpenState::WRITE) {
      return false;
    }
    if (this->ofstream_.fail() || !this->ofstream_.good()) {
      return false;
    }

    if (this->mode_ & std::ios::binary) {
      return false;
    }

    this->ofstream_ << t << std::endl;

    return true;
  }

  //关闭文件
  inline bool close() {
    if (this->state_ == OpenState::WRITE) {
      this->ofstream_.close();
    } else if (this->state_ == OpenState::READ) {
      this->ifstream_.close();
    } else {
      return false;
    }

    return true;
  }

 private:
  std::ifstream ifstream_;

  std::ofstream ofstream_;

  OpenState state_;

  std::ios_base::openmode mode_;
};
}
}
#endif //MAOUTIL_FILE_FILEUTIL_H_

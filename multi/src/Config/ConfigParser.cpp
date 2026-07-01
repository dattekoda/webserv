#include "Config.hpp"

#include <fstream>
#include <string>

enum ETokenType {
  eTTLBrace,
  eTTRBrace,
  eTTStr,
  eTTDir
};

struct Token {
  ETokenType type_;
  std::string str_;
  // std::vector<Token> nodes_;
  Token(ETokenType type) : type_(type), str_() {}
  Token(ETokenType type, std::string const &str) : type_(type), str_(str) {}
};

class ConfigTokenizer {
  std::vector<Token> tokens_;
  std::string const kcontent_;
  size_t offset_;

public:
  ConfigTokenizer(std::string const &content) : kcontent_(content), offset_(0) { tokens_.reserve(content.size() / 10); }
  void tokenizeBlock(void);
  void tokenizeDirective(void);
  std::vector<Token> const &get(void) const;
};

void ConfigTokenizer::tokenizeDirective(void) {
  while (offset_ < kcontent_.size()) {
    while (offset_ < kcontent_.size() && std::isspace(static_cast<unsigned char>(kcontent_[offset_])))
      ++offset_;
  }
}

void ConfigTokenizer::tokenizeBlock(void) {
  int brace_num = 0;

  while (offset_ < kcontent_.size()) {
    while (offset_ < kcontent_.size() && std::isspace(static_cast<unsigned char>(kcontent_[offset_])))
      ++offset_;
    if (kcontent_[offset_] == '{') {
      ++brace_num;
      ++offset_;
      tokens_.push_back(Token(eTTLBrace));
    } else if (kcontent_[offset_] == '}') {
      --brace_num;
      if (brace_num < 0) {
        throw std::runtime_error("Invalid format");
      }
      ++offset_;
      tokens_.push_back(Token(eTTRBrace));
    } else {
      size_t const kStart = offset_;
      while (offset_ < kcontent_.size() && kcontent_[offset_] != '{' && kcontent_[offset_] != '}')
        ++offset_;
      tokens_.push_back(Token(eTTStr, kcontent_.substr(kStart, offset_ - kStart)));
    }
  }
  if (brace_num != 0)
    throw std::runtime_error("Invalid format");
}

std::vector<Token> const &ConfigTokenizer::get(void) const { return tokens_; }

#include <iostream>
int main(int argc, char *argv[]) {
  if (argc == 1)
    return 1;
  ConfigTokenizer ct(argv[1]);
  try {
    ct.tokenizeBlock();
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  std::vector<Token> const &kVt = ct.get();
  for (size_t i = 0; i < kVt.size(); ++i) {
    if (kVt[i].type_ == eTTLBrace)
      std::cout << "left" << std::endl;
    else if (kVt[i].type_ == eTTStr)
      std::cout << kVt[i].str_ << std::endl;
    else if (kVt[i].type_ == eTTRBrace)
      std::cout << "right" << std::endl;
  }
  return 0;
}

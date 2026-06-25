#include "Config.hpp"
#include <vector>

// namespace {
// bool is_valid_json_syntax(const std::string &content);
// }

enum ETokenType {
  eTTLeftPar,
  eTTRightPar,
  eTTDir,
  eTTName,
  eTTValue,
  eTTComma,
  eTTSemiColumn
};

struct Token {
  ETokenType type_;
  std::string str_;
  std::vector<Token> nodes_;
  Token(ETokenType type) : type_(type), str_(0) {}
  Token(ETokenType type, const std::string &str) : type_(type), str_(str) {}
};

class ConfigTokenizer {
  const std::string *kcontent_;
  size_t offset_;
  std::vector<Token> tokens_;

  void tokenizeDirective(void);

public:
  ConfigTokenizer(const std::string &content)
      : kcontent_(&content), offset_(0) {
    tokens_.reserve(content.size() / 10);
    tokenizeDirective();
  }
  std::vector<Token> const &get(void);
};

Config::Config(const std::string &content) {
  ConfigTokenizer ct(content);
  std::vector<Token> const kTokens = ct.get();
}

void ConfigTokenizer::tokenizeDirective(void) {
  for (; offset_ < kcontent_->size(); offset_++) {
    if ((*kcontent_)[offset_] == '{') {
      tokens_.push_back(Token(eTTLeftPar));
    } else if ((*kcontent_)[offset_] == '}') {
      tokens_.push_back(Token(eTTRightPar));
    } else {
      tokens_.push_back(Token(eTTDir));
    }
  }
}

namespace {} // namespace

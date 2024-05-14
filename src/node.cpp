#include "node.h"
#include "token.h"
#include <variant>

Node::Node() {}

Node::~Node() {}

void Node::addToken(Token t) { children.push_back(t); }
void Node::addNode(Node n) { children.push_back(n); }

std::ostream &operator<<(std::ostream &os, const Node &node) {
  for (auto &el : node.children) {
    if (std::holds_alternative<Token>(el)) {
      Token t = std::get<Token>(el);
      os << token_lexeme(t) << std::endl;

    } else if (std::holds_alternative<Node>(el)) {
      Node n = std::get<Node>(el);
      os << n;
    }
  }

  return os;
}

#include <iostream>
#include <vector>

#include "token.h"

class Node {
public:
  Node();
  ~Node();

  void addToken(Token t);
  void addNode(Node n);

  friend std::ostream &operator<<(std::ostream &os, const Node &node);

private:
  std::vector<std::variant<Token, Node>> children;
};

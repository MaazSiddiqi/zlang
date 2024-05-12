#include <vector>

#include "token.h"

class Node {
public:
  Node();
  Node(Node &&) = default;
  Node(const Node &) = default;
  Node &operator=(Node &&) = default;
  Node &operator=(const Node &) = default;
  ~Node();

private:
  std::vector<Node *> children;
  Token token;
};

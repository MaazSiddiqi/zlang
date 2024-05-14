#include <vector>

#include "token.h"

class Node {
public:
  Node();
  ~Node();

private:
  std::vector<std::variant<Token, Node>> children;
};

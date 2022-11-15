#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Node {
  std::string name;
  std::vector<Node> kids;
  Node *parent;
};

auto init_parents(Node &node) -> void {
  for (auto &kid: node.kids) {
    kid.parent = &node;
    init_parents(kid);
  }
}

auto walk(
        const Node &tree,
        std::function<void(const Node &node, int depth)> action,
        int depth = 0) -> void {
  action(tree, depth);
  for (auto &kid: tree.kids) {
    walk(kid, action, depth + 1);
  }
}

auto print(const Node &tree) -> void {
  walk(tree, [](const Node &node, int depth) {
    std::cout << std::string(2 * depth, ' ') << node.name << std::endl;
  });
}

auto calc_total_depth(const Node &tree) -> int {
  int total_depth = 0;
  walk(tree, [&total_depth](const Node &node, int depth) {
    total_depth += depth;
  });
  return total_depth;
}

auto process(const Node &intro) -> Node & {
  auto tree = Node{"root", {
                                   intro,
                                   {"one", {
                                                   {"two"},
                                                   {"three"},
                                           }},
                                   {"four"},
                           }};

  init_parents(tree);
  auto &internal_intro = tree.kids[0];
  print(internal_intro);
  print(tree);

  auto total_depth = 0;
  for (int i = 0; i < 200'000; ++i) {
    total_depth += calc_total_depth(kid);
  }

  std::cout << "Total depth: " << total_depth << std::endl;
  return tree;
}

auto main() -> int {
  auto intro = Node{"intro"};
  auto &tree = process(intro);
  std::cout << "Parent of intro: " << tree.kids[0].parent->name << std::endl;
  return 0;
}
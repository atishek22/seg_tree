#include "segment_tree.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

int main() {
  // range min query segment_tree
  auto min = [](const int &a, const int &b) -> int { return a < b ? a : b; };
  SegmentTree<int> tree_min({1, 2, 3, 4, 5, 6}, min,
                            std::numeric_limits<int>::max());
  std::cout << tree_min.get({2, 4}) << "\n";

  std::vector<int> nums{6, 5, 4, 3, 2, 1};
  SegmentTree<int> tree_sum(nums);
  std::cout << tree_sum.get({1, 3}) << "\n";

  return 0;
}

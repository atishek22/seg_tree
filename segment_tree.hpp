#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> class SegmentTree {
public:
  using vector = std::vector<T>;
  using size_t = std::size_t;
  using range = std::pair<size_t, size_t>;
  using compute = std::function<T(const T &, const T &)>;

  SegmentTree() {}

  SegmentTree(const std::vector<T> &nums, compute c = std::plus<T>{},
              T init = 0) {
    if (nums.size() == 0) {
      throw std::invalid_argument("No elements");
    }
    this->nums = nums;
    this->c = c;
    this->init = init;

    // init tree array - The required size
    // for the tree array = 2 * k - 1 where
    // k is the just greatest power of n
    const size_t n = nums.size();
    size_t size = std::ceil(std::log2(n));
    size = 2 * std::pow(2, size) + 1;
    this->tree.resize(size);

    this->_build_tree({0, n - 1}, 0);
  }

  SegmentTree(const std::initializer_list<T> &nums, compute c = std::plus<T>{},
              T init = 0)
      : SegmentTree(std::vector<T>(nums), c, init) {}

  T get(range query) {
    const size_t n = nums.size();
    if (n == 0) {
      throw std::runtime_error("Can't perform range query on empty tree");
    }
    if (query.first < 0 || query.second > n - 1 || query.first > query.second) {
      throw std::out_of_range("Invalid query");
    }
    return _get(query, {0, n - 1}, 0);
  }

  void update() {}

private:
  vector tree;
  vector nums;
  compute c;
  T init;

  T _build_tree(range r, size_t idx) {
    // Only one element in the range
    if (r.first == r.second) {
      tree[idx] = nums[r.first];
      return nums[r.first];
    }

    // middle of the range
    auto mid = r.first + (r.second - r.first) / 2;
    // build the left and right tree recursively
    tree[idx] = this->c(_build_tree({r.first, mid}, 2 * idx + 1),
                        _build_tree({mid + 1, r.second}, 2 * idx + 2));

    return tree[idx];
  }

  T _get(range &query, range r, size_t idx) {
    // the curr range is entirely inside query
    if (query.first <= r.first && query.second >= r.second) {
      return tree[idx];
    }
    // no overlap
    if (r.second < query.first || r.first > query.second) {
      return init;
    }

    auto mid = r.first + (r.second - r.first) / 2;
    auto inter = this->c(_get(query, {r.first, mid}, 2 * idx + 1),
                         _get(query, {mid + 1, r.second}, 2 * idx + 2));
    return inter;
  }
};

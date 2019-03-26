#include "radix_sort.h"
#include "counting_sort.h"
#include <utility>
#include <type_traits>

namespace {
  void _counting_sort_with(std::vector<uint32_t>& vec, std::vector<uint32_t>& indices, std::vector<uint32_t>& output, uint32_t exp) {
    const auto len = vec.size();
    std::fill(indices.begin(), indices.end(), 0);
    for (const auto val : vec) {
      ++indices[static_cast<size_t>(val / exp % 10)];
    }
    const auto range = indices.size();
    for (size_t i = 0, j = 1; j < range; ++i, ++j) {
      indices[j] = indices[i] + indices[j];
    }
    for (auto i = len; i-- > 0;) {
      const auto val = vec[i];
      output[static_cast<size_t>(--indices[static_cast<size_t>(val / exp % 10)])] = val;
    }
    vec = output;
    //vec = std::move(output); // swap memory
  }
}

namespace algotest {

  /**
   * theta(d*(n+k))
   * 
   */
  void radix_sort(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    auto max = vec[0];
    for (size_t i = 1; i < len; ++i) {
      if (vec[i] > max) {
        max = vec[i];
      }
    }

    std::vector<uint32_t> indices(10), output(vec.size());
    for (uint32_t exp = 1; max / exp > 0; exp *= 10) {
      _counting_sort_with(vec, indices, output, exp);
    }
  }
}
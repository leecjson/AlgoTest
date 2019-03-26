#include "bubble_sort.h"
#include <utility>

namespace algotest {
  /**
   * avg: O(n^2)
   */
  void bubble_sort(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    const auto last = len - 1;
    for (size_t k = 1; k < len; ++k) {
      for (size_t i = 0; i < last; ++i) {
        const auto j = i + 1;
        if (vec[i] > vec[j]) {
          std::swap(vec[i], vec[j]);
        }
      }
    }
  }
}
#include "insertion_sort.h"

namespace algotest {
  /**
   * best: O(n)  sorted list case
   * avg: O(n^2)
   */
  void insertion_sort(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    for (size_t i = 1; i < len; ++i) {
      const auto val = vec[i];
      auto j = i;                                // hole
      for (; j > 0 && vec[j - 1] > val; --j) {
        vec[j] = vec[j - 1];
      }
      vec[j] = val;
    }
  }
}
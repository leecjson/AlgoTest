#include "selection_sort.h"
//#include <type_traits>
//#include <algorithm>
#include <utility>

namespace algotest {
  /**
   * avg: O(n^2)
   */
  void selection_sort(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    /*std::decay_t<decltype(vec)>::iterator min_it;
    const auto end = vec.end();
    for (auto i = vec.begin(); i < (end-1); ++i) {
      min_it = i;
      for (auto j = i; j < end; ++j) {
        if (*j < *min_it) {
          min_it = j;
        }
      }
      if (min_it != i) {
        std::swap(*min_it, *i);
      }
    }*/

    const auto last = len - 1;
    for (size_t i = 0; i < last; ++i) {
      auto imin = i;
      for (auto j = i + 1; j < len; ++j) {
        if (vec[j] < vec[imin]) {
          imin = j;
        }
      }
      if (i != imin) {
        std::swap(vec[i], vec[imin]);
      }
    }
  }
}
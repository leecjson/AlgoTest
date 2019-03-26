#include "quick_sort.h"
#include <utility>

namespace {
  /**
   * lomuto partition，在输入完全正序的大数组排序中，pivot计算始终在最右侧。（完全倒序则在最左侧）
   * 会导致频繁的左递归，递归次数是n-1，将会触发stackoverflow。
   * 而理想的情况是，计算后的pivot应该接近于中心，从中心分割左右递归，这样递归的次数可以是log2(n)*n
   */
  size_t _lomuto_partition(std::vector<uint32_t>& vec, size_t first, size_t last) {
    auto pivot = vec[last];
    size_t p = first;
    for (size_t i = first; i < last; ++i) {
      if (vec[i] < pivot) {
        std::swap(vec[i], vec[p]);
        ++p;
      }
    }
    std::swap(vec[p], vec[last]);
    return p;
  }

  size_t _hoare_partition(std::vector<uint32_t>& vec, size_t first, size_t last) {
    const auto pivot = vec[(first + last) / 2];
    for (auto i = first - 1, j = last + 1;;) {
      do {
        ++i;
      } while (vec[i] < pivot);
      do {
        --j;
      } while (vec[j] > pivot);
      
      if (i >= j) {
        return j;
      }
      std::swap(vec[i], vec[j]);
    }
  }

  void _qsort(std::vector<uint32_t>& vec, size_t first, size_t last) {
    if (first < last) {
      size_t p = _hoare_partition(vec, first, last);
      if (p > 0) {
        _qsort(vec, first, p - 1);
      }
      _qsort(vec, p + 1, last);
    }
  }
}

namespace algotest {
  /**
   * worest case: O(n^2)
   * 
   * avg: O(log2(n))
   */
  void quick_sort(std::vector<uint32_t>& vec) {
    if (vec.size() > 1) {
      _qsort(vec, 0, vec.size() - 1);
    }
  }
}
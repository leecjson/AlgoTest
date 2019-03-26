#include "heap_sort.h"
#include <utility>

#define PARENT(__i) (((__i + 1) >> 1) - 1) // i/2  treat idx start from 1
#define LEFT(__i) (((__i + 1) << 1) - 1) // i*2
#define RIGHT(__i) (((__i + 1) << 1)) // i*2+1

namespace {
  /**
   * O(log2(n)) = O(h)
   */
  void _max_heapify(std::vector<uint32_t>& vec, size_t heap_size, size_t i = 0) {
    const auto left = LEFT(i), right = RIGHT(i);
    auto largest = left < heap_size && vec[left] > vec[i] ? left : i;
    if (right < heap_size && vec[right] > vec[largest])
      largest = right;

    if (largest != i) {
      std::swap(vec[i], vec[largest]);
      _max_heapify(vec, heap_size, largest);
    }
  }

  /**
   * theta(n*log2(n)) ... O(n)
   */
  void _build_max_heap(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    for (auto i = len >> 1; i-- > 0;) {
      _max_heapify(vec, len, i);
    }
  }
}

namespace algotest {
  void heap_sort(std::vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    _build_max_heap(vec);
    for (auto i = len; i-- > 1;) {
      std::swap(vec[0], vec[i]);
      _max_heapify(vec, i);
    }
  }
}
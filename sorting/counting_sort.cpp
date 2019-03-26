#include "selection_sort.h"
#include <utility>
#include <type_traits>

namespace algotest {
  //using size_t = std::vector<int32_t>::size_type;

  /**
   * 
   */
  /*void counting_sort(std::vector<int32_t>& vec, size_t range) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    std::vector<int32_t> indices(range, 0);
    for (const auto val : vec) {
      ++indices[val];
    }
    const auto last = len - 1;
    for (size_t i = 0, j = 1; j < len; ++i, ++j) {
      indices[j] = indices[i] + indices[j];
    }
    std::vector<int32_t> output(len);
    for (const auto val : vec) {
      output[--indices[val]] = val;
    }
    vec = std::move(output);
  }*/

  

  void counting_sort_with(std::vector<uint32_t>& vec, std::vector<uint32_t>& indices, std::vector<uint32_t>& output) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    std::fill(indices.begin(), indices.end(), 0);
    for (const auto val : vec) {
      ++indices[static_cast<size_t>(val)];
    }
    const auto range = indices.size();
    for (size_t i = 0, j = 1; j < range; ++i, ++j) {
      indices[j] = indices[i] + indices[j];
    }
    for (auto i = len; i-- > 0;) {
      const auto val = vec[i];
      output[static_cast<size_t>(--indices[static_cast<size_t>(val)])] = val;
    }
    vec = std::move(output); // swap memory
  }

  /**
   * theta(n)
   * @param value range of element (0 <= x < range)
   */
  void counting_sort(std::vector<uint32_t>& vec, uint32_t range) {
    counting_sort_with(vec, std::vector<uint32_t>(range), std::vector<uint32_t>(vec.size()));
  }
}
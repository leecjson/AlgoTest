#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace algotest {
  void counting_sort_with(std::vector<uint32_t>& vec, std::vector<uint32_t>& indices, std::vector<uint32_t>& output);
  void counting_sort(std::vector<uint32_t>& vec, uint32_t range);
}
#pragma once

#include <cstddef>
#include <cstdint>
#include <list>
#include <vector>


namespace algotest {
  void bucket_sort_with(std::vector<uint32_t>& vec, std::vector<std::list<uint32_t>> buckets);
  void bucket_sort(std::vector<uint32_t>& vec, size_t bucket_count);
}
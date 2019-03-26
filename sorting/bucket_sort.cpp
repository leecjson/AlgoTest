#include "bucket_sort.h"
#include <cmath>
#include <utility>

namespace {
  void _insertion_sort(std::list<uint32_t>& list) {
    if (list.size() < 2) {
      return;
    }
    const auto end = list.end();
    for (auto i = ++list.begin(); i != end; ++i) {
      const auto val = *i;
      auto j = i;
      auto prev_j = i;
      --prev_j;
      for (; prev_j != end && *prev_j > val; j = prev_j--) {
        *j = *prev_j;
      }
      *j = val;
    }
  }
}

namespace algotest {
  void bucket_sort_with(std::vector<uint32_t>& vec, std::vector<std::list<uint32_t>> buckets) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    const auto bucket_count = buckets.size();
    if (bucket_count == 0) {
      return;
    }

    auto max = vec[0];
    for (size_t i = 1; i < len; ++i) {
      if (vec[i] > max) {
        max = vec[i];
      }
    }
    for (const auto val : vec) {
      const auto index = static_cast<size_t>((double)val / (double)max * (double)(bucket_count - 1));
      buckets[index].push_back(val);
    }
    size_t i = 0;
    for (auto& bkt : buckets) {
      _insertion_sort(bkt);
      for (const auto val : bkt) {
        vec[i++] = val;
      }
    }
  }

  void bucket_sort(std::vector<uint32_t>& vec, size_t bucket_count) {
    bucket_sort_with(vec, std::vector<std::list<uint32_t>>(bucket_count));
  }
}
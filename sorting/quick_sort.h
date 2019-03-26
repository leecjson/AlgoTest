#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace algotest {
  void quick_sort(std::vector<uint32_t>& vec);

  //template<typename It, typename Pred>
  //static It _lomuto_partition(It first, It last, Pred pred) {
  //  It p = first;
  //  for (It i = first; i < last; ++i) {
  //    if (pred(*i, *last)) {
  //      std::swap(*i, *p);
  //      ++p;
  //    }
  //  }
  //  std::swap(*p, *last);
  //  return p;
  //}

  //template<typename It, typename Pred>
  //static void _qsort(It first, It last, Pred pred) {
  //  if (first < last) {
  //    It p = _lomuto_partition(first, last, pred);
  //    if (p > first) {
  //      _qsort(first, p - 1, pred); // left part
  //    }
  //    _qsort(p + 1, last, pred); // right part
  //  }
  //}

  //template<typename It, typename Pred>
  //static inline void quick_sort(It start, It finish, Pred pred) {
  //  It first = start,
  //    last = finish - 1;
  //  if (first > last) {
  //    throw std::range_error("invalid iterator");
  //  } else if (first == last) {
  //    return;
  //  }
  //  _qsort(first, last, pred);
  //}
}
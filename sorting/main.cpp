#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstdint>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <utility>

#include "quick_sort.h"
#include "insertion_sort.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "selection_sort.h"
#include "bubble_sort.h"
#include "counting_sort.h"
#include "radix_sort.h"
#include "bucket_sort.h"

namespace {
  using namespace std;
  using namespace std::chrono;

  template<typename TFunc, typename... TArgs>
  auto Measure(const TFunc& fn, TArgs&&... args) {
    //const auto start_time = system_clock::now();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    fn(forward<TArgs>(args)...);
    //const auto end_time = system_clock::now();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    //duration<double> elapsed_seconds = end_time - start_time;
    duration<double> elapsed_seconds = duration_cast<duration<double>>(t2 - t1);
    return elapsed_seconds.count() * 1000;
  }
}

namespace sorting {
  using namespace std;
  using SortFn = function<void(vector<uint32_t>&)>;

  void stdsort(vector<uint32_t>& vec) {
    std::sort(vec.begin(), vec.end());
  }

  void clib_qsort(vector<uint32_t>& vec) {
    const auto len = vec.size();
    if (len < 2) {
      return;
    }
    uint32_t* ptr = vec.data();
    qsort(ptr, len, sizeof(uint32_t), [](const void* a, const void* b) -> int {
      uint32_t arg1 = *static_cast<const uint32_t*>(a);
      uint32_t arg2 = *static_cast<const uint32_t*>(b);

      if (arg1 < arg2) return -1;
      if (arg1 > arg2) return 1;
      return 0;
    });
  }

  bool Check(const vector<uint32_t>& ret) {
    size_t len = ret.size();
    if (len == 0) {
      return false;
    }
    else if (len == 1) {
      return true;
    }
    for (size_t i = 0, j = 1; j < len; ++i, ++j) {
      if (ret[i] > ret[j]) {
        return false;
      }
    }
    return true;
  }

  auto MeasureRandomCase(size_t num, const SortFn& fn) {
    vector<uint32_t> vec(num);
    for (decltype(num) i = 0; i < num; ++i) {
      vec[i] = static_cast<uint32_t>(rand());
    }
    return Measure(fn, vec);
  }

  auto MeasureAscendingOrderCase(size_t num, const SortFn& fn) {
    vector<uint32_t> vec(num);
    for (decltype(num) i = 0; i < num; ++i) {
      vec[i] = static_cast<uint32_t>(i);
    }
    return Measure(fn, vec);
  }

  auto MeasureDescendingOrderCase(size_t num, const SortFn& fn) {
    vector<uint32_t> vec(num);
    for (auto i = num; i-- > 0;) {
      vec[i] = static_cast<uint32_t>(i);
    }
    return Measure(fn, vec);
  }

  void _foreach_sorting(const vector<pair<string, SortFn>>& fn_list, function<void (const SortFn&)> each) {
    for (const auto& fn : fn_list) {
      cout << fn.first.c_str() << " start: ";
      each(fn.second);
    }
  }

  void RunSortingTest(size_t num, const vector<pair<string, SortFn>>& fn_list) {
    const auto start_task = [num](const string& name) {
      cout << name << ":" << " (" << num << ")" << " --------------------------------" << endl;
    };
    const auto end_task = []() {
      cout << endl;
    };
    const auto foreach_sorting = [](auto&& fn_list, auto&& each) {
      for (const auto& fn : fn_list) {
        cout << fn.first.c_str() << " start: ";
        auto time = each(fn.second);
        cout << "finish in " << time << "s" << endl;
      }
    };

    start_task("Random Test");
    foreach_sorting(fn_list, [num](const SortFn& sort_fn) {
      return MeasureRandomCase(num, sort_fn);
    });
    end_task();

    start_task("Ascending Order Test");
    foreach_sorting(fn_list, [num](const SortFn& sort_fn) {
      return MeasureAscendingOrderCase(num, sort_fn);
    });
    end_task();

    start_task("Descending Order Test");
    foreach_sorting(fn_list, [num](const SortFn& sort_fn) {
      return MeasureDescendingOrderCase(num, sort_fn);
    });
    end_task();

  }
}

int main()
{
  using namespace std;

  static_assert(sizeof(size_t) == sizeof(vector<int>::size_type), "env error");
  srand((unsigned int)time(nullptr));

  vector<pair<string, sorting::SortFn>> tasks = {
    make_pair("bubble_sort", algotest::bubble_sort),
    make_pair("insertion_sort", algotest::insertion_sort),
    make_pair("selection_sort", algotest::selection_sort),
    make_pair("std::sort", sorting::stdsort),
    make_pair("qsort", sorting::clib_qsort),
    make_pair("quick_sort", algotest::quick_sort),
    make_pair("heap_sort", algotest::heap_sort),
    make_pair("merge_sort", algotest::merge_sort),
    make_pair("radix_sort", algotest::radix_sort),
  };
  sorting::RunSortingTest(10, tasks);
  sorting::RunSortingTest(100, tasks);
  sorting::RunSortingTest(2048, tasks);

  vector<pair<string, sorting::SortFn>> tasks_of_running_fast = {
    make_pair("std::sort", sorting::stdsort),
    make_pair("qsort", sorting::clib_qsort),
    make_pair("quick_sort", algotest::quick_sort),
    make_pair("heap_sort", algotest::heap_sort),
    make_pair("merge_sort", algotest::merge_sort),
    make_pair("radix_sort", algotest::radix_sort),
    make_pair("bucket_sort", std::bind(algotest::bucket_sort, placeholders::_1, RAND_MAX)),
  };

  sorting::RunSortingTest(10000000, tasks_of_running_fast);

  getchar();
  return 0;
}
#include "merge_sort.h"
#include <utility>

namespace {

  /**
   *   A ... left_sub_A ... right_sub_A
   *
   *  [12, 72, 82, 4, 56, 6, 90, 5, 4, 12, 72, 82, 5, 6, 56, 90] end
   *   ¡ü                            ¡ü              ¡ü             ¡ü
   *   dstart                       lstart         rstart        stk_size
   *   ¡ü                            ¡ý              ¡ý             ¡ý
   *   ¡ü                            ¡ú - - - - - -  megre - - - - ¡û
   *   ¡ü                                           ¡ý
   *   ¡ü ¡û ¡û ¡û ¡û ¡û overwrite ¡û ¡û ¡û ¡û ¡û ¡û ¡û ¡û ¡û ¡û ¡û ¡û
   *
   */
  //void _merge(std::vector<int32_t>& vec, size_t dstart, size_t lstart, size_t rstart, size_t rend) noexcept {
  //  auto i = lstart,
  //    j = rstart,
  //    k = dstart;
  //  const auto lend = rstart;
  //  for (; i < lend && j < rend; ++k) {
  //    if (vec[i] <= vec[j]) {       // if (L[i] <= R[j])   left less then right
  //      vec[k] = vec[i];            // A[k] = L[i]
  //      ++i;
  //    } else {
  //      vec[k] = vec[j];            // A[k] = R[j]
  //      ++j;
  //    }
  //  }
  //  for (; i < lend; ++i, ++k) {
  //    vec[k] = vec[i];
  //  }
  //  for (; j < rend; ++j, ++k) {
  //    vec[k] = vec[j];
  //  }
  //}

  /**
   *  [12, 72, 82, 4, 56, 6, 90, 5, 12, 72, 82, 4, 56, 6, 90, 5] end
   *   ¡ü              ¡ü             ¡ü              ¡ü             ¡ü
   *   s_start(in)    mid(relative) s_end(in)      ¡ü             ¡ü
   *   ¡ü              ¡ü             ¡ü              ¡ü             ¡ü
   *   s_lstart ----> s_lend        ¡ü              ¡ü             ¡ü
   *   ¡ý              ¡ü             ¡ü              ¡ü             ¡ü
   *   ¡ý              s_rstart ---> s_rend         ¡ü             ¡ü
   *   ¡ý              ¡ý             ¡ü              ¡ü             ¡ü
   *   ¡ý              ¡ý             d_lstart ----> d_lend        ¡ü
   *   ¡ý              ¡ý             ¡ü              ¡ü             ¡ü
   *   ¡ý              ¡ý             ¡ü              d_rstart ---> d_rend
   *   ¡ý              ¡ý             ¡ü              ¡ü
   *   ¡ý              ¡ý             ¡ü              ¡ü
   *   ¡ý              ¡ý             ¡ü              ¡ü
   *   ¡ú ¡ú copy ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ü              ¡ü
   *                  ¡ý                            ¡ü
   *                  ¡ú ¡ú ¡ú copy ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ú ¡ü
   *
   */
  //void _merge_sort(std::vector<int32_t>& vec, size_t s_start, size_t s_end) noexcept {
  //  const auto subsize = s_end - s_start;
  //  const auto mid = subsize >> 1,   // subsize/2 = mid = length(L)
  //    rest = (subsize - mid);        // length(sub) - length(A) = rest = length(R)

  //  const auto s_lstart = s_start,
  //    s_rstart = s_lstart + mid,
  //    d_lstart = s_end,
  //    d_rstart = d_lstart + mid,
  //    d_rend = d_rstart + rest;

  //  const auto start_it = vec.begin();
  //  std::copy(start_it + s_lstart, start_it + s_rstart, start_it + d_lstart);
  //  if (mid > 1) { // length(L) > 1
  //    _merge_sort(vec, d_lstart, d_rstart);
  //  }

  //  std::copy(start_it + s_rstart, start_it + d_lstart, start_it + d_rstart);
  //  if (rest > 1) { // length(R) > 1
  //    _merge_sort(vec, d_rstart, d_rend);
  //  }

  //  _merge(vec, s_start, d_lstart, d_rstart, d_rend);
  //}

  /**
   * merge A[start...mid...end] to B[start...end]
   */
  void _merge(std::vector<uint32_t>& A, std::vector<uint32_t>& B, size_t start, size_t mid, size_t end) {
    for (auto i = start, j = mid, k = start; k < end; ++k) {
      if (i < mid && (j >= end || A[i] <= A[j])) {
        B[k] = A[i];
        ++i;
      } else {
        B[k] = A[j];
        ++j;
      }
    }
  }

  /**
   * sort the given run of array B[] using array A[] as a source.   merge A[start...end] to B[start...end]
   *
   *     workspace           input
   *     [8,7,6,5,4,3,2,1]   [8,7,6,5,4,3,2,1]
   *
   *  1: {...}               {...}
   *     [8,7,6,5,4,3,2,1] ¡ú [7,8,6,5,4,3,2,1]
   *
   *  2:     {...}               {...}
   *     [8,7,6,5,4,3,2,1] ¡ú [7,8,5,6,4,3,2,1]
   *
   *  3: {.......}           {.......}
   *     [5,6,7,8,4,3,2,1] ¡û [7,8,5,6,4,3,2,1]
   * 
   *  4:         {...}               {...}
   *     [5,6,7,8,4,3,2,1] ¡ú [5,6,7,8,3,4,2,1]
   *
   *  5:             {...}               {...}
   *     [5,6,7,8,4,3,2,1] ¡ú [5,6,7,8,3,4,1,2]
   *
   *  6:         {.......}           {.......}
   *     [5,6,7,8,1,2,3,4] ¡û [5,6,7,8,3,4,1,2]
   *
   *  7: {...............}   {...............}
   *     [5,6,7,8,1,2,3,4] ¡ú [1,2,3,4,5,6,7,8]
   *
   */
  void _merge_sort(std::vector<uint32_t>& A, std::vector<uint32_t>& B, size_t start, size_t end) {
    if (end - start < 2)
      return;

    const auto mid = (end + start) / 2;
    _merge_sort(B, A, start, mid);
    _merge_sort(B, A, mid, end);
    _merge(A, B, start, mid, end); // merge A->B
  }
}

namespace algotest {
  /**
   * worest: O(n*log2(n))
   * best: O(n*log2(n)/2)
   * extra memory: O(n)
   */
  void merge_sort(std::vector<uint32_t>& vec) {
    //const auto n = vec.size();
    //if (n < 2) {
    //  return;
    //}
    //vec.resize(n * 3 + 1); // 3n + n
    //_merge_sort(vec, 0, n);
    //vec.resize(n);

    std::vector<uint32_t> workspace = vec;
    _merge_sort(workspace, vec, 0, vec.size());
  }
}
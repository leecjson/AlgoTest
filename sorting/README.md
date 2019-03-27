[Open in GitHub](https://github.com/leecjson/AlgoTest/tree/master/sorting)  

## O(n^2)的排序算法

* insertion sort 插入排序
* bubble sort 冒泡排序
* selection sort 选择排序

其中bubble_sort和selection_sort是比较垃圾的，它们都需要完全的n^2次操作，insertion_sort稍微有点不一样的是，在完全正序和完全倒序的输入下，它的运行时间复杂度是O(n)，在大约是正序和大约是倒序的输入下，它的时间接近O(n)。在输入随机顺序的情况下，这几个算法都不适用于大数组排序，insertion_sort只有在大数组几乎已经排序的情况下，才能有一个比较好的运行时间。这几个算法都不能利用多核多计算机并行化计算。但是在小数组排序中可以看到insertion_sort和selection_sort有相对优势，其中可以分析出的是，数组如果足够小，就容易维持在CPU的高速缓存，而且相比其它算法，其它直接了当的在循环中完成，而非递归，因此没有栈上的沉没成本。quick_sort其中的一个优化方案就是在递归层级上的n如果在一个非常小的值，就直接采用insertion_sort实现，代替继续的分割递归。

## O(n*log2(n))的排序算法

* heap sort 堆排序
* merge sort 合并排序
* quick sort 快速排序

heap_sort其实就是一个放在数组里的最大二叉堆，需要每次输出都重新修正堆，它最大堆的优点在于有一个构建好的堆进行变动后能够很快的重新排序，其它算法则大多是完全重新处理，建堆是一次性的沉没成本，如果随后的变动操作足够频繁，则最大堆的优势非常明显。megre_sort和quick_sort较为相似，它们都使用分而治之的思想，一个问题划分为两个相同的子问题，两个划分为四个。从直观上来讲，这样的算法天生就可以两个cpu并行运行。merge_sort的区别是它需要一个大小为n的额外空间作为工作空间，在理论上merge_sort和quick_sort运行时间应该差不多，而实际上总是quick_sort更快一些，因为quick_sort是原址排序，原址意味所有操作在原处进行，它会产生更少的上下文切换（概念上的），更能利用CPU高速缓存。在正序和倒序的输入下，quick_sort也能有非常少的交换次数，总体来看quick_sort的运行情况最稳定，在各种情况下也是平均最快的算法。

## θ(n)的排序算法

* counting sort 计数排序
* bucket sort 桶排序
* radix sort (θ(d*(n+k))) 基数排序

这几个算法是满足特殊条件下最快的排序算法，它们都把待排序的值当成数字处理，以数值直接变换为下标运算。counting_sort要求知道数值的具体范围，而且范围不能太大，bucket_sort要根据具体的情况设置桶的数量，当然是桶越多运行时间越快，但是空间占用越大，同时它也要求知道数值的具体范围，范围不能过大。radix_sort是基于counting_sort的一种实现，它只要求要排序的值是数字即可，不要求范围，radix_sort是一种相对比较稳定和更通用化的算法，在大数组排序中甚至能超越quick_sort。  

最后分享一个很有趣的Video : [15 Sorting Algorithms in 6 Minutes](https://www.youtube.com/watch?v=kPRA0W1kECg)

## 测试用例

以下给出一些测试用例，分别是完全随机的输入，完全正序的输入和完全倒序的输入，每一组测试都使用不同的数组长度。

### Random Test: (10)
Function|Cost
----|----
insertion_sort|0.000255ms
selection_sort|0.000511ms
std::sort|0.000511ms
quick_sort|0.000511ms
heap_sort|0.000511ms
bubble_sort|0.000767ms
qsort|0.001022ms
merge_sort|0.001022ms
radix_sort|0.002044ms

### Ascending Order Test: (10)
Function|Cost
----|----
insertion_sort|0ms
selection_sort|0.000255ms
std::sort|0.000255ms
bubble_sort|0.000511ms
quick_sort|0.000511ms
heap_sort|0.000511ms
qsort|0.000766ms
radix_sort|0.001022ms
merge_sort|0.002555ms

### Descending Order Test: (10)
Function|Cost
----|----
std::sort|0ms
selection_sort|0.000255ms
quick_sort|0.000255ms
insertion_sort|0.000256ms
bubble_sort|0.000511ms
qsort|0.000511ms
heap_sort|0.000511ms
merge_sort|0.000767ms
radix_sort|0.000767ms

### Random Test: (100)
Function|Cost
----|----
insertion_sort|0.002044ms
std::sort|0.00281ms
heap_sort|0.003321ms
quick_sort|0.003577ms
radix_sort|0.00511ms
merge_sort|0.005621ms
selection_sort|0.00741ms
qsort|0.007664ms
bubble_sort|0.014052ms

### Ascending Order Test: (100)
Function|Cost
----|----
insertion_sort|0.000256ms
std::sort|0.000767ms
quick_sort|0.001533ms
radix_sort|0.002555ms
heap_sort|0.00281ms
merge_sort|0.003066ms
qsort|0.003576ms
selection_sort|0.005366ms
bubble_sort|0.006643ms

### Descending Order Test: (100)
Function|Cost
----|----
insertion_sort|0.000511ms
std::sort|0.000766ms
quick_sort|0.001788ms
heap_sort|0.00281ms
radix_sort|0.00281ms
merge_sort|0.003065ms
qsort|0.003577ms
selection_sort|0.005621ms
bubble_sort|0.006387ms

### Random Test: (2048)
Function|Cost
----|----
heap_sort|0.076646ms
radix_sort|0.08099ms
std::sort|0.086611ms
quick_sort|0.09402ms
merge_sort|0.144351ms
qsort|0.206435ms
insertion_sort|0.438419ms
selection_sort|1.92511ms
bubble_sort|3.52856ms

### Ascending Order Test: (2048)
Function|Cost
----|----
insertion_sort|0.002044ms
std::sort|0.012008ms
quick_sort|0.01303ms
merge_sort|0.04982ms
heap_sort|0.062595ms
radix_sort|0.064639ms
qsort|0.076646ms
selection_sort|1.93814ms
bubble_sort|2.11979ms

### Descending Order Test: (2048)
Function|Cost
----|----
insertion_sort|0.001789ms
std::sort|0.011753ms
quick_sort|0.012775ms
merge_sort|0.04982ms
heap_sort|0.063106ms
radix_sort|0.064639ms
qsort|0.076646ms
selection_sort|1.94453ms
bubble_sort|2.20998ms

### Random Test: (100000)
Function|Cost
----|----
radix_sort|4.08399ms
heap_sort|5.81646ms
std::sort|5.97896ms
quick_sort|6.19254ms
merge_sort|9.64855ms
qsort|14.2272ms
insertion_sort|1010.97ms
selection_sort|4314.77ms
bubble_sort|16228.6ms

### Ascending Order Test: (100000)
Function|Cost
----|----
insertion_sort|0.092487ms
quick_sort|0.827274ms
std::sort|0.926404ms
merge_sort|3.1369ms
radix_sort|4.09191ms
heap_sort|4.56585ms
qsort|4.97718ms
selection_sort|4496.34ms
bubble_sort|5119.64ms

### Descending Order Test: (100000)
Function|Cost
----|----
insertion_sort|0.091976ms
quick_sort|0.817566ms
std::sort|0.926659ms
merge_sort|3.15095ms
radix_sort|4.08016ms
heap_sort|4.55026ms
qsort|4.9897ms
selection_sort|4515.32ms
bubble_sort|5099.9ms

### Random Test: (10000000)
Function|Cost
----|----
radix_sort|438.893ms
std::sort|575.052ms
quick_sort|654.543ms
merge_sort|1142.97ms
qsort|1280.58ms
heap_sort|3013.18ms
bucket_sort|3491.35ms

### Ascending Order Test: (10000000)
Function|Cost
----|----
quick_sort|104.541ms
std::sort|143.37ms
merge_sort|398.077ms
radix_sort|603.373ms
heap_sort|666.731ms
qsort|688.126ms
bucket_sort|836.04ms

### Descending Order Test: (10000000)
Function|Cost
----|----
quick_sort|104.082ms
std::sort|141.883ms
merge_sort|395.885ms
radix_sort|599.715ms
heap_sort|669.701ms
qsort|685.884ms
bucket_sort|828.724ms
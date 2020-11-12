#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <stdlib.h>
#include <vector>
using namespace std::chrono;
using namespace std;

// Get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
// Print an array
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

void countingSort(int arr[], int n, int exp)
{
    int res[n];
    int i, count[10] = { 0 };
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        res[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    // Copy the output array to arr[], so that arr[] contains sorted numbers
    for (i = 0; i < n; i++)
        arr[i] = res[i];
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);   // Find the maximum number to know number of digits
    for (int exp = 1; m / exp > 0; exp *= 10)   // Do counting sort for every digit.
        countingSort(arr, n, exp);
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    // Copy data to temp arrays L[] and R[]
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // Merge the temp arrays back into arr[l..r]
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy the remaining elements of L[]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copy the remaining elements of R[]
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Avoids overflow for large l and h
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_index;
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j] < arr[min_index])
            min_index = j;
        // Swap the found minimum element with the first element
        swap(&arr[min_index], &arr[i]);
    }
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
      for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

//Average function
 std::chrono::duration<long int, std::micro> average(vector<std::chrono::duration<long  int, std::micro>> v){
  std::chrono::duration<long int, std::micro> avg = v[0];
  for(int i = 1; i < v.size(); i++){
    avg = avg + v[i];
  }
  std::chrono::duration<long int, std::micro> res = (avg / v.size()) ;
  return res;
}

int main()
{
  int maxnum = 10;
  vector<std::chrono::duration<long int, std::micro>> tRadix;
  vector<std::chrono::duration<long int, std::micro>> tMerge;
  vector<std::chrono::duration<long int, std::micro>> tQuick;
  vector<std::chrono::duration<long int, std::micro>> tSelec;
  vector<std::chrono::duration<long int, std::micro>> tBubbl;
  for(int i = 0; i <= 100; i++){
    int arr1[maxnum];
    int arr2[maxnum];
    int arr3[maxnum];
    int arr4[maxnum];
    int arr5[maxnum];
    for(int j = 0; j < maxnum; j ++){
      arr1[j] = rand() % maxnum+1;
      arr2[j] = rand() % maxnum+1;
      arr3[j] = rand() % maxnum+1;
      arr4[j] = rand() % maxnum+1;
      arr5[j] = rand() % maxnum+1;
   }//for j

    int n = sizeof(arr3) / sizeof(arr3[0]);

    auto start1 = high_resolution_clock::now();
    radixsort(arr1, n);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    tRadix.push_back(duration1);

    auto start2 = high_resolution_clock::now();
    mergeSort(arr2, 0, n-1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    tMerge.push_back(duration2);

    auto start3 = high_resolution_clock::now();
    quickSort(arr3, 0, n-1);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    tQuick.push_back(duration3);

    auto start4 = high_resolution_clock::now();
    selectionSort(arr4, n);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    tSelec.push_back(duration4);

    auto start5 = high_resolution_clock::now();
    bubbleSort(arr5, n);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    tBubbl.push_back(duration5);
  }//for i
  auto radixT = duration_cast<microseconds>(average(tRadix)) ;
  cout << "Average time(microseconds) for Radix sort was: " << radixT.count() << " for " << " size. " << maxnum << endl;

  auto mergeT = duration_cast<microseconds>(average(tMerge)) ;
  cout << "Average time(microseconds) for Merge sort was: " << mergeT.count() << " for " << " size. " << maxnum << endl;

  auto quickT = duration_cast<microseconds>(average(tQuick)) ;
  cout << "Average time(microseconds) for Quick sort was: " << quickT.count() << " for " << " size. " << maxnum << endl;

  auto selecT = duration_cast<microseconds>(average(tSelec)) ;
  cout << "Average time(microseconds) for Selec sort was: " << selecT.count() << " for " << " size. " << maxnum << endl;

  auto bubblT = duration_cast<microseconds>(average(tBubbl)) ;
  cout << "Average time(microseconds) for Bubbl sort was: " << bubblT.count() << " for " << " size. " << maxnum << endl;

  return 0;
}

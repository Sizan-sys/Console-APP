#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Function to generate N random numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> numbers;
    srand(time(0));
    for (int i = 0; i < N; i++) {
        numbers.push_back(rand() % 1000); // Random numbers between 0 and 999
    }
    return numbers;
}

// Binary Search
int binarySearch(const vector<int>& arr, int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search
int interpolationSearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));
        if (arr[pos] == key) return pos;
        if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Merge Sort Helper Function
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Merge Sort Algorithm
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to measure execution time
void measureExecutionTime(int N) {
    vector<int> numbers = generateRandomNumbers(N);
    vector<int> sortedNumbers = numbers;

    // Sorting required before searching
    sort(sortedNumbers.begin(), sortedNumbers.end());

    int key = sortedNumbers[N / 2]; // Middle element as search key

    cout << "\nN = " << N << " elements:\n";

    // Measure Binary Search
    auto start = high_resolution_clock::now();
    binarySearch(sortedNumbers, 0, N - 1, key);
    auto stop = high_resolution_clock::now();
    cout << "Binary Search Time: " << duration_cast<microseconds>(stop - start).count() << " µs\n";

    // Measure Interpolation Search
    start = high_resolution_clock::now();
    interpolationSearch(sortedNumbers, key);
    stop = high_resolution_clock::now();
    cout << "Interpolation Search Time: " << duration_cast<microseconds>(stop - start).count() << " µs\n";

    // Measure Selection Sort
    vector<int> selectionSorted = numbers;
    start = high_resolution_clock::now();
    selectionSort(selectionSorted);
    stop = high_resolution_clock::now();
    cout << "Selection Sort Time: " << duration_cast<microseconds>(stop - start).count() << " µs\n";

    // Measure Merge Sort
    vector<int> mergeSorted = numbers;
    start = high_resolution_clock::now();
    mergeSort(mergeSorted, 0, N - 1);
    stop = high_resolution_clock::now();
    cout << "Merge Sort Time: " << duration_cast<microseconds>(stop - start).count() << " µs\n";
}

int main() {
    measureExecutionTime(100);
    measureExecutionTime(500);
    measureExecutionTime(1000);
    measureExecutionTime(5000);
    measureExecutionTime(10000);

    return 0;
}


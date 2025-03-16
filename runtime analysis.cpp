#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Function to generate N random numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> numbers;
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < N; i++) {
        numbers.push_back(rand() % 1000); // Generates numbers between 0 and 999
    }
    return numbers;
}

// Binary Search Algorithm
int binarySearch(const vector<int>& arr, int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search Algorithm
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

// Selection Sort Algorithm
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

int main() {
    cout << "N,SelectionSort,MergeSort,BinarySearch,InterpolationSearch\n";

    for (int N = 1000; N <= 10000; N += 1000) {
        vector<int> numbers = generateRandomNumbers(N);

        // Measure Selection Sort Runtime
        auto start = chrono::high_resolution_clock::now();
        vector<int> selectionSorted = numbers;
        selectionSort(selectionSorted);
        auto end = chrono::high_resolution_clock::now();
        double selectionSortTime = chrono::duration<double>(end - start).count();

        // Measure Merge Sort Runtime
        start = chrono::high_resolution_clock::now();
        vector<int> mergeSorted = numbers;
        mergeSort(mergeSorted, 0, N - 1);
        end = chrono::high_resolution_clock::now();
        double mergeSortTime = chrono::duration<double>(end - start).count();

        // Measure Binary Search Runtime
        int key = rand() % 1000; // Random key to search
        start = chrono::high_resolution_clock::now();
        binarySearch(mergeSorted, 0, N - 1, key);
        end = chrono::high_resolution_clock::now();
        double binarySearchTime = chrono::duration<double>(end - start).count();

        // Measure Interpolation Search Runtime
        start = chrono::high_resolution_clock::now();
        interpolationSearch(mergeSorted, key);
        end = chrono::high_resolution_clock::now();
        double interpolationSearchTime = chrono::duration<double>(end - start).count();

        // Output runtime data
        cout << N << "," << selectionSortTime << "," << mergeSortTime << ","
             << binarySearchTime << "," << interpolationSearchTime << "\n";
    }

    return 0;
}

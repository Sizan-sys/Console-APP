#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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

// Binary Search Algorithm (Requires sorted array)
int binarySearch(const vector<int>& arr, int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid; // Key found
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // Key not found
}

// Interpolation Search Algorithm (Requires sorted array)
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

// Function to print an array
void printArray(const vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

int main() {
    int N, key;
    
    cout << "Enter number of random elements (N): ";
    cin >> N;

    vector<int> numbers = generateRandomNumbers(N);

    cout << "\nGenerated Random Numbers:\n";
    printArray(numbers);

    // Sorting using Selection Sort
    vector<int> selectionSorted = numbers;
    selectionSort(selectionSorted);
    cout << "\nSorted Numbers (Selection Sort):\n";
    printArray(selectionSorted);

    // Sorting using Merge Sort
    vector<int> mergeSorted = numbers;
    mergeSort(mergeSorted, 0, N - 1);
    cout << "\nSorted Numbers (Merge Sort):\n";
    printArray(mergeSorted);

    cout << "\nEnter number to search: ";
    cin >> key;

    // Perform Binary Search
    int binaryResult = binarySearch(mergeSorted, 0, N - 1, key);
    if (binaryResult != -1) cout << "Binary Search: Element found at index " << binaryResult << endl;
    else cout << "Binary Search: Element not found!\n";

    // Perform Interpolation Search
    int interpolationResult = interpolationSearch(mergeSorted, key);
    if (interpolationResult != -1) cout << "Interpolation Search: Element found at index " << interpolationResult << endl;
    else cout << "Interpolation Search: Element not found!\n";

    return 0;
}

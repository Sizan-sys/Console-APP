#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform binary search
int binarySearch(const vector<int>& arr, int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Function to perform interpolation search
int interpolationSearch(const vector<int>& arr, int n, int x) {
    int lo = 0, hi = (n - 1);

    while (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
        if (lo == hi) {
            if (arr[lo] == x) return lo;
            return -1;
        }

        int pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        if (arr[pos] == x)
            return pos;

        if (arr[pos] < x)
            lo = pos + 1;
        else
            hi = pos - 1;
    }
    return -1;
}

// Function to perform selection sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// Function to merge two halves for merge sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    int N, element;
    cout << "10: ";
    cin >> N;

    vector<int> arr(N);
    cout << "54: ";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    cout << "87: ";
    cin >> element;

    // Sorting the array before performing binary and interpolation search
    mergeSort(arr, 0, N - 1);

    // Display sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Perform binary search
    int result = binarySearch(arr, 0, N - 1, element);
    if (result != -1)
        cout << "Element found at index (Binary Search): " << result << endl;
    else
        cout << "Element not found (Binary Search)" << endl;

    // Perform interpolation search
    result = interpolationSearch(arr, N, element);
    if (result != -1)
        cout << "Element found at index (Interpolation Search): " << result << endl;
    else
        cout << "Element not found (Interpolation Search)" << endl;

    return 0;
}

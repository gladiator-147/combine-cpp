#include <iostream>
#include <vector>
using namespace std;

struct MinMax {
    int min;
    int max;
};

// Divide and Conquer function to find min and max
MinMax findMinMax(const vector<int>& arr, int low, int high) {
    MinMax result, left, right;

    // If only one element
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }

    // If two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    // If more than two elements
    int mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Compare results of left and right halves
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);

    return result;
}

int main() {
    int n;
    cout << "Enter number of elements in the list: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    MinMax result = findMinMax(arr, 0, n - 1);

    cout << "\nMinimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl;

    return 0;
}

#include <bits/stdc++.h>
#include <random>
#include <windows.h>
#include <process.h>

using namespace std;

/*
variableName
functionName
SignalName
ConstantName
attribute_name
*/

namespace utility {
    template <typename T>
    int printVector(vector<T> vec) {
        if (vec.empty()) {
            return -1;
        }
        cout << '{';
        for (int i = 0; i < vec.size(); i++) {
            if (i == vec.size() - 1) {
                cout << vec[i] << '}' << '\n';
                continue;
            }
            cout << vec[i] << ", ";
        }
        return 1;
    }
    template <typename T>
    bool isSorted(vector<T> vec) {
        vector<T> sorted = vec;
        sort(sorted.begin(), sorted.end());
        return sorted == vec;
    }
    vector<int> generateRandomVector(int size, int range_start, int range_end,
        bool onlyUniqueNumbers = false) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(range_start, range_end);

        vector<int> randomVector;

        if (onlyUniqueNumbers) {
            if (size < range_end - range_start) {
                cerr
                    << "Error: Cannot generate more unique numbers than the range allows."
                    << endl;
                return randomVector;
            }
            vector<int> uniqueNumbers;
            for (int i = range_start; i <= range_end; i++) {
                uniqueNumbers.push_back(i);
            }

            shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), gen);

            for (int i = 0; i < size; i++) {
                randomVector.push_back(uniqueNumbers[i]);
            }
        }
        else {
            for (int i = 0; i < size; i++) {
                int randomValue = dist(gen);
                randomVector.push_back(randomValue);
            }
        }

        return randomVector;
    }
}

namespace ultimateSort {
    void countSort(vector<int>* vec) {
        if (vec == nullptr || vec->empty()) {
            return;
        }

        int maxVal = *max_element(vec->begin(), vec->end());
        int minVal = *min_element(vec->begin(), vec->end());

        vector<int> buckets(maxVal - minVal + 1, 0);

        for (int i = 0; i < vec->size(); i++) {
            buckets[(*vec)[i] - minVal]++;
        }

        int index = 0;
        for (int i = 0; i < buckets.size(); i++) {
            while (buckets[i] > 0) {
                (*vec)[index] = i + minVal;
                index++;
                buckets[i]--;
            }
        }
    }

    void bogoSort(vector<int>* vec) {
        if (vec == nullptr || vec->empty()) {
            return;
        }

        while (!utility::isSorted(*vec)) {
            random_device rd;
            mt19937 gen(rd());
            shuffle(vec->begin(), vec->end(), gen);
        }
    }

    void selectionSort(vector<int>* vec) {
        if (vec == nullptr || vec->empty()) {
            return;
        }

        int minIndex;

        for (int i = 0; i < vec->size() - 1; i++) {
            minIndex = i;
            for (int j = i + 1; j < vec->size(); j++) {
                if ((*vec)[minIndex] > (*vec)[j]) {
                    minIndex = j;
                }
            }

            swap((*vec)[i], (*vec)[minIndex]);
        }
    }

    void heapify(vector<int>& arr, int n, int i) {
        int largestNumber = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largestNumber])
            largestNumber = left;

        if (right < n && arr[right] > arr[largestNumber])
            largestNumber = right;

        if (largestNumber != i) {
            swap(arr[i], arr[largestNumber]);
            heapify(arr, n, largestNumber);
        }
    }

    void heapSort(vector<int>& vec) {
        int n = vec.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(vec, n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(vec[0], vec[i]);
            heapify(vec, i, 0);
        }
    }

    void insertionSort(vector<int>* vec) {
        if (vec == nullptr || vec->empty()) {
            return;
        }

        for (int i = 1; i < vec->size(); i++) {
            int val = (*vec)[i];
            int n = i;
            while (n > 0 && (*vec)[n - 1] > val) {
                (*vec)[n] = (*vec)[n - 1];
                n -= 1;
            }
            (*vec)[n] = val;
        }
    }

    void bubbleSort(vector<int>* vec) {
        if (vec == nullptr || vec->empty()) {
            return;
        }

        for (int i = vec->size() - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (vec[j] > vec[j + 1]) {
                    swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
    void beadSort(vector<int>& vec) {
        int len = vec.size();
        int max = vec[0];
        for (int i = 1; i < len; i++) {
            if (vec[i] > max) {
                max = vec[i];
            }
        }

        vector<vector<int>> beads(len, vector<int>(max, 0));

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < vec[i]; j++) {
                beads[i][j] = 1;
            }
        }

        for (int j = 0; j < max; j++) {
            int sum = 0;
            for (int i = 0; i < len; i++) {
                sum += beads[i][j];
                beads[i][j] = 0;
            }
            for (int i = len - 1; i >= len - sum; i--) {
                beads[i][j] = 1;
            }
        }

        for (int i = 0; i < len; i++) {
            int sum = 0;
            for (int j = 0; j < max; j++) {
                sum += beads[i][j];
            }
            vec[i] = sum;
        }
    }
}

int main() {
    vector<int> a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::beadSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';

    return 0;
}

#include <bits/stdc++.h>
#include <random>

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
    /*
    * for i in range(len(arr)):

    # 가장 작은 값을 저장할 변수에 i를 초기화
        min_idx = i
        for j in range(i + 1, len(arr)):
        # 만약 가장 작은 값변수가 다음 인덱스의 값보다 클경우
            if arr[min_idx] > arr[j]:
                min_idx = j # 값을 변경

    # 값을 변경
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    */

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
}

int main() {
    vector<int> a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::heapSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';

    return 0;
}

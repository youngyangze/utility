#include <bits/stdc++.h>
#include <random>

using namespace std;

namespace sort {
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
        if (sort::countSort(vec) == vec) {
            return true;
        } else {
            return false;
        }
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

int main() {

    return 0;
}

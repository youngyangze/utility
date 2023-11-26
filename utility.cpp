#include <bits/stdc++.h>
#include <process.h>
#include <random>
#include <windows.h>

using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL)


typedef long long ll;

const int INF = 1e9;

int n, m;

/*
variableName
functionName
SignalName
ConstantName
attribute_name
*/

namespace utility {
    template <typename T> void dfs(int start, vector<vector<T>>& graph, vector<bool>& visited) {
        // cout << start << ' ';
        visited[start] = true;
        for (int next : graph[start]) {
            if (!visited[next]) {
                dfs(next, graph, visited);
            }
        }
    }

    template <typename T> void bfs(int start, vector<vector<T>>& graph, vector<bool>& visited) {
        queue<int> queue;
        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            // cout << current << ' ';

            for (int next : graph[current]) {
                if (!visited[next]) {
                    queue.push(next);
                    visited[next] = true;
                }
            }
        }
    }

    template <typename T> ll binarySearch(vector<T>& vec, const ll target) {
        ll low = 0, mid = 0, high = vec.size() - 1;

        while (low <= high) {
            mid = (low + high) / 2;

            if (target < vec[mid]) {
                high = mid - 1;
            } else if (target > vec[mid]) {
                low = mid + 1;
            } else {
                return mid; // mid = index of target
            }
        }

        return -1;
    }

    template <typename T> void floydWarshall(vector<T>& vec) {
        ll V = vec.size(); // O(V^3)

        for (ll k = 0; k < V; k++) {
            for (ll i = 0; i < V; i++) {
                for (ll j = 0; j < V; j++) {
                    if (vec[i][k] != INF && vec[k][j] != INF && vec[i][j] > vec[i][k] + vec[k][j]) { // INF는 경로가 존재 하지 않는다는 뜻입니다.
                        vec[i][j] = vec[i][k] + vec[k][j];
                    }
                }
            }
        }
    }

    template <typename T> ll lowerBound(vector<T> vec, const ll target) {
        ll begin = 0;
        ll end = vec.size();

        while (begin < end) {
            ll mid = (begin + end) / 2;

            if (vec[mid] >= target) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }
        return end;
    }

    template <typename T> ll upperBound(vector<T> vec, ll target) {
        ll begin = 0;
        ll end = vec.size();

        while (begin < end) {
            ll mid = (begin + end) / 2;

            if (vec[mid] <= target) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        return end;
    }

    template <typename T> void floodFill4Way(vector<T>& vec, const int x, const int y) { // n은 가로, m은 세로의 길이
        const vector<int> dx = { -1, 0, 1 };
        const vector<int> dy = { -1, 0, 1 };

        if (x < 1 || x > n || y < 1 || y > m || vec[x][y]) {
            return;
        }
        vec[x][y] = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i != 1 || j != 1) {
                    floodFill4Way(vec, x + dx[i], y + dy[j]);
                } // if문은 생략할 수 있음
            }
        }
        /*
        floodFill4Way(vec, x - 1, y);
        floodFill4Way(vec, x, y - 1);
        floodFill4Way(vec, x, y + 1);
        floodFill4Way(vec, x + 1, y);
        */
    }

    template <typename T> void floodFill8Way(vector<T>& vec, const int x, const int y) {
        const vector<int> dx = { -1, -1, -1, 0, 0, 1, 1, 1 };
        const vector<int> dy = { -1, 0, 1, -1, 1, -1, 0, 1 };

        if (x < 1 || x > n || y < 1 || y > m || vec[x][y]) {
            return;
        }
        vec[x][y] = 1;
        for (int i = 0; i < 8; i++) {
            floodFill8Way(vec, x + dx[i], y + dy[i]);
        }
        /*
        floodFill8Way(x - 1, y - 1);
        floodFill8Way(x - 1, y);
        floodFill8Way(x - 1, y + 1);
        floodFill8Way(x, y - 1);
        floodFill8Way(x, y + 1);
        floodFill8Way(x + 1, y - 1);
        floodFill8Way(x + 1, y);
        floodFill8Way(x + 1, y + 1);
        */
    }

    template <typename T> int printVector(vector<T> vec) {
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

    template <typename T> bool isSorted(vector<T> vec) {
        vector<T> sorted = vec;
        sort(sorted.begin(), sorted.end());
        return sorted == vec;
    }

    vector<int> generateRandomVector(const int size, const int range_start, const int range_end, const bool onlyUniqueNumbers = false) {
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
} // namespace utility

namespace ultimateSort {
    void countSort(vector<int>& vec) {
        int maxVal = *max_element(vec.begin(), vec.end());
        int minVal = *min_element(vec.begin(), vec.end());

        vector<int> buckets(maxVal - minVal + 1, 0);

        for (int i = 0; i < vec.size(); i++) {
            buckets[vec[i] - minVal]++;
        }

        int index = 0;
        for (int i = 0; i < buckets.size(); i++) {
            while (buckets[i] > 0) {
                vec[index] = i + minVal;
                index++;
                buckets[i]--;
            }
        }
    }

    void bogoSort(vector<int>& vec) {
        while (!utility::isSorted(vec)) {
            random_device rd;
            mt19937 gen(rd());
            shuffle(vec.begin(), vec.end(), gen);
        }
    }

    void selectionSort(vector<int>& vec) {
        int minIndex;

        for (int i = 0; i < vec.size() - 1; i++) {
            minIndex = i;
            for (int j = i + 1; j < vec.size(); j++) {
                if (vec[minIndex] > vec[j]) {
                    minIndex = j;
                }
            }

            swap(vec[i], vec[minIndex]);
        }
    }

    void heapify(vector<int>& vec, const int n, const int i) {
        int largestNumber = i, left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && vec[left] > vec[largestNumber])
            largestNumber = left;

        if (right < n && vec[right] > vec[largestNumber])
            largestNumber = right;

        if (largestNumber != i) {
            swap(vec[i], vec[largestNumber]);
            heapify(vec, n, largestNumber);
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

    void insertionSort(vector<int>& vec) {
        for (int i = 1; i < vec.size(); i++) {
            int val = vec[i];
            int n = i;
            while (n > 0 && vec[n - 1] > val) {
                vec[n] = vec[n - 1];
                n -= 1;
            }
            vec[n] = val;
        }
    }

    void bubbleSort(vector<int>& vec) {
        for (int i = vec.size() - 1; i > 0; i--) {
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
} // namespace ultimateSort

typedef complex<double> cpx;
namespace lab {
    void FFT(vector<cpx>& vec, bool inv) {
        int len = vec.size();

        for (int i = 1, j = 0; i < len; i++) {
            int bit = len / 2;

            while (j >= bit) {
                j -= bit;
                bit /= 2;
            }
            j += bit;

            if (i < j) {
                swap(vec[i], vec[j]);
            }
        }

        for (int k = 1; k < len; k *= 2) {
            double angle = (inv ? acos(-1) / k : -acos(-1) / k);
            cpx w(cos(angle), sin(angle));

            for (int i = 0; i < len; i += k * 2) {
                cpx z(1, 0);

                for (int j = 0; j < k; j++) {
                    cpx even = vec[i + j];
                    cpx odd = vec[i + j + k];

                    vec[i + j] = even + z * odd;
                    vec[i + j + k] = even - z * odd;

                    z *= w;
                }
            }
        }

        if (inv) {
            for (int i = 0; i < len; i++) {
                vec[i] /= len;
            }
        }
    }
    vector<int> mul(vector<int>& vec, vector<int>& vec2) {
        vector<cpx> vc(vec.begin(), vec.end());
        vector<cpx> uc(vec2.begin(), vec2.end());

        int n = 2;
        while (n < vec.size() + vec2.size())
            n *= 2;

        vc.resize(n);
        FFT(vc, false);
        uc.resize(n);
        FFT(uc, false);

        for (int i = 0; i < n; i++)
            vc[i] *= uc[i];
        FFT(vc, true);

        vector<int> w(n);
        for (int i = 0; i < n; i++)
            w[i] = round(vc[i].real());

        return w;
    }
} // namespace lab

int main() {
    /*
    vector<vector<int>> graph = {
        {0, 8, 4, 5, 5},
        {7, 0, 6, 2, 2},
        {3, 2, 0, 3, 7},
        {7, 3, 7, 0, 1},
        {3, 7, 4, 2, 0}
    };
    const int V = graph.size();

    utility::floydWarshall(graph);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF) {
                cout << "INF ";
            }
            else {
                cout << graph[i][j] << "  ";
            }
        }
        cout << '\n';
    }
    */

    fastio;

    vector<int> a = utility::generateRandomVector(50, 1, 50, true);
    cout << "bead sort\n";
    utility::printVector(a);
    ultimateSort::beadSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "bubble sort\n";
    a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::bubbleSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "insertion sort\n";
    a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::insertionSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "heap sort\n";
    a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::heapSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "selection sort\n";
    a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::selectionSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "count sort\n";
    a = utility::generateRandomVector(50, 1, 50, true);
    utility::printVector(a);
    ultimateSort::countSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';
    cout << "bogo sort\n";
    a = utility::generateRandomVector(5, 1, 5, true);
    utility::printVector(a);
    ultimateSort::bogoSort(a);
    utility::printVector(a);
    cout << utility::isSorted(a) << '\n';


    return 0;
}

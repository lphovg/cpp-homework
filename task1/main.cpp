#include <iostream>
#include <iomanip>

struct Result {
  int first;
  int second;
};

double Average(const int* array, int size) {
  double sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += array[i];
  }
  return sum / size;
}

Result MinMax(const int* array, int size) {
  int max = array[0];
  int min = array[0];
  for (int i = 1; i < size; ++i) {
    if (max < array[i]) {
      max = array[i];
    }
    if (min > array[i]) {
      min = array[i];
    }
  }
  Result ans;
  ans.first = min;
  ans.second = max;
  return ans;
}

int FrozenCnt(const int* array, int size) {
    int cnt = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] < 0) {
            cnt += 1;
        }
    }
    return cnt;
}

int main() {
  int n;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }
  int* temperature = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> temperature[i];
  }
  std::cout << std::fixed << std::setprecision(1) << Average(temperature, n) << std::endl;
  Result mm = MinMax(temperature, n);
  std::cout << mm.first << " " << mm.second << std::endl;
  std::cout << FrozenCnt(temperature, n) << std::endl;
  delete[] temperature;
  return 0;
}
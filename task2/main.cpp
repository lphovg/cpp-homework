#include <iostream>

struct Table {
  const char* name;
  bool (*func)(int&, int);
  bool needarg; 
};

bool Deposit(int& sum, int k) {
  if (k <= 0) {
    return false;
  }
  sum += k;
  return true;
}

bool Withdraw(int& sum, int k) {
  if (k <= 0 || k > sum) {
    return false;
  }
  sum -= k;
  return true;
}

bool Balance(int& sum, int) {
    std::cout << sum << std::endl;
    return true;
}

bool Reset(int& sum, int) {
    sum = 0;
    return true;
}

bool Breakfast(int& sum, int) {
    if (sum < 300) {
        return false;
    }
    sum -= 300;
    return true;
}

bool Is(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a += 1;
        b += 1;
    }
    return *a == *b;
}

int main() {
  Table Comands[] = {
    {"deposit", Deposit, true}, 
    {"withdraw", Withdraw, true}, 
    {"balance", Balance, false},
    {"reset", Reset, false},
    {"breakfast", Breakfast, false}
  };
  int sum = 0;
  char c[64];
  while (std::cin >> c) {
    if (Is(c, "stop")) {
      break;
    }
    bool f = false;
    for (auto i : Comands) {
        if (Is(i.name, c)) {
          int arg = 0;
          if (i.needarg) {
            std::cin >> arg;
          }
          if (!i.func(sum, arg)) {
            std::cout << "error" << std::endl;
          }
          f = true;
          break;
        }
    }
    if (!f) {
        std::cout << "error" << std::endl;
    }
  }
  return 0;
}
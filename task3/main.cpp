#include <iostream>

struct Table {
  const char* name;
  bool (*func)(char**, int, int, char*);
  bool needarg; 
};

int Size(const char* c) {
    int ans = 0;
    while (c[ans] != '\0') {
        ++ans;
    }
    return ans;
}

bool Correct(int x, int y, int len) {
    if (x >= 0 && x + len - 1 < 10 && y >= 0 && y < 5) {
        return true;
    }
    return false;
}

bool Clear(char** tablo, int, int, char*) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            tablo[i][j] = ' ';
        }
    }
    return true;
}

bool Put(char** tablo, int x, int y, char* c) {
    int len = Size(c);
    if (len == 1 && Correct(x, y, len)) {
        tablo[y][x] = c[0];
        return true;
    }
    return false;
}

bool Text(char** tablo, int x, int y, char* c) {
    int len = Size(c);
    if (Correct(x, y, len)) {
        for (int i = 0; i < len; ++i) {
            tablo[y][x + i] = c[i];
        }
        return true;
    }
    return false;
}

bool Print(char** tablo, int, int, char*) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << tablo[i][j];
        }
        std::cout << '\n';
    }
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
    {"clear", Clear, false}, 
    {"put", Put, true}, 
    {"text", Text, true},
    {"print", Print, false},
  };
  char** tablo = new char*[5];
  for (int i = 0; i < 5; ++i) {
    tablo[i] = new char[10];
    for (int j = 0; j < 10; ++j) {
        tablo[i][j] = ' ';
    }
  }
  char c[64];
  while (std::cin >> c) {
    if (Is(c, "quit")) {
        break;
    }
    bool f = false;
    for (const auto& i : Comands) {
        if (Is(c, i.name)) {
            int x = 0;
            int y = 0;
            char str[64]{};
            if (i.needarg) {
                std::cin >> x >> y >> str;
            }
            if (!i.func(tablo, x, y, str)) {
                std::cout << "error" << '\n';
            }
            f = true;
            break;
        }
    }
    if (!f) {
        std::cout << "error" << '\n';
    }
  }
  for (int i = 0; i < 5; ++i) {
    delete[] tablo[i];
  }
  delete[] tablo;
  return 0;
}
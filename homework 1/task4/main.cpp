#include <iostream>

int main() {
    int granprix, drivers, laps;
    std::cout << "Enter number of GPs, drivers, laps per race: ";
    std::cin >> granprix >> drivers >> laps;
    void* raw = new int[granprix * drivers * laps];
    int* flat = static_cast<int*>(raw);
    int*** cube = new int**[granprix];
    for (int i = 0; i < granprix; ++i) {
        cube[i] = new int*[drivers];
        for (int j = 0; j < drivers; ++j) {
            cube[i][j] = flat + (i * drivers + j) * laps;
        }
    }
    std::cout << "Enter " << granprix*drivers*laps << " lap times in ms (one per lap):\n";
    long long total = 0;
    int best = -1;
    for (int i = 0; i < granprix; ++i) {
        for (int j = 0; j < drivers; ++j) {
            for (int k = 0; k < laps; ++k) {
                std::cin >> cube[i][j][k];
                int t = cube[i][j][k];
                total += t;
                if (best < 0 || t < best) {
                    best = t;;
                }
            }
        }
    }
    std::cout << "Total season time in ms: " << total << "\n";
    std::cout << "Best lap: " << best << " ms \n";
    for (int i = 0; i < granprix; ++i) {
        delete[] cube[i];
    }
    delete[] cube;
    delete[] flat;
    return 0;
}
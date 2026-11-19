#include <iostream>

int main() {
    // Обрабатываем времена гонщиков формулы один за все гранпри. Выбираем наименьшее.
    // Нужен int*** потмоу структура трехмерная. На каждом гранпри рассматриваем
    // у каждого гонщика каждый круг. Находим минимальное время на всех гранпри.
    // (Опустим, что между гранпри нельзя сравнивать времена из-за разной длины трасс)
    // void* используем в качестве аллокатора памяти, чтобы плоскую строку памяти превратить
    // в трехмерный массив. Остальные варианты использования кажутся слишком притянутыми.
    int granprix, drivers, laps;
    std::cout << "Enter number of GPs, drivers, laps per race: ";
    std::cin >> granprix >> drivers >> laps;
    void* raw = new int[granprix * drivers * laps];
    int* flat = static_cast<int*>(raw);
    int*** race = new int**[granprix];
    for (int i = 0; i < granprix; ++i) {
        race[i] = new int*[drivers];
        for (int j = 0; j < drivers; ++j) {
            race[i][j] = flat + (i * drivers + j) * laps;
        }
    }
    std::cout << "Enter " << granprix*drivers*laps << " lap times in ms (one per lap):\n";
    long long total = 0;
    int best = -1;
    for (int i = 0; i < granprix; ++i) {
        for (int j = 0; j < drivers; ++j) {
            for (int k = 0; k < laps; ++k) {
                std::cin >> race[i][j][k];
                int t = race[i][j][k];
                total += t;
                if (best < 0 || t < best) {
                    best = t;
                }
            }
        }
    }
    std::cout << "Total season time in ms: " << total << "\n";
    std::cout << "Best lap: " << best << " ms \n";
    for (int i = 0; i < granprix; ++i) {
        delete[] race[i];
    }
    delete[] race;
    delete[] flat;
    return 0;
}
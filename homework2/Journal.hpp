#pragma once
#include <vector>
#include <string>
#include "Errors.hpp"

template <typename T, int Cap>
class RegJournal {
private:
    std::vector<std::pair<T, bool>> notes;
    int cnt = 0;
public:
    RegJournal() {notes.reserve(Cap);}
    void add(T object, bool type) {
        if (cnt >= Cap) {
            throw JournalOverflowError();
        }
        notes.push_back({object, type});
        cnt += 1;
    }
    void clean() {
        notes.clear();
        cnt = 0;
    }
    int size() const {
        return static_cast<int>(notes.size());
    }
    std::string deleted() {
        std::string ans = "";
        int anscnt = 0;
        for (long long i = 0; i < cnt; ++i) {
            if (!notes[i].second) {
                anscnt += 1;
                ans += notes[i].first->describe() + "\n";
            }
        }
        if (anscnt == 0) {
            return "there are no deleted";
        }
        return ans;
    }
    inline friend std::ostream& operator<<(std::ostream& out, const RegJournal& item) {
        for (int i = 0; i < item.size(); ++i) {
            out << item.notes[i].first << " ";
            if (item.notes[i].second) {
                out << "added\n";
            } else {
                out << "deleted\n";
            }
        }
        return out;
    }
    std::pair<T, bool> operator[](int i) {
        return notes[i];
    }
};

template <int Cap>
class RegJournal<std::string, Cap> {
private:
    std::vector<std::string> notes;
    int cnt = 0;
public:
    RegJournal() {notes.reserve(Cap);}
    void add(std::string object) {
        if (cnt >= Cap) {
            throw JournalOverflowError();
        }
        notes.push_back(object);
        cnt += 1;
    }
    void clean() {
        notes.clear();
        cnt = 0;
    }
    int size() const {
        return static_cast<int>(notes.size());
    }
    inline friend std::ostream& operator<<(std::ostream& out, const RegJournal& item) {
        for (int i = 0; i < item.size(); ++i) {
            out << item.notes[i] << "\n";
        }
        return out;
    }
    std::string operator[](int i) {
        return notes[i];
    }
};
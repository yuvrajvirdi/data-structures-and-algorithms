#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> next_table(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);
    int i = 0, len = 0;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            next[i] == len;
            i++;
        } else {
            if (len != 0) len = next[len-1];
            else {
                next[i] = 0;
                i++;
            }
        }
    }

    return next;
}

void kmp(const string& text, const string& pattern) {
    int n = text.length(), m = pattern.length();
    vector<int> next = next_table(pattern);
    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

    }
}
#include <iostream>
#include <vector>
#include <functional>
#include <bitset>
using namespace std;

class BloomFilter {
private:
    bitset<1000> bits;
    vector<function<size_t(const string&)>> hash_functions;

    // hash functions
    size_t hash1(const string& key) const {
        size_t hash = 0;
        for (char c : key) 
            hash = 31 * hash + c;
        return hash % 1000;
    }
    size_t hash2(const string& key) const {
        size_t hash = 0;
        for (char c : key) 
            hash = 37 * hash + c;
        return hash % 1000;
    }
    size_t hash3(const string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash = 41 * hash + c;
        }
        return hash % 1000;
    }

public:
    BloomFilter() {
        // init hash functions
        hash_functions.push_back([this](const std::string& key) { return hash1(key); });
        hash_functions.push_back([this](const std::string& key) { return hash2(key); });
        hash_functions.push_back([this](const std::string& key) { return hash3(key); });
    }

    // add key (word)
    void add(const string& key) {
        for (const auto& hash_function: hash_functions) 
            bits[hash_function(key)] = true;
    }

    // check
    bool might_contain(const string& key) const {
        for (const auto& hash_function : hash_functions) {
            if (!bits[hash_function(key)]) 
                return false;
        }
        return true;
    }

};

int main() {
    BloomFilter bloom_filter;

    bloom_filter.add("apple");
    bloom_filter.add("banana");

    std::cout << "Might contain 'apple': " << bloom_filter.might_contain("apple") << std::endl;
    std::cout << "Might contain 'banana': " << bloom_filter.might_contain("banana") << std::endl;
    std::cout << "Might contain 'orange': " << bloom_filter.might_contain("orange") << std::endl;

    return 0;
}
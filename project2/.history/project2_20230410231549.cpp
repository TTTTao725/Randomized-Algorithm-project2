#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <climits>

using KeyType = int;
using ValueType = std::string;

// Hash table implementation using chaining
class HashTable {
public:
    explicit HashTable(size_t capacity) : data(capacity) {}

    bool Insert(const KeyType& key, const ValueType& value) {
        size_t index = hash_func(key) % data.size();
        for (auto& kvp : data[index]) {
            if (kvp.first == key) {
                kvp.second = value;
                return false;
            }
        }
        data[index].emplace_back(key, value);
        return true;
    }

    bool Remove(const KeyType& key) {
        size_t index = hash_func(key) % data.size();
        auto& list = data[index];
        for (auto itr = list.begin(); itr != list.end(); ++itr) {
            if (itr->first == key) {
                list.erase(itr);
                return true;
            }
        }
        return false;
    }

    bool Find(const KeyType& key, ValueType& value) const {
        size_t index = hash_func(key) % data.size();
        const auto& list = data[index];
        for (const auto& kvp : list) {
            if (kvp.first == key) {
                value = kvp.second;
                return true;
            }
        }
        return false;
    }

private:
    // Hash function using multiply-shift
    size_t hash_func(const KeyType& key) const {
        const size_t word_size = sizeof(size_t);
        const size_t bits_in_word = word_size * CHAR_BIT;
        static std::random_device rd;
        static std::mt19937_64 rng(rd());
        static std::uniform_int_distribution<size_t> dist(0, bits_in_word - 1);

        static const size_t p = find_random_prime(1ull << 32, 1ull << 31);
        size_t h = static_cast<size_t>(key);
        h *= p;
        h >>= dist(rng);
        h >>= (bits_in_word - BITS);
        return h;
    }

    // Helper function to find a random prime number in a given range
    size_t find_random_prime(size_t upper_bound, size_t lower_bound) const {
        std::random_device rd;
        std::mt19937_64 rng(rd());
        std::uniform_int_distribution<size_t> dist(lower_bound, upper_bound);

        auto is_prime = [](size_t n) {
            if (n <= 1) return false;
            if (n <= 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;
            for (size_t i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i + 2) == 0) return false;
            }
            return true;
        };

        size_t p;
        while (true) {
            p = dist(rng);
            if (is_prime(p)) return p;
        }
    }

private:
    static constexpr size_t BITS = 16; // number of bits in hash code
    std::vector<std::vector<std::pair<KeyType, ValueType>>> data;
};

int main() {
    HashTable ht(10);

    ht.Insert(1, "one");
    ht.Insert(2, "two");
    ht.Insert(3, "three");
    ht.Insert(4, "four");

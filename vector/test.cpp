#include <catch.hpp>

#include "vector.hpp"

#include <vector>

namespace {

void require_equality(const Vector<int> &actual, const std::vector<int> &expected) {
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}
}

TEST_CASE("Constructors") {
    {
        Vector<int> a;
        REQUIRE(a.size() == 0u);
        REQUIRE(a.capacity() == 0u);
    }
    {
        Vector<int> a{1, 2, 3, 4};
        require_equality(a, std::vector{1, 2, 3, 4});
        a = a; // NOLINT
        require_equality(a, std::vector{1, 2, 3, 4});
    }
    {
        Vector<int> a(5);
        require_equality(a, std::vector<int>(5));
    }
}

TEST_CASE("Basic methods") {
    Vector a{1, 3, 5};
    REQUIRE(a.capacity() == 3u);
    require_equality(a, std::vector{1, 3, 5});

    a.pop_back();
    REQUIRE(a.empty() == false);
    require_equality(a, std::vector{1, 3});
    a.clear();
    REQUIRE(a.empty() == true);
    REQUIRE(a.capacity() == 3u);
    require_equality(a, std::vector<int>());

    a.push_back(6);
    require_equality(a, std::vector{6});

    Vector b{3, 4};

    auto *a_data = a.data();
    auto *b_data = b.data();

    a.swap(b);
    require_equality(a, std::vector{3, 4});
    require_equality(b, std::vector{6});

    REQUIRE(a_data == b.data());
    REQUIRE(b_data == a.data());

    REQUIRE(b.empty() == false);
    b.pop_back();
    REQUIRE(b.empty() == true);
}

TEST_CASE("Modifications with []") {
    Vector a{3, 7, 8};
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    require_equality(a, std::vector{1, 2, 3});
}

TEST_CASE("Iterators 1") {
    Vector<int> a(5);
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = i;
    }
    {
        Vector<int>::value_type cur = 0;
        for (auto elem : a) {
            REQUIRE(cur++ == elem);
        }
    }

    {
        auto first = a.begin();
        auto last = a.end();
        REQUIRE(static_cast<Vector<int>::size_type>(last - first) == a.size());
        REQUIRE(*first == 0);

        REQUIRE(first == a.begin());
        REQUIRE(first != last);
        REQUIRE(first < last);
        REQUIRE(first <= last);
        REQUIRE(last > first);
        REQUIRE(last >= first);

        ++first;
        REQUIRE(*first == 1);
        auto tmp = first++;
        REQUIRE(*tmp == 1);
        REQUIRE(*first == 2);
        auto end = last--;
        REQUIRE(end == a.end());
        REQUIRE(*last == 4);
        --last;
        REQUIRE((first += 1) == last);
        last -= 3;
        REQUIRE(*last == 0);
    }

    {
        auto first = a.begin();
        int size = static_cast<int>(a.size());
        for (int i = 0; i < size; ++i) {
            for (int diff = -2; diff <= 2; ++diff) {
                if (i + diff >= 0 && i + diff < size) {
                    REQUIRE(*(first + i + diff) == i + diff);
                }
                if (i - diff >= 0 && i - diff < size) {
                    REQUIRE(*(first + i - diff) == i - diff);
                }
            }
        }
    }
}


TEST_CASE("Reverse iterators 1") {
    Vector<int> a(5);
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = i;
    }
    {
        Vector<int>::value_type cur = 0;
        for (auto elem : a) {
            Vector<int> a(5);
            REQUIRE(cur++ == elem);
        }
    }

    {
        auto first = a.rbegin();
        auto last = a.rend();
        REQUIRE(static_cast<Vector<int>::size_type>(last - first) == a.size());
        REQUIRE(*first == 4);

        REQUIRE(first == a.rbegin());
        REQUIRE(first != last);
        REQUIRE(first < last);
        REQUIRE(first <= last);
        REQUIRE(last > first);
        REQUIRE(last >= first);

        ++first;
        REQUIRE(*first == 3);
        auto tmp = first++;
        REQUIRE(*tmp == 3);
        REQUIRE(*first == 2);
        auto end = last--;
        REQUIRE(end == a.rend());
        REQUIRE(*last == 0);
        --last;
        REQUIRE((first += 1) == last);
        last -= 3;
        REQUIRE(*last == 4);
    }

    {
        auto first = a.rbegin();
        int size = static_cast<int>(a.size());
        for (int i = 0; i < size; ++i) {
            for (int diff = -2; diff <= 2; ++diff) {
                if (i + diff >= 0 && i + diff < size) {
                    REQUIRE(*(first + i + diff) == 4 - (i + diff));
                }
                if (i - diff >= 0 && i - diff < size) {
                    REQUIRE(*(first + i - diff) == 4 - (i - diff));
                }
            }
        }
    }
}


TEST_CASE("Iterators 2") {
    Vector a{1, 3, 5};
    *(a.begin().operator->()) = 2;
    *((--a.end()).operator->()) = 4;

    require_equality(a, std::vector{2, 3, 4});

    Vector<int>::iterator it;
    it = a.begin() + 1;
    REQUIRE(*it == 3);
}

TEST_CASE("Reverse iterators 2") {
    Vector a{1, 3, 5};
    *(a.rbegin().operator->()) = 2;
    *((--a.rend()).operator->()) = 4;

    require_equality(a, std::vector{4, 3, 2});

    Vector<int>::reverse_iterator it;
    it = a.rbegin() + 1;
    REQUIRE(*it == 3);
}

TEST_CASE("Reallocation") {
    const int steps = 16;
    Vector<int> data;
    for (int step = 0; step <= steps; ++step) {
        std::vector<int> ok_data;
        for (Vector<int>::value_type i = 0; i <= (1 << step); ++i) {
            data.push_back(i);
            ok_data.push_back(i);
        }
        require_equality(data, ok_data);
        REQUIRE(data.capacity() == (1u << (step + 1)));
        data.clear();
    }
}

TEST_CASE("Comparison") {
    REQUIRE(Vector({1, 2, 3}) == Vector({1, 2, 3}));
    REQUIRE(Vector({1, 2, 3}) != Vector({2, 3, 4}));

    REQUIRE(Vector({1, 2, 3}) < Vector({2, 3, 4}));
    REQUIRE(Vector({1, 2, 3}) < Vector({1, 2, 3, 4}));
    REQUIRE(Vector({1, 2, 3, 4}) <= Vector({2}));
    REQUIRE(Vector({1, 2, 3, 4}) > Vector<int>());
    REQUIRE(Vector({1, 2, 3, 4}) >= Vector({1}));
}

TEST_CASE("Reserve") {
    Vector<int> a;
    a.reserve(5);
    REQUIRE(a.size() == 0u);
    REQUIRE(a.capacity() == 5u);

    for (Vector<int>::value_type i = 0; i < 5; ++i) {
        a.push_back(i);
    }

    REQUIRE(a.capacity() == 5u);
    a.push_back(4);
    REQUIRE(a.capacity() == 10u);
    a.reserve(3);
    REQUIRE(a.capacity() == 10u);
    a.clear();
    REQUIRE(a.size() == 0u);
    REQUIRE(a.capacity() == 10u);
    a.resize(2);
    REQUIRE(a.size() == 2u);
    REQUIRE(a.capacity() == 10u);
    a.shrink_to_fit();
    REQUIRE(a.size() == 2u);
    REQUIRE(a.capacity() == 2u);
    a.shrink_to_fit();
    REQUIRE(a.size() == 2u);
    REQUIRE(a.capacity() == 2u);
    a.clear();
    a.shrink_to_fit();
    REQUIRE(a.size() == 0u);
    REQUIRE(a.capacity() == 0u);
    a.shrink_to_fit();
    REQUIRE(a.size() == 0u);
    REQUIRE(a.capacity() == 0u);
}

TEST_CASE("Sort") {
    Vector<int> a = {2, 9, 7, 1, 5, 3, 8, 6, 4, 0};
    auto b = a;
    REQUIRE(a == b);
    std::sort(a.begin(), a.end());
    std::sort(b.rbegin(), b.rend());
    require_equality(a, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    require_equality(b, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
}

TEST_CASE("Resize and assign") {
    {
        Vector<int> a;
        for (int i : {3, 4, 5, 12, 50, 51, 52, 53}) {
            auto old_capacity = a.capacity();
            a.resize(i);
            auto new_capacity = a.capacity();
            if (old_capacity != new_capacity) {
                REQUIRE(old_capacity * 2 <= new_capacity);
            }
        }
    }
    {
        Vector<int> a;
        for (int i : {3, 4, 5, 12, 50, 51, 52, 53}) {
            auto old_capacity = a.capacity();
            a.assign(i, 0);
            auto new_capacity = a.capacity();
            if (old_capacity != new_capacity) {
                REQUIRE(old_capacity * 2 <= new_capacity);
            }
        }
    }
    Vector<int> a = {2};
    a.resize(3);
    require_equality(a, {2, 0, 0});
    a.assign(2, 1);
    require_equality(a, {2, 0});
    a.assign(3, 1);
    require_equality(a, {2, 0, 1});
    a.resize(1);
    require_equality(a, {2});
    REQUIRE(a.empty() == false);
    a.resize(0);
    require_equality(a, {});
    REQUIRE(a.empty() == true);
    a.assign(2, 3);
    require_equality(a, {3, 3});
    a.assign(0, 3);
    require_equality(a, {});
}

TEST_CASE("Insert and erase") {
    Vector<int> a;
    std::vector<int> b;
    std::vector<int> inds = {0, 0, 0, 1, 2, 5, 6, 4, 0};
    for (int i = 0; i < static_cast<int>(inds.size()); ++i) {
        a.insert(a.begin() + inds[i], i);
        b.insert(b.begin() + inds[i], i);
        require_equality(a, b);
    }
    for (int ind : {0, 0, 6, 5, 3, 3, 2, 0, 0}) {
        a.erase(a.begin() + ind);
        b.erase(b.begin() + ind);
        require_equality(a, b);
    }
}

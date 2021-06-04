#include "big_integer.h"
#include "binpow.h"
#include "combinatorics.h"
#include "dijkstra.h"
#include "dsu.h"
#include "fenwick_tree.h"
#include "floyd_warshall.h"
#include "gcd_lcm.h"
#include "kruskal.h"
#include "mod.h"
#include "prefix_function.h"
#include "prime.h"
#include "search.h"
#include "segtree.h"

#include <chrono>

void dont_cut(int x);

void check(bool value) {
    if (!value) {
        std::abort();
    }
}

void test_big_integer(const BigInteger& a, int b) {
    check((a + b - a) == b);
    check((a * b / b) == a);
}

int main() {
    test_big_integer(BigInteger("123475474526378454234387234579234533429586234573455498763214"), 123456789);
    test_big_integer(BigInteger("0"), 123456789);
    test_big_integer(BigInteger("1"), 1);
    test_big_integer(BigInteger("999999999"), 999999999);

    check(binpow(105, 5) == 12762815625ll);
    check(binpow(0, 5) == 0);
    check(binpow(105, 0) == 1);
    check(binpow(2, 30) == 1073741824ll);
    check(binpow(2, 63) == 9223372036854775808ll);
    check(binpow(-2, 5) == -32);
    check(binpow(-2, 6) == 64);

    check(c(100, 1) == 100);
    check(c(100, 100) == 1);
    check(c(10, 3) == 120);
    check(c(100, 10) == 17310309456440ll);

    vector<vector<ll>> cnk = build_pascal_triangle(50);
    for (size_t i = 0; i <= 50; i++) {
        for (size_t j = 0; j <= 50; j++) {
            check(cnk[i][j] == c(i, j));
        }
    }

    check(fac(5) == 120ll);
    check(fac(10) == 3628800ll);
    check(fac(20) == 2432902008176640000ll);

    {
        vector<vector<pair<int, int>>> adj_list{
            { { 1, 2 }, { 2, 5 } },
            { { 3, 5 }, { 2, 2 } },
            { { 3, 2 }, { 4, 5 } },
            { { 4, 2 } },
            {}
        };

        auto [parents, costs] = dijkstra(adj_list, 0);
        check((parents == vector<int>{ numeric_limits<int>::max(), 0, 1, 2, 3 }));
        check((costs == vector<int>{ 0, 2, 4, 6, 8 }));
    }

    {
        DSU<int> dsu;
        dsu.build(5);
        for (int i = 0; i < 5; i++) {
            check(dsu.find_set(i) == i);
        }
        dsu.union_sets(0, 1);
        check(dsu.find_set(0) == dsu.find_set(1));
        dsu.union_sets(2, 3);
        check(dsu.find_set(2) == dsu.find_set(3));
        dsu.union_sets(0, 2);
        check(dsu.find_set(0) == dsu.find_set(1) && dsu.find_set(1) == dsu.find_set(2) && dsu.find_set(2) == dsu.find_set(3));
        check(dsu.find_set(4) == 4);
    }

    {
        FenwickTree<int> fenwick;
        fenwick.build(20);
        int sum = 0;
        for (int i = 1; i <= 20; i++) {
            fenwick.add(i, i);
            sum += i;
        }
        check(fenwick.sum(20) == sum);
        check(fenwick.sum(5, 10) == 5 + 6 + 7 + 8 + 9 + 10);
        for (int i = 1; i <= 20; i++) {
            check(fenwick.get(i) == i);
        }
        check(fenwick.search(0) == 1);
        check(fenwick.search(1 + 2 + 3 + 3) == 4);
        check(fenwick.search(1 + 2 + 3 + 4) == 4);
        check(fenwick.search(1 + 2 + 3 + 4 + 5 + 5) == 6);
        check(fenwick.search(1 + 2 + 3 + 4 + 5 + 6) == 6);
        check(fenwick.search(sum) == 20);
        check(fenwick.search(sum + 1) == 21);
        check(fenwick.search(numeric_limits<int>::max()) == 21);
    }

    {
        constexpr int INF = numeric_limits<int>::max();

        vector<vector<int>> matrix{
            { 0,   1,   INF, INF, INF },
            { 1,   0,   1,   INF, INF },
            { INF, 1,   0,   1,   INF },
            { INF, INF, 1,   0,   1   },
            { INF, INF, INF, 1,   0   },
        };

        floyd_warshall(matrix);

        check((matrix[0] == vector<int>{ 0, 1, 2, 3, 4 }));
        check((matrix[1] == vector<int>{ 1, 0, 1, 2, 3 }));
        check((matrix[2] == vector<int>{ 2, 1, 0, 1, 2 }));
        check((matrix[3] == vector<int>{ 3, 2, 1, 0, 1 }));
        check((matrix[4] == vector<int>{ 4, 3, 2, 1, 0 }));
    }

    check(gcd(4, 8) == 4);
    check(gcd(2, 9) == 1);
    check(gcd(143, 77) == 11);
    check(gcd(143, 143) == 143);
    check(gcd(143, 101) == 1);
    check(lcm(143, 101) == 14443);
    check(lcm(143, 143) == 143);
    check(lcm(143, 77) == 1001);
    check(lcm(2, 9) == 18);
    check(lcm(4, 8) == 8);

    {
        vector<tuple<int, int, int>> input {
            { 2, 0, 1 },
            { 5, 0, 2 },
            { 7, 1, 3 },
            { 1, 1, 4 },
            { 1, 2, 3 },
            { 1, 2, 4 },
            { 4, 3, 4 },
        };

        vector<pair<int, int>> output = kruskal(5, input);
        check((output == vector<pair<int, int>>{ { 1, 4 }, { 2, 3 }, { 2, 4 }, { 0, 1 } }));
    }

    check(add(5, 2, 4) == 3);
    check(dec(2, 5, 4) == 1);
    check(mul(7, 2, 4) == 2);
    check(fac(7, 11) == 2);
    check(binpow(3, 6, 4) == 1);

    vector<int> prefix = prefix_function<int>("abc#abcabcaaabbbcccabc");
    check((prefix == vector<int>{ 0, 0, 0, 0, 1, 2, 3, 1, 2, 3, 1, 1, 1, 2, 0, 0, 0, 0, 0, 1, 2, 3 }));
    prefix = prefix_function<int>("1212123#12121212");
    check((prefix == vector<int>{ 0, 0, 1, 2, 3, 4, 0, 0, 1, 2, 3, 4, 5, 6, 5, 6 }));

    check((build_primes(10) == vector<ll>{ 2, 3, 5, 7 }));
    check((build_primes_set(10) == set<ll>{ 2, 3, 5, 7 }));

    vector<int> numbers{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    check(bin_search(0, 10, [&](int x) { return numbers[x] < 5; }) == 5);
    vector<int> numbers2{ 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3 };
    check(bin_search(0, 12, [&](int x) { return numbers2[x] < 3; }) == 9);
    check(bin_search(0, 12, [&](int x) { return numbers2[x] < 2; }) == 5);
    check(bin_search(0, 12, [&](int x) { return numbers2[x] < 1; }) == 3);
    check(bin_search(0, 12, [&](int x) { return numbers2[x] < 0; }) == 0);
    vector<int> numbers3{ 3, 3, 3, 2, 2, 2, 2, 1, 1, 0, 0, 0 };
    check(bin_search(0, 12, [&](int x) { return numbers3[x] > 0; }) == 9);
    check(bin_search(0, 12, [&](int x) { return numbers3[x] > 1; }) == 7);
    check(bin_search(0, 12, [&](int x) { return numbers3[x] > 2; }) == 3);
    check(bin_search(0, 12, [&](int x) { return numbers3[x] > 3; }) == 0);
    check(abs(ternary_search<false>(0.0, 3.14, 1e-5, [](double x) { return sin(x); }) - 1.57) < 1e-2);
    check((ternary_search<false, int>(0, 10, [](int x) { return 6 * x - x * x; }) == 3));

    {
        using namespace query_on_range_change_single;

        SegmentTree<int> segtree;
        segtree.build(20);
        int sum = 0;
        for (int i = 0; i < 20; i++) {
            segtree.update(i, i);
            sum += i;
        }
        check(segtree.sum(0, 19) == sum);
        check(segtree.sum(4, 9) == 4 + 5 + 6 + 7 + 8 + 9);
        segtree.traverse([](size_t idx, int value) {
            cout << value << " ";
        });
        cout << endl;
        for (int i = 0; i < 20; i++) {
            check(segtree.sum(i, i) == i);
        }
    }

    {
        using namespace change_on_range_query_single;

        SegmentTree<int> segtree;
        segtree.build(20);
        int sum = 0;
        for (int i = 0; i < 20; i++) {
            segtree.add(0, i, 1);
            sum += i;
        }
        segtree.traverse([](size_t idx, int value) {
            cout << value << " ";
        });
        cout << endl;
        for (int i = 0; i < 20; i++) {
            check(segtree.get(i) == 20 - i);
        }
    }

    cout << endl;

    //
    // Benchmark.
    //

    {
        FenwickTree<int> fenwick_bench;

        // Build is very fast for any size.

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        fenwick_bench.build(10000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Fenwick build 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Add performs in about 1 second for count = 5 * 10^7.

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 10000000; i++) {
            fenwick_bench.add(i, i);
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick add 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Sum performs in about 1 second for count = 1.25 * 10^8.

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 10000000; i++) {
            dont_cut(fenwick_bench.sum(i));
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick sum 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Add performs in about 1 second for count = 5 * 10^7.

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 10000000; i++) {
            dont_cut(fenwick_bench.search(i));
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick search 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    cout << endl;

    {
        using namespace query_on_range_change_single;

        SegmentTree<int> segtree;

        // Build is very fast for any size.

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        segtree.build(10000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "SegmentTree build 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Update performs in about 1 second for count = 10^7.

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) {
            segtree.update(i, i);
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree update 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Sum performs in about 1 second for count = 6.5 * 10^6.

        begin = chrono::steady_clock::now();
        int sum = 0;
        for (int i = 0; i < 10000000; i++) {
            dont_cut(segtree.sum(0, i));
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree sum 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    cout << endl;

    {
        using namespace change_on_range_query_single;

        SegmentTree<int> segtree;

        // Build is very fast for any size.

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        segtree.build(10000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "SegmentTree build 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Add performs in about 1 second for count = 8.9 * 10^6.

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) {
            segtree.add(0, i, 1);
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree add 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        // Get performs in about 1 second for count = 2 * 10^7.

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) {
            dont_cut(segtree.get(i));
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree get 10^7: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    return 0;
}

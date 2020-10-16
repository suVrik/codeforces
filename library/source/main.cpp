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

void test_big_integer(const BigInteger& a, int b) {
    assert((a + b - a) == b);
    assert((a * b / b) == a);
}

void dont_cut(int value);

int main() {
    test_big_integer(BigInteger("123475474526378454234387234579234533429586234573455498763214"), 123456789);
    test_big_integer(BigInteger("0"), 123456789);
    test_big_integer(BigInteger("1"), 1);
    test_big_integer(BigInteger("999999999"), 999999999);

    assert(binpow(105, 5) == 12762815625ll);
    assert(binpow(0, 5) == 0);
    assert(binpow(105, 0) == 1);
    assert(binpow(2, 30) == 1073741824ll);
    assert(binpow(2, 63) == 9223372036854775808ll);
    assert(binpow(-2, 5) == -32);
    assert(binpow(-2, 6) == 64);

    assert(c(100, 1) == 100);
    assert(c(100, 100) == 1);
    assert(c(10, 3) == 120);
    assert(c(100, 10) == 17310309456440ll);

    vector<vector<ll>> cnk = build_pascal_triangle(50);
    for (size_t i = 0; i <= 50; i++) {
        for (size_t j = 0; j <= 50; j++) {
            assert(cnk[i][j] == c(i, j));
        }
    }

    assert(fac(5) == 120ll);
    assert(fac(10) == 3628800ll);
    assert(fac(20) == 2432902008176640000ll);

    {
        vector<vector<pair<int, int>>> adj_list{
            { { 1, 2 }, { 2, 5 } },
            { { 3, 5 }, { 2, 2 } },
            { { 3, 2 }, { 4, 5 } },
            { { 4, 2 } },
            {}
        };

        auto [parents, costs] = dijkstra(adj_list, 0);
        assert((parents == vector<int>{ numeric_limits<int>::max(), 0, 1, 2, 3 }));
        assert((costs == vector<int>{ 0, 2, 4, 6, 8 }));
    }

    {
        DSU<int> dsu;
        dsu.build(5);
        for (int i = 0; i < 5; i++) {
            assert(dsu.find_set(i) == i);
        }
        dsu.union_sets(0, 1);
        assert(dsu.find_set(0) == dsu.find_set(1));
        dsu.union_sets(2, 3);
        assert(dsu.find_set(2) == dsu.find_set(3));
        dsu.union_sets(0, 2);
        assert(dsu.find_set(0) == dsu.find_set(1) && dsu.find_set(1) == dsu.find_set(2) && dsu.find_set(2) == dsu.find_set(3));
        assert(dsu.find_set(4) == 4);
    }

    {
        FenwickTree<int> fenwick;
        fenwick.build(20);
        int sum = 0;
        for (int i = 1; i <= 20; i++) {
            fenwick.add(i, i);
            sum += i;
        }
        assert(fenwick.sum(20) == sum);
        assert(fenwick.sum(5, 10) == 5 + 6 + 7 + 8 + 9 + 10);
        for (int i = 1; i <= 20; i++) {
            assert(fenwick.get(i) == i);
        }
        assert(fenwick.search(1 + 2 + 3 + 4) == 4);
        assert(fenwick.search(1 + 2 + 3 + 4 + 5 + 6) == 6);
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

        assert((matrix[0] == vector<int>{ 0, 1, 2, 3, 4 }));
        assert((matrix[1] == vector<int>{ 1, 0, 1, 2, 3 }));
        assert((matrix[2] == vector<int>{ 2, 1, 0, 1, 2 }));
        assert((matrix[3] == vector<int>{ 3, 2, 1, 0, 1 }));
        assert((matrix[4] == vector<int>{ 4, 3, 2, 1, 0 }));
    }

    assert(gcd(4, 8) == 4);
    assert(gcd(2, 9) == 1);
    assert(gcd(143, 77) == 11);
    assert(gcd(143, 143) == 143);
    assert(gcd(143, 101) == 1);
    assert(lcm(143, 101) == 14443);
    assert(lcm(143, 143) == 143);
    assert(lcm(143, 77) == 1001);
    assert(lcm(2, 9) == 18);
    assert(lcm(4, 8) == 8);

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
        assert((output == vector<pair<int, int>>{ { 1, 4 }, { 2, 3 }, { 2, 4 }, { 0, 1 } }));
    }

    assert(add(5, 2, 4) == 3);
    assert(dec(2, 5, 4) == 1);
    assert(mul(7, 2, 4) == 2);
    assert(fac(7, 11) == 2);
    assert(binpow(3, 6, 4) == 1);

    vector<int> prefix = prefix_function<int>("abc#abcabcaaabbbcccabc");
    assert((prefix == vector<int>{ 0, 0, 0, 0, 1, 2, 3, 1, 2, 3, 1, 1, 1, 2, 0, 0, 0, 0, 0, 1, 2, 3 }));
    prefix = prefix_function<int>("1212123#12121212");
    assert((prefix == vector<int>{ 0, 0, 1, 2, 3, 4, 0, 0, 1, 2, 3, 4, 5, 6, 5, 6 }));

    assert((build_primes(10) == vector<size_t>{ 2, 3, 5, 7 }));
    assert((build_primes_set(10) == set<size_t>{ 2, 3, 5, 7 }));

    vector<int> numbers{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(bin_search(0, 10, [&](int x) { return numbers[x] < 5; }) == 5);
    assert(abs(ternary_search<false>(0.0, 3.14, 1e-5, [](double x) { return sin(x); }) - 1.57) < 1e-2);
    assert((ternary_search<false, int>(0, 10, [](int x) { return 6 * x - x * x; }) == 3));

    {
        using namespace query_on_range_change_single;

        SegmentTree<int> segtree;
        segtree.build(20);
        int sum = 0;
        for (int i = 0; i < 20; i++) {
            segtree.update(i, i);
            sum += i;
        }
        assert(segtree.sum(0, 19) == sum);
        assert(segtree.sum(4, 9) == 4 + 5 + 6 + 7 + 8 + 9);
        segtree.traverse([](size_t idx, int value) {
            cout << value << " ";
        });
        cout << endl;
        for (int i = 0; i < 20; i++) {
            assert(segtree.sum(i, i) == i);
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
            assert(segtree.get(i) == 20 - i);
        }
    }

    // TODO: treap

    cout << endl;

    {
        FenwickTree<int> fenwick_bench;

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        fenwick_bench.build(100000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Fenwick build 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 100000000; i++) {
            fenwick_bench.add(i, i);
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick add 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 100000000; i++) {
            dont_cut(fenwick_bench.sum(i));
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick sum 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 1; i <= 100000000; i++) {
            dont_cut(fenwick_bench.search(i));
        }
        end = chrono::steady_clock::now();
        cout << "Fenwick search 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    cout << endl;

    {
        using namespace query_on_range_change_single;

        SegmentTree<int> segtree;

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        segtree.build(100000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "SegmentTree build 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 100000000; i++) {
            segtree.update(i, i);
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree update 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        int sum = 0;
        for (int i = 0; i < 100000000; i++) {
            dont_cut(segtree.sum(0, i));
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree sum 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    cout << endl;

    {
        using namespace change_on_range_query_single;

        SegmentTree<int> segtree;

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        segtree.build(100000000);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "SegmentTree build 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 100000000; i++) {
            segtree.add(0, i, 1);
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree add 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;

        begin = chrono::steady_clock::now();
        for (int i = 0; i < 100000000; i++) {
            dont_cut(segtree.get(i));
        }
        end = chrono::steady_clock::now();
        cout << "SegmentTree get 10^8: " << chrono::duration_cast<chrono::duration<float>>(end - begin).count() << " sec" << std::endl;
    }

    // TODO: perf treap

    return 0;
}

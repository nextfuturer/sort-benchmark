#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()

string build_str(int sz, mt19937& gen) {
    string res(sz, 'a');
    uniform_int_distribution<int> d(0, 25);
    for (int i = 0; i < sz; ++i) {
        res[i] = (char)('a' + d(gen));
    }
    return res;
}

void task_c(int mode) {
    int max_items = 10000;
    cout << max_items << "\n";
    mt19937 rnd(333 + mode);
    uniform_int_distribution<int> len_d(10, 100);

    if (mode == 5) {
        string dup = build_str(50, rnd);
        for (int i = 0; i < max_items; ++i) cout << dup << "\n";
    }
    else if (mode == 4) {
        vector<string> v(max_items);
        for (int i = 0; i < max_items; ++i) v[i] = build_str(len_d(rnd), rnd);
        sort(all(v), [](const string& x, const string& y) {
            if (x.size() != y.size()) return x.size() > y.size();
            return x > y;
            });
        for (const auto& str : v) cout << str << "\n";
    }
    else if (mode == 3) {
        string base(100, 'z');
        for (int i = 0; i < max_items; ++i) {
            cout << base.substr(0, len_d(rnd)) << "\n";
        }
    }
    else if (mode == 2) {
        vector<string> v(max_items);
        for (int i = 0; i < max_items; ++i) v[i] = build_str(100, rnd);
        sort(v.rbegin(), v.rend());
        for (const auto& str : v) cout << str << "\n";
    }
    else {
        for (int i = 0; i < max_items; ++i) cout << build_str(len_d(rnd), rnd) << "\n";
    }
}

void task_a(int mode) {
    int max_items = 100000;
    cout << max_items << "\n";
    mt19937 rnd(111 + mode);
    uniform_int_distribution<int> d(-2147483647 - 1, 2147483647);

    switch (mode) {
    case 4: {
        vector<int> v(max_items);
        for (int i = 0; i < max_items; ++i) v[i] = d(rnd);
        sort(v.begin(), v.begin() + max_items / 2, greater<int>());
        sort(v.begin() + max_items / 2, v.end());
        for (int x : v) cout << x << "\n";
        break;
    }
    case 3: {
        for (int i = 0; i < max_items; ++i) {
            if (i % 2 == 0) cout << 2147483647 - (rnd() % 100) << "\n";
            else cout << (-2147483647 - 1) + (rnd() % 100) << "\n";
        }
        break;
    }
    case 2: {
        int same = d(rnd);
        for (int i = 0; i < max_items; ++i) cout << same << "\n";
        break;
    }
    case 1: {
        vector<int> v(max_items);
        for (int i = 0; i < max_items; ++i) v[i] = d(rnd);
        sort(v.rbegin(), v.rend());
        for (int x : v) cout << x << "\n";
        break;
    }
    default: {
        for (int i = 0; i < max_items; ++i) cout << d(rnd) << "\n";
        break;
    }
    }
}

void task_b(int mode) {
    int max_items = 100000;
    cout << max_items << "\n";
    mt19937 rnd(222 + mode);
    uniform_int_distribution<int> len_d(10, 100);

    if (mode == 5) {
        uniform_int_distribution<int> bin_d(0, 1);
        for (int i = 0; i < max_items; ++i) {
            int sz = len_d(rnd);
            string tmp = "";
            for (int j = 0; j < sz; ++j) tmp += (char)('a' + bin_d(rnd));
            cout << tmp << "\n";
        }
    }
    else if (mode == 4) {
        vector<string> v(max_items);
        for (int i = 0; i < max_items; ++i) v[i] = build_str(len_d(rnd), rnd);
        sort(v.rbegin(), v.rend());
        for (const auto& str : v) cout << str << "\n";
    }
    else if (mode == 3) {
        string dup = build_str(50, rnd);
        for (int i = 0; i < max_items; ++i) cout << dup << "\n";
    }
    else if (mode == 2) {
        string pref(90, 'a');
        for (int i = 0; i < max_items; ++i) cout << pref + build_str(10, rnd) << "\n";
    }
    else {
        for (int i = 0; i < max_items; ++i) cout << build_str(len_d(rnd), rnd) << "\n";
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc < 3) return 0;

    string req = argv[1];
    int val = stoi(argv[2]);

    if (req == "strlenlexi") {
        task_c(val);
    }
    else if (req == "strlexi") {
        task_b(val);
    }
    else if (req == "int") {
        task_a(val);
    }

    return 0;
}
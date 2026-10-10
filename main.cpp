#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string data_file = "data.txt";
    unordered_map<string, set<int>> db;
    // Load existing data if file exists
    {
        ifstream fin(data_file);
        if (fin) {
            string idx; long long val;
            while (fin >> idx >> val) {
                db[idx].insert((int)val);
            }
        }
    }
    int n;
    if (!(cin >> n)) return 0;
    string cmd;
    for (int i = 0; i < n; ++i) {
        cin >> cmd;
        if (cmd == "insert") {
            string idx; int val; cin >> idx >> val;
            db[idx].insert(val);
        } else if (cmd == "delete") {
            string idx; int val; cin >> idx >> val;
            auto it = db.find(idx);
            if (it != db.end()) {
                it->second.erase(val);
                if (it->second.empty()) db.erase(it);
            }
        } else if (cmd == "find") {
            string idx; cin >> idx;
            auto it = db.find(idx);
            if (it == db.end() || it->second.empty()) {
                cout << "null\n";
            } else {
                bool first = true;
                for (int v : it->second) {
                    if (!first) cout << ' ';
                    first = false;
                    cout << v;
                }
                cout << '\n';
            }
        }
    }
    // Write back data
    {
        ofstream fout(data_file, ios::trunc);
        for (auto &p : db) {
            for (int v : p.second) {
                fout << p.first << ' ' << v << '\n';
            }
        }
    }
    return 0;
}

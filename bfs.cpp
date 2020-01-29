#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;

void bfs(unordered_map<int, unordered_set<int>>& graph, int start, int end) {
    unordered_map<int, int> visited;
    queue<pair<int, int>> next;
    next.push({start, -1});

    while (!next.empty()) {
        auto [cur, parent] = next.front();
        next.pop();

        cout << cur << " ";

        if (cur == end) {
            cout << "Found!\n" << cur;

            int p = parent;
            while (p != -1) {
                cout << " - " << p;
                p = visited[p];
            }
            cout << endl;

            return;
        }

        for (int n : graph[cur]) {
            if (!visited.count(n)) {
                next.push({n, cur});
            }
        }

        visited[cur] = parent;
    }
}

void bdbfs(unordered_map<int, unordered_set<int>>& graph, int start, int end) {
    unordered_map<int, int> visited_s;
    unordered_map<int, int> visited_e;

    queue<pair<int, int>> next_s;
    queue<pair<int, int>> next_e;

    next_s.push({start, -1});
    next_e.push({end, -1});

    while (!next_s.empty() && !next_e.empty()) {
        auto [cur_s, parent_s] = next_s.front();
        next_s.pop();
        auto [cur_e, parent_e] = next_e.front();
        next_e.pop();

        cout << cur_s << " " << cur_e << " ";

        if (visited_s.count(cur_e) || visited_e.count(cur_s)) {
            cout << "Found!\n";

            list<int> path;

            if (visited_s.count(cur_e))
                path.push_back(cur_e);
            else
                path.push_back(cur_s);

            int p = parent_e;
            while (p != -1) {
                path.push_back(p);
                p = visited_e[p];
            }

            p = parent_s;
            while(p != -1) {
                path.push_front(p);
                p = visited_s[p];
            }

            list<int>::reverse_iterator i = path.rbegin();
            cout << *i++;
            while (i != path.rend()) {
                cout << " - " << *i;
                ++i;
            }
            cout << endl;

            return;
        }

        for (int n : graph[cur_s]) {
            if (!visited_s.count(n)) {
                next_s.push({n, cur_s});
            }
        }

        for (int n : graph[cur_e]) {
            if (!visited_e.count(n)) {
                next_e.push({n, cur_e});
            }
        }

        visited_s[cur_s] = parent_s;
        visited_e[cur_e] = parent_e;
    }
}

int main() {
    unordered_map<int, unordered_set<int>> graph({
        {0, {3}},
        {1, {3}},
        {2, {3}},
        {3, {0, 1, 2, 4}},
        {4, {3, 5}},
        {5, {4, 6}},
        {6, {5, 7}},
        {7, {6}}
    });

    bfs(graph, 4, 7);
    bdbfs(graph, 4, 7);

    return 0;
}
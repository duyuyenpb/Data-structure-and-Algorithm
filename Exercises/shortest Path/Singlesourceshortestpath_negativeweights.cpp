//https://open.kattis.com/problems/shortestpath3
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2000000000000;

void bellmann_ford(vector<vector<pair<int, long long>>>  &edges, int source, vector<long long>  &dist, vector<bool> &n_cycle) {
	dist.assign(edges.size(), INF);
	n_cycle.assign(edges.size(), false);
	dist[source] = 0;
	for (int i = 0; i < edges.size() - 1; i++) {
		for (int j = 0; j < edges.size(); j++){
			if (dist[j] < INF){
				for (auto &e : edges[j]){
					dist[e.first] = min(dist[e.first], dist[j] + e.second);
				}
			}
		}
	}
	bool ch = true;
	while (ch) {
		ch = false;
		for (int u = 0; u < edges.size(); u++) {
			if (dist[u] == INF) continue;
			for (auto &e : edges[u]) {
				if (dist[e.first] > dist[u] + e.second && !n_cycle[e.first]) {
					dist[e.first] = -INF;
					ch = true;
					n_cycle[e.first] = true;
				}
			}
		}
	}
}

int main() {
	int n, m, q, s;
	while (cin >> n >> m >> q >> s) {
		if (n == 0 && m == 0 && q == 0 && s == 0) break;
		vector<vector<pair<int, long long>>>  e(n, vector<pair<int, long long>>());
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			e[u].push_back({v, (long long)w});
		}

		vector<long long> dist;
		vector<bool> n_cycle;
		bellmann_ford(e, s, dist, n_cycle);
		for (int i = 0; i < q; ++i) {
			int x;
			cin >> x;
			if (dist[x] == INF)
				cout << "Impossible\n";
			else if (n_cycle[x])
				cout << "-Infinity\n";
			else cout << dist[x] << '\n';
		}
		cout << endl;

	}
	return 0;
}

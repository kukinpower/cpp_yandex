#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int 	main() {
	int n;
	cin >> n;
	map<vector<string>, int> m;

	while (n > 0) {
		n--;
		int count;
		cin >> count;
		vector<string> stops(count);
		for (auto &i : stops) {
			cin >> i;
		}
		if (m.find(stops) != m.end()) {
			cout << "Already exists for " << m[stops] << endl;
		} else {
			int size = m.size();
			m[stops] = size + 1;
			cout << "New bus " << size + 1 << endl;
		}
	}
	return 0;
}

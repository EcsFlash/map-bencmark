#include "TreeMap.h"
#include <string>
#include <iostream>
#include "HashMap.cpp"
#include <set>
#include <sstream>
#include <list>
#include <vector>
#include <random>
#include <fstream>


using namespace std;

set<string> result;

set<string> degenerate_keys(int l, int n = 1000) {
	srand((unsigned)time(0));
	while(result.size() < n){
		stringstream ss;
		for (int i = 0; i < l; i++) {
			char k = (rand() % 26) + 65;
			ss << k;
		}
		string temp = "";
		ss >> temp;
		result.insert(temp);
	}
	return result;
}

int main() {
	cout << "Key count: " << '\t' << "Tree map iter_in " << '\t' << "Tree map iter_se " << '\t' << "Tree map iter_rm " << '\t' << "Hash map iter_in " << '\t' << "Hash map iter_se " << '\t' << "Hash map iter_rm " << '\t' << endl;
	ofstream of("res3.txt");
	for (int j = 0; j <= 300000; j+= 1000) {
		cout << j << endl;
		MapLinear<string, int> map2(1000000);
		TreeMap<string, int> map;
		set<string> temp = degenerate_keys(6, j);
		vector<string> ltemp;
		for (auto i : temp) {
			ltemp.push_back(i);
		}

		for (auto i : ltemp) {
			map2.insert(i, 2);
			map.Insert(i, 2);
		}

		random_shuffle(ltemp.begin(), ltemp.end());

		for (auto i : ltemp) {
			map.Search(i);
			map2.search(i);
		}
		random_shuffle(ltemp.begin(), ltemp.end());
		for (auto i : ltemp) {
			map.Remove(i);
			map2.remove(i);
		}
		cout << sizeof(map) << '\t' << sizeof(map2) << endl;
		of << temp.size()  << '\t' << map.iterations_i << '\t' << map.iterations_s << '\t' << map.iterations_r << '\t' << map2.iterations_i << '\t' << map2.iterations_s << '\t' << map2.iterations_r << endl;
	}
	of.close();
}
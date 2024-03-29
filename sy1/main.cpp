#include<bits/stdc++.h>
#include"FA.h"
#include <iostream>
using namespace std;

int main()
{
	//vector<int> K = { 0,1,2,3,4 };
	//vector<char> Sigma = {'a','b' };
	//vector<vector<vector<int>>> f(5);
	//f[0].push_back({ 0,3 });
	//f[0].push_back({ 0,1 });
	//f[1].push_back({});
	//f[1].push_back({ 2 });
	//f[2].push_back({ 2 });
	//f[2].push_back({ 2 });
	//f[3].push_back({ 3 });
	//f[3].push_back({});
	//f[4].push_back({ 4 });
	//f[4].push_back({ 4 });
	//vector<int> S = { 0 };
	//vector<int> Z = { 2,4 };


	freopen("./example2.txt", "r", stdin);
	
	int n, m, p, q, t;	cin >> n >> m >> p >> q >> t;
	vector<int> K,S,Z;
	vector<vector<vector<int>>> F;
	vector<char> Sigma;
	for (int i = 0; i < n; i++)	K.push_back(i);
	for (int i = 0; i < m; i++) {
		string s;	cin >> s;
		if (s != "epsilon")
			Sigma.push_back(s[0]);
		else Sigma.push_back('\0');
	}
	F.resize(n);
	for (int i = 0; i < n; i++)
	{
		F[i].resize(m);
	}
	for (int i = 0; i < p; i++)
	{
		int c, u, v;
		cin >> c >> u >> v;
		F[u][c].push_back(v);
	}
	for (int i = 0; i < q; i++) {
		int u; cin >> u; S.push_back(u);
	}
	for (int i = 0; i < t; i++) {
		int u;	cin >> u; Z.push_back(u);
	}
	NondeterministicFiniteAutomata nfa = NondeterministicFiniteAutomata(K, Sigma, F, S, Z);
	DeterministicFiniteAutomata dfa = Determine(nfa);
	dfa.paint();

	//system("python paint.py");
	return 0;
}
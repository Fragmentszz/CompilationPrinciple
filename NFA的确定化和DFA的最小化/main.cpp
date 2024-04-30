#include<iostream>
#include<set>
#include<vector>
#include"FA.h"
using namespace std;

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

void createTest(int test_num) 
{
	std::ofstream outputFile("test.txt",ios::out);
	if (!outputFile) {
		std::cerr << "无法打开文件" << std::endl;
		return;
	}

	// 初始化随机数生成器
	std::srand(std::time(0));

	// 设置字符串长度
	const int MAX_LENGTH = 20;

	// 生成并写入1000个随机字符串
	for (int i = 0; i < test_num; ++i) {
		std::string randomString;
		int nowl = rand() * 1.0 / RAND_MAX * MAX_LENGTH + 1;
		randomString.resize(nowl);

		for (int j = 0; j <nowl; ++j) {
			// 随机选择'a', 'b', 或 'c'
			char randomChar = 'a' + std::rand() % 3;
			randomString[j] = randomChar;
		}

		outputFile << randomString << std::endl;
	}
	outputFile.close();
	std::cout << "随机字符串已写入test.txt" << std::endl;
}


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


	freopen("./minimize_example_3.txt", "r", stdin);
	
	int n, m, p, q, t;	cin >> n >> m >> p >> q >> t;
	vector<int> K,S,Z;
	vector<vector<vector<int>>> F;
	vector<vector<int>> f;
	vector<char> Sigma;
	for (int i = 0; i < n; i++)	K.push_back(i);
	for (int i = 0; i < m; i++) {
		string s;	cin >> s;
		if (s != "epsilon")
			Sigma.push_back(s[0]);
		else Sigma.push_back('\0');
	}
	F.resize(n);
	f.resize(n);
	for (int i = 0; i < n; i++)
	{
		F[i].resize(m);
		f[i].resize(m);
		for (int j = 0; j < m; j++)	f[i][j] = -1;
	}
	for (int i = 0; i < p; i++)
	{
		int c, u, v;
		cin >> c >> u >> v;
		F[u][c].push_back(v);
		f[u][c] = v;
	}
	for (int i = 0; i < q; i++) {
		int u; cin >> u; S.push_back(u);
	}
	for (int i = 0; i < t; i++) {
		int u;	cin >> u; Z.push_back(u);
	}

	NondeterministicFiniteAutomata nfa = NondeterministicFiniteAutomata(K, Sigma, F, S, Z);
	DeterministicFiniteAutomata dfa = Determine(nfa);
	// DeterministicFiniteAutomata dfa = DeterministicFiniteAutomata(K, Sigma, f, S[0], Z);
	nfa.paint();				//nfa的png
	dfa.paint();				//dfa的png


	DeterministicFiniteAutomata dfa2 = dfa.minimize();
	dfa2.paint("DFA_min.png");	//dfa2的png
	int test_num = 1000000;
	createTest(test_num);
	ifstream fin;
	fin.open("test.txt",ios::in);
	for (int i = 0; i < test_num; i++)
	{
		string t;	fin >> t;
		/*cout << t << endl;*/
		bool c1 = nfa.check(t), c2 = dfa.check(t), c3 = dfa2.check(t);
		if (c1 !=  c2 || c1 != c3 || c2 != c3)
		{
			cout << c1 << " " << " " << c2 << " " << c3 << " " << t << endl;
		}
	}
	return 0;
}
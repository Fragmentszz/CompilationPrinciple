#include<bits/stdc++.h>
using namespace std;

class ReturnInt
{
	vector<int> vi;
	int i;
public:
	ReturnInt(int _i = 0);
	ReturnInt(vector<int> _vi);
	operator int();
	operator vector<int>();
};


class FA
{
protected:
	vector<int> K, Z;
	vector<bool> isEnd;
	vector<char> Sigma;
	int n, m;
	map<char, int> ys;
public:
	FA(vector<int> _K, vector<char> _Sigma,vector<int> _Z);
	virtual ReturnInt next(int u, char c) = 0;
	int getM() const;
	int getN() const;
	bool IsEnd(int t);
	vector<char> getSigma() const;
	//virtual vector<int> closure(vector<int> I) = 0;
	//virtual vector<int> move(vector<int> I, char c) = 0;
};


class NondeterministicFiniteAutomata
	:public FA
{
protected:
	vector<int> S;
	vector<vector<vector<int>>> f;
public:
	NondeterministicFiniteAutomata(vector<int> _K, vector<char> _Sigma, vector<vector<vector<int>>> _f, vector<int>_S, vector<int>_Z);
	virtual ReturnInt next(int u, char c);
	virtual vector<int> closure(vector<int> I);
	virtual vector<int> move(vector<int> I, char c);
	vector<int> getStart() const;
};

class DeterministicFiniteAutomata
	:public FA
{
	int S;
	vector<vector<int>> f;
public:
	DeterministicFiniteAutomata(vector<int> _K, vector<char> _Sigma, vector<vector<int>> _f, int S, vector<int> _Z);
	virtual ReturnInt next(int u, char c);
	void paint() const;
};


DeterministicFiniteAutomata Determine(NondeterministicFiniteAutomata& dfa);
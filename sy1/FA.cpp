#include"FA.h"
#include<fstream>
#include<sstream>
ReturnInt::ReturnInt(int _i)
	:i(_i)
{

}

ReturnInt::ReturnInt(vector<int> _vi)
	:vi(_vi),i(0)
{

}

ReturnInt::operator vector<int>(){return vi; }
ReturnInt::operator int() { return i; }

FA::FA(vector<int> _K, vector<char> _Sigma, vector<int> _Z)
	:K(_K),Sigma(_Sigma),Z(_Z)
{
	n = _K.size(); m = _Sigma.size();
	for (int i = 0; i < m; i++) {
		ys[_Sigma[i]] = i;
	}
	isEnd.resize(n, 0);
	for (int i = 0; i < _Z.size(); i++)
	{
		isEnd[_Z[i]] = 1;
	}
}
int FA::getM() const
{
	return m;
}
int FA::getN() const
{
	return n;
}

vector<char> FA::getSigma() const
{
	return Sigma;
}

bool FA::IsEnd(int t)
{
	if (t >= n)	return 0;
	return isEnd[t];
}
/*********************************************************/
vector<int> bfs(vector<int> I, vector<vector<int>> g)
{
	int n = g.size();
	vector<bool> vis(n, 0);
	queue<int> q;
	for (int u : I)	q.push(u);
	vector<int> ans;
	while (!q.empty())
	{
		int f = q.front(); q.pop();
		if (vis[f])	continue;
		vis[f] = 1;
		ans.push_back(f);
		for (int v : g[f])
		{
			if (!vis[v])	q.push(v);
		}
	}
	return ans;
}

NondeterministicFiniteAutomata::NondeterministicFiniteAutomata(vector<int> _K, vector<char> _Sigma, vector<vector<vector<int>>> _f, vector<int>_S, vector<int>_Z)
	:FA(_K,_Sigma,_Z),f(_f),S(_S)
{
	
}

ReturnInt NondeterministicFiniteAutomata::next(int u, char c)
{
	return f[u][ys[c]];
}

vector<int> NondeterministicFiniteAutomata::closure(vector<int> I)
{
	if (ys.find('\0') != ys.end())
	{
		int c = ys['\0'];
		vector<vector<int>> g;
		for (auto row : f)
		{
			g.push_back(row[c]);
		}
		return bfs(I, g);
	}
	else
	{
		cout << "字符表中没有epsilon字符!!" << endl;
		return I;
	}
}

vector<int> NondeterministicFiniteAutomata::move(vector<int> I, char c)
{
	if (ys.find(c) != ys.end())
	{
		int column = ys[c];
		vector<int> ans;
		vector<bool> vis(n, 0);
		for (int u : I)
		{
			for (int v : f[u][column])
			{
				if (!vis[v])
				{
					ans.push_back(v);
					vis[v] = 1;
				}
			}
		}
		return ans;
	}
	else
	{
		cout << "字符表中没有该" << c << "字符!!" << endl;
		return {};
	}
}

vector<int> NondeterministicFiniteAutomata::getStart() const
{
	return S;
}





/*******************************************************/
DeterministicFiniteAutomata::DeterministicFiniteAutomata(vector<int> _K, vector<char> _Sigma, vector<vector<int>> _f, int _S, vector<int> _Z)
	:FA(_K,_Sigma,_Z),f(_f), S(_S)
{
}

ReturnInt DeterministicFiniteAutomata::next(int u, char c)
{
	return f[u][ys[c]];
}

void DeterministicFiniteAutomata::paint() const
{
	ofstream fout("./html/render.txt", ios::out);
	vector<vector<int>> edges;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			edges.push_back({ j,i,f[i][j] });
		}
	}
	fout << n << " " << m << " " << n * m << " " << 1 << " " << Z.size() << endl;
	for (int i = 0; i < m; i++)	fout << Sigma[i] << " ";
	fout << endl;
	for (auto edge : edges)
	{
		for (int v : edge)	fout << v << " ";
		fout << endl;
	}
	fout << S << endl;
	for (int i = 0; i < Z.size(); i++)	fout << Z[i] << " ";
	fout << endl;
	fout.close();
	system("python paint.py ./html/render.txt");
}



/*************************************************************************/
DeterministicFiniteAutomata Determine(NondeterministicFiniteAutomata& nfa)
{
	queue<int> q;
	vector<int> S = nfa.getStart();
	vector<int> Ks = nfa.closure(S);
	vector<vector<int>> K;
	K.push_back(Ks);
	vector<vector<int>> F;
	int m = nfa.getM(), n = nfa.getN();
	vector<char> Sigma0 = nfa.getSigma();
	vector<char> Sigma = {};
	for (char c : Sigma0) { if (c != '\0')Sigma.push_back(c); }
	for (int k = 0;; k++)
	{
		if (k >= K.size())	break;
		vector<int> nowstate = K[k];
		F.push_back(vector<int>(Sigma.size(), -1));
		for (int i = 0; i < Sigma.size(); i++)
		{
			vector<int> tmp = nfa.move(nowstate, Sigma[i]);
			vector<int> newstate = nfa.closure(tmp);
			vector<bool> newbool(n, 0);
			for (int u : newstate)	newbool[u] = 1;
			int flag = -1;
			for (int j = 0; j < K.size(); j++)
			{
				vector<int> oristate = K[j];
				vector<bool> oribool(n, 0);
				for (int v : oristate)	oribool[v] = 1;
				bool same = 1;
				for (int i = 0; i < n; i++) {
					if (newbool[i] != oribool[i])
					{
						same = 0;
						break;
					}
				}
				if (same) {
					flag = j;
					break;
				}
			}
			if (flag >= 0) { F[k][i] = flag; }
			else {
				F[k][i] = K.size();
				K.push_back(newstate);
			}
		}
	}
	vector<int> Kt = {};
	vector<int> Kk = {};
	for (int i = 0; i < K.size(); i++)
	{
		Kk.push_back(i);
		vector<int> nowstate = K[i];
		for (int v : nowstate) {
			if (nfa.IsEnd(v)) {
				Kt.push_back(i);
				break;
			}
		}
	}
	DeterministicFiniteAutomata dfa = DeterministicFiniteAutomata(Kk, Sigma, F, 0, Kt);

	
	return dfa;
}
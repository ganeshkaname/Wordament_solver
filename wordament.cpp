/*
ID:		ganeshk2
lang:	cpp
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long		ll;
typedef pair<int, int>	ii;
typedef pair<ll, ll>	pll;
typedef vector<int>		vi;
typedef vector<ll>		vl;
typedef vector<ii>		vii;
typedef vector<pll>		vpll;
typedef vector<vi>		vvi;
typedef vector<vl>		vvl;
#define si(x)		scanf("%d",&x)
#define sl(x)		scanf("%I64d",&x)
#define ss(s)		scanf("%s",s)
#define pb			push_back
#define mp			make_pair
#define rep(i,b,a)  for(i=a;i<b;i++)
#define f(i,n)      rep(i,n,0)
#define tr(it,container) for(auto it=container.begin();it!=container.end();++it)
#define all(a)		a.begin(),a.end()
#define sortall(a)	sort(all(a))
#define mem(a,x)	memset(a,x,sizeof(a))
#define MOD			1000000007
#define PI          3.1415926535897932384626
#define F			first
#define S			second
#define endl		'\n'
/*
*/
#define maxn 100010

vector<string> ans;
string str[4];
int l[4][4],r[4][4],up[4][4],down[4][4],visited[4][4];

/*			define trie struct 			*/
struct trie{
	bool flag;
	trie *node[26];
	trie(){
		flag=0;
		for(int i=0; i<26; i++) node[i] = NULL;
	}
};

trie *insert(trie *t,int pos,string &s)
{
	if(pos == s.size())
	{
		t->flag=1;
		return t;
	}
	int ch = s[pos]-'a';
	if(t->node[ch] == NULL) {
		t->node[ch] = new trie();
	}
	t->node[ch] = insert(t->node[ch], pos + 1, s);
	return t;
}

bool trie_search(trie *t, int pos, string &s)
{
	if( pos == s.size() && t->flag == 1) return true;
	if( pos == s.size() ) return false;
	int ch = s[pos]-'a';
	if(t->node[ch] == NULL) return false;
	return trie_search(t->node[ch], pos + 1, s);

}
/*			trie part ends here			*/

/*			reset matrix values			*/
void set_val()
{
	int i,j;
	mem(visited,0);
	f(i,4) f(j,4) l[i][j] = 1, r[i][j] = 1, up[i][j] = 1, down[i][j] = 1;
	f(i,4) l[i][0] = 0, r[i][3] = 0, up[0][i] = 0, down[3][i] = 0;
}

/*		calculate every possible word	*/
void cal_dfs(string s,int i,int j)
{
	string a;
	a = s;
	a += str[i][j];
	ans.pb(a);
	visited[i][j] = 1;
	if(j>0 and l[i][j] and !visited[i][j-1]) cal_dfs(a,i,j-1);
	if(j<3 and r[i][j] and !visited[i][j+1]) cal_dfs(a,i,j+1);
	if(i>0 and up[i][j] and !visited[i-1][j]) cal_dfs(a,i-1,j);
	if(i<3 and down[i][j] and !visited[i+1][j]) cal_dfs(a,i+1,j);
	visited[i][j] = 0;
}

int main()
{	
	trie *t = new trie();
	ifstream iFile("wordsEn.txt");
	while(true)
	{
		string aa;
		iFile >> aa;
		if(iFile.eof()) break;
		t = insert(t,0,aa);
	}
	int i,j;
	// string aa;
	// f(i,5)
	// {
	// 	cin>>aa;
	// 	t = insert(t,0,aa);
	// }
	f(i,4) cin>>str[i];
	set_val();
	string s="";
	f(i,4) f(j,4) cal_dfs(s,i,j);
	//f(i,ans.size()) cout<<ans[i]<<endl;
	f(i,ans.size())
	{
		if(trie_search(t,0,ans[i])) cout << ans[i] << endl;
	}

return 0;
}
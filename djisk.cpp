/*short and int: -32,767 to 32,767
**unsigned short int and unsigned int: 0 to 65,535
**long int: -2,147,483,647 to 2,147,483,647
**unsigned long int: 0 to 4,294,967,295
**long long int: -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
**unsigned long long int: 0 to 18,446,744,073,709,551,615.*/

#include <bits/stdc++.h>
#define lli long long int
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define pf push_front
#define MOD 1000000007
#define F first
#define S second
#define inf INT_MAX
#define gcd(x,y) __gcd(x,y)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define i_am_iron_man ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

vector <int> v;

const int MAX=100001;
typedef pair <long long ,int> P;
bool marked[MAX];
vector <P> adj[MAX];
const int INF=999999;
int d[MAX];
int parent[MAX];
int Diskstra(int n,int s,int v)
{
		priority_queue< P,vector<P>,greater<P> >Q;
		for(int i =0 ; i<=n ; i++){
            d[i]=INF;
		}
		memset(parent,-1,sizeof(parent));
		memset(marked,false,sizeof(marked));
		int x;
		P p;
		d[s]=0;
		int y,z;
		Q.push(make_pair(0,s));

		while(!Q.empty())
		{
			p=Q.top();
			Q.pop();
			x=p.second;
			if(marked[x]==true)
				continue;
			 marked[x]=true;
			for (int i = 0; i < adj[x].size(); ++i)
			{
					z=adj[x][i].second;
					y=adj[x][i].first;
					if(d[z]>d[x]+y)
					{
						d[z]=d[x]+y;
						Q.push(make_pair(d[z],z));
						parent[z]=x;
                    }

            }
		}
		return d[v];

}

int main()
{
    i_am_iron_man
    int agents;
    float battery_capacity;
    cout << "Enter the number of agents(population size): " << endl;
    cin >> agents;
    cout << "Enter battery capacity for the cars: " << endl;
    cin >> battery_capacity;
    for(int z = 1; z <= agents; z++)
    {
        cout << "Enter the SoC  for agent " << z << endl;
        int n,edges;
        float soc, curr_bat_cap;
        cin >> soc;
        curr_bat_cap = (soc*battery_capacity)/100 ;
        cout << "Current battery level is: " << curr_bat_cap << endl;
        cout << "Enter number of nodes and edges: " << endl;
        cin>>n>>edges;
        int x,y;
        long long weight;
        cout << "Enter the connections between nodes and energy expenditure for every node now: " << endl;
        for(int i = 0; i < edges; ++i)
        {
                cin>>x>>y>>weight;
                adj[y].push_back(make_pair(weight,x));
                adj[x].push_back(make_pair(weight,y));
        }
        cout << "Now enter the source and destination: " << endl;
        cin>>x>>y;
        int res_dis = Diskstra(n,x,y);

        vector<int> res;
        int u=y;
        while(u!=x ||  u==-1){
            res.push_back(u);
            u=parent[u];
        }
        if(u==-1){
            cout<<"Sorry, no such path exists" <<endl;
            break;
        }
        res.push_back(u);
        cout<<endl;
        reverse(res.begin(),res.end());
        for(int i =0  ; i< res.size() ; i++){
            cout<<res[i]<<" ";
    }
    cout << endl;
    cout << "Total energy expenditure along the path is: " << res_dis << endl;
    if(curr_bat_cap < res_dis)
        v.pb(z);
   }
   cout << "The following agents will need refilling from charging stations: " << endl;
   for(int i = 0; i < v.size(); i++)
       cout << v[i] << " ";
    cout << endl;
	return 0;
}

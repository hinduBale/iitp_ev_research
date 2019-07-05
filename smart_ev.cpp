/*short and int: -32,767 to 32,767
**unsigned short int and unsigned int: 0 to 65,535
**long int: -2,147,483,647 to 2,147,483,647
**unsigned long int: 0 to 4,294,967,295
**long long int: -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
**unsigned long long int: 0 to 18,446,744,073,709,551,615.*/

#include <bits/stdc++.h>
#include <fstream>
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

float battery_capacity;
int vir_q_capacity;

vector <pii> graph[10010];
vector <int> charging_stations;
int phy_q[100];
int vir_q[100];
int W[100];
float Wc[100];
float NEVSE[100];
float Nc[100];
float Rc[100];
float slot_min[100];
float EV_target[100][100];
float EV_current[100][100];
float soc[100][100];
float Wq[100][100];
int Wq_sum[100];

void welcome()
{
    cout << "*********************************************************************** " << endl;
    cout << "WELCOME TO THE SMART_EV_SLOTS" << endl;
    cout << "*********************************************************************** " << endl;
    cout << "Enter battery capacity for a typical EV in this test run: " << endl;
    cin >> battery_capacity;
}

void create_graph(int nodes, int edges)
{
    int a, b, weight, i = 0;
    int A[100], B[100], W[100];
    ifstream infile;
    infile.open("graph_input.txt");
    if(!(infile.is_open()))
    {
        cout << "\"graph_input.txt\" file cannot be opened due to some reason" << endl;
        exit(1);
    }
    else
    {
        infile >> nodes >> edges;
        while(!(infile.eof()))
        {
            infile >> a >> b >> weight;
            A[i] = a;
            B[i] = b;
            W[i] = weight;
            ++i;
        }
        for(int i = 0; i < edges; i++)
        {
            graph[A[i]].pb({B[i], W[i]});
            graph[B[i]].pb({A[i], W[i]});
        }
        cout << "Graph successfully created" << endl;
    }


}

void create_CS_array(int nodes, int initial, int destination)
{
    for(int i = 1; i <= nodes; i++)
        if(!((i == initial) || (i == destination)))
            charging_stations.pb(i);
}

void view_CS_array()
{
    cout << "Charging stations on the map are: " << endl;
    for(auto i : charging_stations)
        cout << i << " ";
    cout << endl;
}

void initialise(int i)
{
    Wc[i] = 120;
    NEVSE[i] = 5;
    Rc[i] = 1.2;
    Nc[i] = 1 + (rand()%(5 - 1 + 1));
    slot_min[i] = Wc[i];
    for(int j = 1; j <= Nc[i]; j++)
    {
        cout << "Enter SoC for car number " << j << " at CS number " << i << endl;
        cin >> soc[i][j];
        EV_current[i][j] = (soc[i][j]*battery_capacity)/100;
        EV_target[i][j] = battery_capacity;
    }
    int phy_queue_ev = 0 + (rand() %(5-0+1)); //Generating random number of cars in the physical queue.
    int virtual_queue_ev = 0 + (rand() %(5-0+1));
    phy_q[i] = phy_queue_ev;
    vir_q[i] = virtual_queue_ev;
}

int main()
{
    i_am_iron_man
    lli initial, destination, nodes, edges;
    welcome();
    cout << "Accessing the graph input: " << endl;
    create_graph(nodes, edges);
    cout << "Enter the initial starting point and the source: " << endl;
    cin >> initial >> destination;
    create_CS_array(nodes, initial, destination);
    for(auto each_cs : charging_stations)
    {
        int sum = 0;
        cout << "For charging station number: " << each_cs << endl;
        initialise(each_cs);
        int phy_queue_ev_main = phy_q[each_cs];
        int vir_queue_ev_main = vir_q[each_cs];
        if(Nc[each_cs] < NEVSE[each_cs])
            Wc[each_cs] = 0;
         else
            for(int each_ev = 0; each_ev < Nc[each_cs]; each_ev++)
                if((float)((EV_target[each_cs][each_ev] - EV_current[each_cs][each_ev])/Rc[each_cs]) < slot_min[each_cs])
                    Wc[each_cs] = (EV_target[each_cs][each_ev] - EV_current[each_cs][each_ev])/Rc[each_cs];

        for(int phy_queue_ev_it = 0; phy_queue_ev_it < phy_queue_ev_main; phy_queue_ev_it++)
           Wq[each_cs][phy_queue_ev_it] += (EV_target[each_cs][phy_queue_ev_it] - EV_current[each_cs][phy_queue_ev_it])/Rc[each_cs];

        for(int sum_ev = 0; sum_ev < phy_queue_ev_main; sum_ev++)
            sum += Wq[each_cs][sum_ev];
        Wq_sum[each_cs] = sum;
        W[each_cs] = Wc[each_cs] + Wq_sum[each_cs]; //Waiting time at each CS.

        cout << "The LISTslot consists of " << vir_q[each_cs] << " EVs in the virtual queue " << phy_q[each_cs] << " EVs in the physical queue with a total waiting time of " << W[each_cs] << "minutes" << endl;
    }
    return 0;
}

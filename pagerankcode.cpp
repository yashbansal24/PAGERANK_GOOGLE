#include<bits/stdc++.h>
#define NODES 6301
#define EDGES 20777
#pragma comment(linker, "/STACK:20000000")
#pragma comment(linker, "/HEAP:20000000")
using namespace std;

vector< int > v[NODES];       /*  Remember it is a Column Vector list*/
vector<int> sum(NODES);
vector<long double> ranks(NODES);
vector<long double> new_ranks(NODES);
vector<long double> errors;

int read_data()
{

        std::ifstream file("dataset.txt");
        std::string   line;
        int i=0,j;
        while(std::getline(file, line))
        {

          std::stringstream   linestream(line);

          int                 val1;
          int                 val2;

          linestream >> val1 >> val2;
          v[val2].push_back(val1);
          sum[val1]++;

          i++;
        }
        /*
        DEAD ends and spider traps handling
        */
        for(i=0;i<NODES;i++)
        {
            if(sum[i]==0)
            {
                sum[i]=NODES;
                for(j=0;j<NODES;j++)
                v[i].push_back(j);
            }
        }
        return 0;

}

void print_ranks()
{
    for(int i=0;i<10;i++)
    {
        cout<< "[ "<< ranks[i] << " ]"<<endl;

    }
}

int power_method(long double beta,long double epsilon)
{
    int i,j,k=0;
    long double error,curr_rank=0;
    long double a=1.0*(1.0 - beta) / NODES  ;
    //b=0.85*1.0/sum[v[i][j]];
    for(i=0;i<NODES;i++)
        {
            ranks[i]=1.0/NODES;
        }

    while(1 && k<=40)
    {
        k++;
        for(i=0;i<NODES;i++)
        {
            curr_rank=0;
            for(j=0;j<v[i].size();j++)
            {
                curr_rank += .85*ranks[v[i][j]]/sum[v[i][j]];
                //if(sum[v[i][j]]<0) {cout<<"Error3"<<" "<<k;return 0;}
            }
            //if(curr_rank<0) {cout<<"Error2"<<" "<<k;return 0;}
            curr_rank += a;


            new_ranks[i]= curr_rank;
            //cout<<curr_rank<<endl;
        }
        error=0;
        for(i=0;i<NODES;i++)
        {
            error+=pow(abs(new_ranks[i] - ranks[i]),2);
            ranks[i]=new_ranks[i]/1.0;
            //if(ranks[i]<0) {cout<<"Error5"<<" "<<k;return 0;}
        }
        errors.push_back(error);
        //print_ranks();
        if(error<=epsilon)
            {cout<<k<<endl;break;}
    }
    return 0;
}

void write_file()
{
    ofstream output;
    output.open ("output.txt");
    for(int i=0;i<NODES;i++)
    output << ranks[i]<<endl;

    output.close();

    output.open ("errors.txt");
    for(int i=0;i<errors.size();i++)
    output << errors[i]<<endl;

    output.close();

}

int main()
{
    read_data();
    power_method(.85,0.000001);
    print_ranks();
    write_file();

    return 0;
}

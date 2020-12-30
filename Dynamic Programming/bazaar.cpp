#include<iostream>
#include<vector>
using namespace std;
#define INFINITY 2147483647


vector<int> knapsack(vector<pair<int,int>> offer,int N){
    int P = offer.size();
    vector<vector <int>> min_cost(P+1, vector<int>(N+1));
    for(int p=0; p<=P; p++){
        min_cost[p][0] = 0;
    }
    for(int i=1; i<=N; i++){
        min_cost[0][i] = INFINITY;
    }
    for(int p=1; p<=P; p++){
        for(int i=1; i<=N; i++){
            if(i-offer[p-1].first>=0){
                int tmp; 
                if(min_cost[p-1][i-offer[p-1].first]==(INFINITY)){
                    tmp = INFINITY;
                }
                else{
                    tmp = min_cost[p-1][i-offer[p-1].first] + offer[p-1].second;
                }
                
                if(tmp>min_cost[p-1][i]){
                    min_cost[p][i] = min_cost[p-1][i]; 
                }
                else
                {
                    min_cost[p][i] = tmp;
                }
                
            }
            else{
                int tmp = offer[p-1].second;
                if(tmp>min_cost[p-1][i]){
                    min_cost[p][i] = min_cost[p-1][i];
                }
                else{
                    min_cost[p][i] = tmp;
                }
                
            }            
        }
    }
    return min_cost[P];
}
void add(vector<int> &min_cost,vector<int> tmp){
    for(int i=0; i<min_cost.size(); i++){
        if((min_cost[i]==(INFINITY))||(tmp[i]==(INFINITY))){
            min_cost[i] = INFINITY;            
        }
        else{
            min_cost[i]+=tmp[i];
        }        
    }
}
int main(){
    
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);
    
    vector<pair<int,int>> offer1A;
    vector<pair<int,int>> offer1B;
    vector<pair<int,int>> offer1C;
    vector<pair<int,int>> offer2A;
    vector<pair<int,int>> offer2B;
    vector<pair<int,int>> offer2C;
    vector<pair<int,int>> offer3A;
    vector<pair<int,int>> offer3B;
    vector<pair<int,int>> offer3C;

    int dealer;
    char product;
    int quantity;
    int value;
    for(int i=0; i<M; i++){
        scanf("%d",&dealer);
        product = getchar();
        scanf("%d",&quantity);
        scanf("%d",&value);
        if(dealer==1){
            if(product=='A'){
                offer1A.push_back({quantity,value});
            }
            else if(product=='B'){
                offer1B.push_back({quantity,value});
            }
            else{
                offer1C.push_back({quantity,value});
            }
        }
        else if(dealer==2){
            if(product=='A'){
                offer2A.push_back({quantity,value});
            }
            else if(product=='B'){
                offer2B.push_back({quantity,value});
            }
            else{
                offer2C.push_back({quantity,value});
            }
        }
        else{
            if(product=='A'){
                offer3A.push_back({quantity,value});
            }
            else if(product=='B'){
                offer3B.push_back({quantity,value});
            }
            else{
                offer3C.push_back({quantity,value});
            }
        }
    }
    
    vector<int> min_cost1;
    min_cost1 = knapsack(offer1A,N);
    add(min_cost1,knapsack(offer1B,N));
    add(min_cost1,knapsack(offer1C,N));
    
    vector<int> min_cost2;
    min_cost2 = knapsack(offer2A,N);
    add(min_cost2,knapsack(offer2B,N));
    add(min_cost2,knapsack(offer2C,N));
    
    vector<int> min_cost3;
    min_cost3 = knapsack(offer3A,N);
    add(min_cost3,knapsack(offer3B,N));
    add(min_cost3,knapsack(offer3C,N));
    int min = INFINITY;
    for(int i=0; i<=N; i++){
        for(int j=0; j<=N; j++){
            int pos = N-i-j;
            if(pos<0){
                continue;
            }
            int tmp;
            if((min_cost1[i]==(INFINITY))||(min_cost2[j]==(INFINITY))||(min_cost3[pos]==(INFINITY))){
                tmp = INFINITY;
            }
            else{
                tmp = min_cost1[i]+min_cost2[j]+min_cost3[pos];
            }
            if(min>tmp){
                min = tmp;
            }
        }
    }
    if(min==(INFINITY)){
        cout<<-1<<endl;
    }
    else{
        cout<<min<<endl;
    }
    
}
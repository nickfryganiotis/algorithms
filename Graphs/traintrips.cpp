#include<iostream>
#include<vector>
#include <queue>
#include<algorithm>
using namespace std;
#define INFINITY 18446744073709551615
typedef pair<unsigned long long int,int> iPair;

vector<unsigned long long int> Dijkstra(int min_dist,vector<int> d){
    priority_queue< iPair , vector<iPair> , greater<iPair> > heap;
    vector<unsigned long long int> D(min_dist, INFINITY);
    heap.push({0, 0}); 
    D[0] = 0;  
    while (!heap.empty()){
        int src = heap.top().second;
        unsigned long long int path = heap.top().first;
        heap.pop();
        if(path==INFINITY){
            break;
        }
        for(int i=0; i<d.size(); i++){
            if(d[i]!=min_dist){
                int dst = (d[i]+path)%min_dist;
                if(D[dst]>D[src]+d[i]){
                    D[dst] = D[src]+d[i];
                    heap.push({D[dst], dst});
                }
            }
        }
    } 

    return D;

}
int main(){
    int N,Q;
    scanf("%d",&N);
    scanf("%d",&Q);

    int tmp;
    int min_dist = 10000;
    vector<int> d(N);
    for(int i=0; i<N; i++){
        scanf("%d",&tmp);
        d[i] = tmp;
        min_dist = min(min_dist,tmp);
    }

    vector<int> s(Q);
    for(int j=0; j<Q; j++){
        scanf("%d",&tmp);
        s[j] = tmp;
    }

    
    vector<unsigned long long int> D = Dijkstra(min_dist,d);
    
    for(int j=0; j<Q; j++){
        if( (D[(s[j] % min_dist)]<INFINITY) && (D[(s[j] % min_dist)]<=s[j])){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }


}
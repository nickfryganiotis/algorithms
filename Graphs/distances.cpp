#include <iostream>
#include <vector>
using namespace std;

int find(vector<pair<int,int>>&trees, int i) {  
    if (trees[i].second != i) 
        trees[i].second = find(trees, trees[i].second); 
    return trees[i].second; 
}

void Union(vector<pair<int,int>>&trees, int a, int b) { 
    int rootA = find(trees, a); 
    int rootB = find(trees, b); 
    
    if (trees[rootA].first < trees[rootB].first) 
        trees[rootA].second = rootB; 
    else if (trees[rootA].first > trees[rootB].first) 
        trees[rootB].second = rootA; 

    else{ 
        trees[rootB].second = rootA; 
        trees[rootA].first++; 
    } 
}

vector<vector <pair<int,int>>> Boruvkas_function(vector<vector<int>>Graph,int V,int E) { 
    
    vector<pair<int,int>>trees;
    vector<vector <pair<int,int>>> Mst(V);
      
    for (int i = 0; i < V; i++) { 
        trees.push_back(make_pair(0,i));
    } 
    
    int TotalTrees = V; 
    int MST_total_weight = 0; 
    
    while (TotalTrees > 1) { 
        
        vector<int> smallest_edge(V,-1);
        for (int i=0; i<E; i++) { 
            
            int setA = find(trees, Graph[i][0]); 
            int setB = find(trees, Graph[i][1]); 
            
            if (setA == setB) 
                continue; 
            else{ 
            if (smallest_edge[setA] == -1 || 
                Graph[smallest_edge[setA]][2] > Graph[i][2]) 
                smallest_edge[setA] = i; 
            if (smallest_edge[setB] == -1 || 
                Graph[smallest_edge[setB]][2] > Graph[i][2]) 
                smallest_edge[setB] = i; 
            } 
        } 
        
        for (int i=0; i<V; i++) { 
             
            if (smallest_edge[i] != -1) { 
                
                int setA=find(trees, Graph[smallest_edge[i]][0]); 
                int setB=find(trees, Graph[smallest_edge[i]][1]); 
                if (setA == setB) 
                    continue; 
                MST_total_weight += Graph[smallest_edge[i]][2];
                Mst[Graph[smallest_edge[i]][0]].push_back({Graph[smallest_edge[i]][1],Graph[smallest_edge[i]][2]}); 
                Mst[Graph[smallest_edge[i]][1]].push_back({Graph[smallest_edge[i]][0],Graph[smallest_edge[i]][2]}); 
                Union(trees, setA, setB); 
                TotalTrees--;
            } 
        } 
    } 

    return Mst;
} 

int dfs(vector<unsigned long long int> &EdgeFrequency,vector<vector<pair<int,int>>> &Tree,int &N,int u=0,int p=0){
    int sz = 1;
    
    for(auto &v: Tree[u]){
        if(v.first!=p){
            
            int val = dfs(EdgeFrequency,Tree,N,v.first,u);
            int m = v.second;
            EdgeFrequency[m] = (unsigned long long int) val*(N-val);

            sz+=val;
        }
    }
    return sz;
}


int main(){
    
    //Read the input
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);

    vector<vector<int>>Graph;

    int src,dst,w;
    for(int i=0; i<M; i++){
        scanf("%d",&src);
        scanf("%d",&dst);
        scanf("%d",&w);
        Graph.push_back({src-1,dst-1,w});
    }

    //Boruvka algorithm returns the Minimum spanning tree
    vector<vector <pair<int,int>>> Mst = Boruvkas_function(Graph,N,M);
    
    vector<unsigned long long int> EdgeFrequency(M,0);
    //count the frequency every edge appears in a shortest path
    int sz = dfs(EdgeFrequency,Mst,N);
    
    unsigned long long int temp,mod;  
    vector<int> bin;  
    for(int i=0; i<M; i++){  
        mod = EdgeFrequency[i]%2;
        if(i<M-1){  
            EdgeFrequency[i+1] = EdgeFrequency[i+1]+(EdgeFrequency[i]-mod)/2;  
            bin.push_back(mod);  
        }  
        else{  
            bin.push_back(mod);  
            if(EdgeFrequency[i]>1){  
                temp = (EdgeFrequency[i]-mod)/2;  
                while(1){  
                    if(temp%2==1&&temp!=1){  
                        bin.push_back(1);  
                        temp=(temp-1)/2;  
                    }  
                    else if(temp==1){  
                        bin.push_back(1);  
                        break;  
                    }  
                    else{  
                        bin.push_back(0);  
                        temp = temp/2;  
                    }  
                }  
            }  
        }  
    }
    
  
    
    
    int c_one=0;  
    for(int i = bin.size()-1; i>=0; i--){  
        if(bin[i]==0 && c_one ==0){  
            continue;  
        }  
        else{  
            cout<<bin[i];  
            c_one = 1;  
        }  
    }  
    cout<<"\n";
         
}
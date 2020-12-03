#include <iostream>        
#include<bits/stdc++.h>        
#include<algorithm>        
using namespace std;        
bool canBeSorted(int N,int M,int c[],vector<pair<int,pair<int,int>>> p,int index){               
    vector<int> adj[N];               
    bool vis[N];        
    for(int i=0; i<N; i++){               
        vis[i] = false;        
    }         
    //construct the adjacency matrix of the subgraph        
    for(int i=index; i<M; i++){        
        adj[p[i].second.first].push_back(p[i].second.second);         
        adj[p[i].second.second].push_back(p[i].second.first);         
    }      
    for (int i = 0; i < N; i++) { 
  
        // If not already visited 
        // then apply BFS 
        if (!vis[i]) { 
            queue<int> q; 
            vector<int> v1; 
            vector<int> v2; 
  
            // Set visited to true 
            vis[i] = true; 
  
            // Push the node to the queue 
            q.push(i); 
  
            // While queue is not empty 
            while (!q.empty()) { 
                int u = q.front(); 
                v1.push_back(u); 
                v2.push_back(c[u]); 
                q.pop(); 
  
                // Check all the adjacent nodes 
                for (auto s : adj[u]) { 
  
                    // If not visited 
                    if (!vis[s]) { 
  
                        // Set visited to true 
                        vis[s] = true; 
                        q.push(s); 
                    } 
                } 
            } 
            sort(v1.begin(), v1.end()); 
            sort(v2.begin(), v2.end()); 
  
            // If the connected component does not 
            // contain same elements then return false 
            if (v1 != v2) 
                return false; 
        } 
    } 
    return true; 
}        
int main(){        
   
    ios::sync_with_stdio(false);        
    //reading input              
    int N,M;        
    cin>>N;                
    cin>>M;

    int c[N];        
    int c_i;        
    for(int i=0; i<N; i++){        
        cin>>c_i;                
        c[i] = c_i-1;        
    }        
        
    vector<pair<int,pair<int,int>>> p(M);        
    int a_i;      
    int b_i;       
    int w_i;        
    for(int i=0; i<M; i++){        
        cin>>a_i;               
        cin>>b_i;                
        cin>>w_i;                
        p[i] = make_pair(w_i,make_pair(a_i-1,b_i-1));        
    }        
             
    sort(p.begin(), p.end());  
               
    //binary search        
    int l=0;        
    int r=M-1;        
    int m = 0;        
    int res = 0;        
    while(l<=r){        
        m = (l+r)/2;        
        if(canBeSorted(N,M,c,p,m)){        
            l = m+1;        
            res = p[m].first;        
        }        
        else{        
            r = m-1;        
        }        
    }               
    cout<<res<<endl;        
}        
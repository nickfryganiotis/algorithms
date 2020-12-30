#include <iostream>  
#include <vector>  
using namespace std;  

void min_cost(int left,int right,vector<vector<int>> &cost,vector<vector<int>> &c,int k,pair<int,int> bound){  
   if(left>right){  
       return;  
   }  
   int mid = (left+right)/2;  
   
   int low = bound.first;  
   int up = bound.second;  
   int tmp_up = up;  
   if(tmp_up>(mid-1)){  
       tmp_up = mid-1;  
    }  
    int index = low;  
    int min = c[index][k-1]+cost[index+1][mid];  
    for(int j=low+1; j<=tmp_up; j++){  
        int tmp = c[j][k-1]+cost[j+1][mid];  
        if(min>tmp){  
            min = tmp;  
            index = j;  
        }  
    }  
    c[mid][k] = min;  
    min_cost(left,mid-1,cost,c,k,{low,index});  
    min_cost(mid+1,right,cost,c,k,{index,up});  
    
}  
int main(){  
    
      
    //Read the input  
    int N,K;    
    scanf("%d",&N);  
    scanf("%d",&K); 
  
    vector<vector<int> > A(N, vector<int>(N));  
    for(int i=0; i<N; i++){  
        A[i][i] = 0;  
        for(int j=i+1; j<N; j++){  
            int num;  
            scanf("%d",&num);  
            A[i][j] = A[j][i] = num;  
        }  
    }  
      
      
    //Calculate cost[1...j]  
    vector<vector<int> > cost(N+1, vector<int>(N+1));  
    for (int i = 0; i <= N; i++){  
        cost[i][0] = 0;  
    }  
    for(int j = 1; j <= N; j++){  
        cost[0][j] = 0;  
    }  
    for (int i=1; i<=N; i++){  
        for(int j=1; j<=i; j++){  
            cost[i][j] = 0;  
        }  
    }  
    for(int j=2; j<=N; j++){  
        for(int i=j-1; i>=1; i--){
            cost[i][j] = cost[i+1][j]+cost[i][j-1]-cost[i+1][j-1]+A[i-1][j-1];    
        }  
    }  
  
    vector<vector<int> > c(N+1, vector<int>(K+1));  
    for(int i=0; i<=N; i++){  
        c[i][0] = 0;  
    }  
    for(int k=1; k<=K; k++){  
        c[0][k] = 0;  
        c[1][k] = 0;  
    }  
    
    
    // Calculating minimum cost for only a box is trivial  
    for(int i=2; i<=N; i++){  
        c[i][1] = cost[1][i];  
    }
    // Calculate minimum cost for k>1 boxes using binary search  
    int left = 1;  
    int right = N;
    for(int k = 2; k<=K; k++){  
        min_cost(left,right,cost,c,k,{left,right});  
    }  
       
      
    cout<<c[N][K]<<endl;  
      
      
}  
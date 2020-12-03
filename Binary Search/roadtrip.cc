#include <iostream>    
#include <algorithm>    
using namespace std;    
    
class sort_indices    
{    
   private:    
     int* mparr;    
   public:    
     sort_indices(int* parr) : mparr(parr) {}    
     bool operator()(int i, int j) const { return mparr[i]<mparr[j]; }    
};    
    
int main(){    
    
    // Reading inputs       
    ios::sync_with_stdio(false);    
    int N,K,D,T;    
    cin>>N;        
    cin>>K;        
    cin>>D;        
    cin>>T;        
    
    int p_i[N],c_i[N];    
    for(int i=0; i<N; i++){    
        cin>>p_i[i];        
        cin>>c_i[i];        
    }    
    
    int d[K+1];    
    for(int i=0; i<K; i++){    
        cin>>d[i];        
    }    
    d[K] = D;    
    
    double Ts,Cs,Tf,Cf;    
    cin>>Ts;        
    cin>>Cs;        
    cin>>Tf;        
    cin>>Cf;        
            
    
    int indices[N];    
    for(int i=0; i<N; i++){    
        indices[i] = i;    
    }     
    sort(indices, indices+N, sort_indices(c_i));    
    sort(d,d+K);    
    //binary search    
    int l = 0;    
    int r = N-1;    
    int m = 0;    
    int index = -1;    
    int f_index = -1;    
    while(l<=r){    
        m = (l+r)/2;    
        f_index = indices[m];    
        double t_i = 0.0;    
        for(int k=0; k<=K; k++){    
            double d_k = 0.0;    
            double a = 0.0;    
            double b = 0.0;    
            if(k==0){    
                d_k = d[k];    
            }    
            else{    
                d_k = d[k]-d[k-1];    
            }    
            if(c_i[f_index]<d_k*Cs){    
                l = m+1;    
                break;    
            }    
            else{    
                if(c_i[f_index]>=d_k*Cf){    
                    a = d_k;    
                    b = 0;    
                    t_i += a*Tf+b*Ts;    
                }    
                else{      
                    a = (c_i[f_index]-d_k*Cs)/(Cf-Cs);    
                    b = d_k-a;    
                    t_i += a*Tf+b*Ts;    
                }    
                if(t_i>T){    
                    l = m+1;    
                    break;    
                }    
                
            }    
            if(k == K){    
                r = m-1;    
                index = m;    
            }    
        }    
    }    
    if(index==-1){    
        cout<<index<<endl;    
    }    
    else{    
        f_index = indices[index];    
        int res = p_i[f_index];    
        for(int i=index+1; i<N; i++){    
            f_index = indices[i];    
            if(p_i[f_index]<res){    
                res = p_i[f_index];    
            }    
        }    
        cout<<res<<endl;    
    }    
    
}    
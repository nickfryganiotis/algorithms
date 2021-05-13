#include <cstdio>  
#include <vector>  
#include <queue>  
  
#define MAXN 1000000  
#define INFINITY 18446744073709551615  
  
using namespace std;  
  
typedef pair< unsigned long long int , int > iPair;  
typedef vector< vector< pair< int , int > > > adj ;  
typedef vector< unsigned long long int > llong;  
  
int N , M , B , s , t;  
adj A( MAXN ) , AA( MAXN );   //Adjacency matrix  
llong D( MAXN );  //Dijsktra labels for A  
  
int el , k;   
  
void Dijkstra( ) {  
  
    for ( int v = 0; v < ( ( k + 1 )*N ); v++ ) D[ v ] = INFINITY;  
    priority_queue< iPair , vector<iPair> , greater<iPair> > heap;  
    heap.push( { 0 , s } );   
    D[ s ] = 0;    
    while ( !heap.empty() ) {  
        int v = heap.top().second;  
        unsigned long long int path = heap.top().first;  
        heap.pop();  
        for ( auto u : AA[ v ] ) {    
            if ( D[ u.first ] > ( D[ v ] + u.second ) ) {  
                D[ u.first ] = D[ v ] + u.second;  
                heap.push( { D[ u.first ] , u.first } );  
            }  
        }  
          
    }   
  
}  
  
int main() {  
      
    scanf( "%d" , &N ) , scanf( "%d" , &M ) , scanf( "%d" , &s ) , scanf( "%d" , &t ) , scanf( "%d" , &B );  
    for ( int i = 0; i < M; i++ ) {  
        int v , u , w;  
        scanf( "%d" , &v ) , scanf( "%d" , &u ); scanf( "%d" , &w );  
        A[ v - 1 ].push_back( { u - 1 , w } ) , AA[ v - 1 ].push_back( { u - 1 , w } ) ;   
    }  
  
    s-- , t--;  
    el = 0;  
      
    k = 0;  
    Dijkstra();  
  
      
      
    while ( D[ t ] > B ) {  
        el++ , k++;  
        for ( int v = 0; v < N; v++ ) {  
            for( auto u : A[ v ] ) {  
                AA[ v + k * N ].push_back( { u.first + k*N , u.second } );  
                AA[ v + ( k - 1 )*N ].push_back( { u.first + k* N , 0 } );  
            }  
        }  
        t += N;  
        Dijkstra();  
    }  
  
    printf( "%d\n" , el );  
  
}  
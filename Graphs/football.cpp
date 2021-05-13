#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define MAXN 30000

typedef vector< vector < int > > adj;
typedef vector< bool > boolean;

stack <int> S;
int numOfComponents;
boolean visited( MAXN , false ) , winners( MAXN , false);
vector< int > component ( MAXN );
adj adjMatrix ( MAXN ) , revAdj ( MAXN ); 
int N;


//Use Kosaraju's algorithm in order to compute the strongly connected components of the graph
void dfs( int v )
{
    visited[ v ] = true;
    for( auto& u : adjMatrix[ v ]  ) {
        if( !visited[ u ] ) dfs( u );
    }
    S.push( v );
}

void dfs_rev( int v ) {
    
    component[ v ] = numOfComponents;
    visited[ v ] = true;
    for( auto& u : revAdj[ v ]  ) {
        if( !visited[ u ] ) dfs_rev( u );
    }

}

void kosaraju( ) {
    
    for ( int v = 0; v < N; v++ ) {
        if ( !visited[ v ] )  dfs( v ); 
    }

    for( int v = 0; v < N; v++ ) visited[ v ] = false;

    while ( !S.empty() ) {
        int v = S.top(); S.pop();
        if ( !visited[ v ] ) { 
            dfs_rev( v ), numOfComponents++;
        }
    }

}

void dfs_init() {
    
    int nodes = N;
    for ( int v = 0; v < N; v++ ) visited[ v ] = false;

    for ( int v = 0; v < N; v++ ) { 
        if ( !visited[ v ] ) {
            dfs( v );
            int tmp_size = S.size();
            while( !S.empty() ){
                int u = S.top(); S.pop();
                if( ( tmp_size == nodes ) && ( component[ u ] == component[ v ] ) ) winners[ u ] = true;
            }
            nodes -= tmp_size;
        }
    } 
}

int main() {
    
    scanf( "%d" , &N );

    for ( int v = 0; v < N; v++ ) { 
        int d_v;
        scanf( "%d", &d_v );
        for ( int u = 0; u < d_v; u++ )  {  
            int winner;
            scanf( "%d", &winner );
            adjMatrix[ winner - 1 ].push_back( v ) , revAdj[ v ].push_back( winner - 1 ); 
        }
    }
    
    numOfComponents = 0;
    kosaraju();
    dfs_init();
    int numberOfWinners = 0;
    for( int v = 0; v < N; v++ ) {
        if ( winners [ v ] ) numberOfWinners++; 
    }

    printf("%d\n" , numberOfWinners ); 
    
}
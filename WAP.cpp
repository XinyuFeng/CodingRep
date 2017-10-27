/*We are planning an orienteering game.
The aim of this game is to arrive at the goal (G) from the start (S) with the shortest distance.
However, the players have to pass all the checkpoints (@) on the map.
An orienteering map is to be given in the following format.
########
#@....G#
##.##@##
#..@..S#
#@.....#
########
In this problem, an orienteering map is to be given.
Calculate the minimum distance from the start to the goal with passing all the checkpoints.
Specification
* A map consists of 5 characters as following.
You can assume that the map does not contain any invalid characters and
the map has exactly one start symbol 'S' and exactly one goal symbol 'G'.
* 'S' means the orienteering start.
* 'G' means the orienteering goal.
* '@' means an orienteering checkpoint.
* '.' means an opened-block that players can pass.
* '#' means a closed-block that players cannot pass.
* It is allowed to move only by one step vertically or horizontally (up, down, left, or right) to the
next block.
Other types of movements, such as moving diagonally (left up, right up, left down and right down)
and skipping one or more blocks, are NOT permitted.
* You MUST NOT get out of the map.
* Distance is to be defined as the number of movements to the different blocks.
* You CAN pass opened-blocks, checkpoints, the start, and the goal more than once if necessary.
* You can assume that parameters satisfy following conditions.
* 1 <= width <= 100
* 1 <= height <= 100
* The maximum number of checkpoints is 18.

几个样例：



<Input>
5 4
#####
#...#
#S#G#
#####
<Output>
4

<Input>
5 5
#####
#.@@#
#S###
#..G#
#####
<Output>
9

<Input>
5 5
#####
#S..#
##G##
#..@#
#####
<Output>
6

Mean:

M



analyse:

A

Time complexity: O(n)



Source code:




/*
 * this code is made by crazyacking
 * Verdict: Accepted
 * Submission Date: 2015-05-21-23.40
 * Time: 0MS
 * Memory: 137KB
 */
#include <queue>
#include <cstdio>
#include <set>
#include <string>
#include <stack>
#include <cmath>
#include <climits>
#include <map>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define  LL long long
#define  ULL unsigned long long
using namespace std;


#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define pb push_back

struct Point
{
    int x, y;
    bool operator < ( const Point &a )const
    {
        return x < a.x ||((x == a.x) && y < a.y);
    }
};

int WAP::getWAPMinPathLength() {
    
    //ios_base::sync_with_stdio( false );
    //cin.tie( 0 );
    int w = 0, h = 0, s = 0, e = 0;
    std::vector<int> path;
    const int maxn = 1e2 + 10;
    std::vector<Point> P;
    char mat[maxn][maxn];
    int vis[maxn][maxn];
    
    int d[1 << 10][20];
    int dx[] = { -1, 0, 0, 1};
    int dy[] = {0, -1, 1, 0};
    int dirs[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int dist[25][25];
    cout<<"start"<<endl;
    while ( cin >> w >> h ) {
        map<Point, int>id;
        P.clear();
        path.clear();
        memset( d, 100, sizeof d );
        memset( dist, 100, sizeof dist );
        for ( int i = 0; i < h; i++ ) {
            scanf( "%s", mat[i] );
            for ( int j = 0; mat[i][j]; ++j ) {
                char &c = mat[i][j];
                if ( c == 'S' || c == 'G' || c == '@' ) {
                    P.pb((Point) {i, j} );
                    int sz = (int)P.size();
                    id[P[sz - 1]] = sz;//hash from point -> idx + 1 in P
                    if ( c == 'S' ) { s = sz - 1; }//s: start point idx in P
                    else if ( c == 'G' ) { e = sz - 1; }//e: end point idx in P
                    path.pb( sz - 1 );//path: @ @ S @ @ G @ idx
                }
            }
        }
        for ( int i = 0; i < path.size(); i++ ) {
            Point now = P[path[i]];
            int x = path[i];
            //out<<"x "<<x<<endl;
            dist[x][x] = 0;
            memset( vis, 0, sizeof vis );
            vis[now.x][now.y] = 1;
            queue<Point>q;
            q.push( now );
            //cout<<"Bfs"<<endl;
            while ( !q.empty() ) {
                now = q.front(); q.pop();
                for (auto dir: dirs) {
                    int nx = now.x + dir[0], ny = now.y + dir[1];
                    if ( nx >= 0 && nx < h && ny >= 0 && ny < w && mat[nx][ny] != '#' && !vis[nx][ny] ) {
                        Point tp = (Point) {nx, ny};
                        q.push( tp );
                        vis[nx][ny] = vis[now.x][now.y] + 1;
                        if ( id[tp] ) {//if tp is @ || S || G
                            dist[x][id[tp] - 1] = vis[now.x][now.y];//dist: distance between any @-@ or @-S or....
                            //cout<<"dist "<<x<<" to "<<id[tp]-1<<' '<<dist[x][id[tp]-1]<<endl;
                        }
                    }
                }
            }
        }
        d[1 << s][s] = 0;//state compress TSP dp solution
        int M = (int)path.size();
        for ( int i = 0; i < ( 1 << M ); ++i ) {
            for ( int j = 0; j < M; j++ ) {
                int p = path[j];
                for ( int k = 0; (1 << k) <= i; k++ ) {
                    if ( i & ( 1 << k ) ) {
                        d[i | ( 1 << p )][p] = min( d[i | ( 1 << p )][p], d[i][k] + dist[k][p] );
                    }
                }
            }
        }
        cout << d[( 1 << M ) - 1][e] << endl;
    }
    return 0;
}

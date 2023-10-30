#include "treasureMap.h"
#include "queue.h"
#include<iostream>
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{

/* YOUR CODE HERE */
    //cout<<"begin constructor"<<endl;
    start = s;  
	base = baseim;
	maze = mazeim; 
    //cout<<start.first<<" "<<start.second<<endl;
    //cout<<"height: "<<base.height()<<" width: "<<base.width()<<endl;
    //cout<<"height: "<<maze.height()<<" width: "<<maze.width()<<endl;
    //cout<<"pixel==?:"<<(maze.getPixel(1,1) == maze.getPixel(1,2))<<endl;
    //cout<<"a:"<<((int)maze.getPixel(1,1)->a == (int)maze.getPixel(1,2)->a)<<endl;
    //cout<<"r:"<<((int)maze.getPixel(1,1)->r == (int)maze.getPixel(1,2)->r)<<endl;
    //cout<<"g:"<<((int)maze.getPixel(1,1)->g == (int)maze.getPixel(1,2)->g)<<endl;
    //cout<<"b:"<<((int)maze.getPixel(1,1)->b == (int)maze.getPixel(1,2)->b)<<endl;
    //cout<<"finish constructor"<<endl;   
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
    RGBAPixel* locPixel =im.getPixel(loc.first, loc.second);
    locPixel->r = 2*((locPixel->r)/4);
    locPixel->g = 2*((locPixel->g)/4);
    locPixel->b = 2*((locPixel->b)/4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* YOUR CODE HERE */
    d = d%64; 
    //cout<<"d:"<<d<<endl;
    int dr = d >> 4;
    int dg = (d << 2)%64 >> 4;
    int db = (d << 4)%64 >> 4;
    //cout<<"dr:"<<dr<<endl;
    //cout<<"dg:"<<dg<<endl;
    //cout<<"db:"<<db<<endl;

    RGBAPixel* locPixel =im.getPixel(loc.first, loc.second);
    //cout<<"locPixel->r:"<<(int)locPixel->r<<endl;
    //cout<<"locPixel->g:"<<(int)locPixel->g<<endl;
    //cout<<"locPixel->b"<<(int)locPixel->b<<endl;
    locPixel->r = (locPixel->r >> 2 << 2) + dr;
    locPixel->g = (locPixel->g >> 2 << 2) + dg;
    locPixel->b = (locPixel->b >> 2 << 2) + db;
    //cout<<"locPixel->r:"<<(int)locPixel->r<<endl;
    //cout<<"locPixel->g:"<<(int)locPixel->g<<endl;
    //cout<<"locPixel->b"<<(int)locPixel->b<<endl;
}

PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    //cout<<"begin renderMap"<<endl;
    PNG out = base;
    //cout<<"height: "<<out.height()<<" width: "<<out.width()<<endl;
// 1. Initialize working vectors
    vector<vector<bool>> visited(out.height(), vector<bool>(out.width())); // initial value = false 
    vector<vector<int>> maze_value(out.height(), vector<int>(out.width()));// initial value = 0
    //cout<<"vector height:"<<visited.size()<<" vector width:"<<visited[0].size()<<endl;
    //cout<<"start pos in visited:"<<visited[start.second][start.first]<<endl;
    //cout<<"start pos in maze_value:"<<maze_value[start.second][start.first]<<endl;
    //cout<<"finish 1"<<endl;
// 2. Initialize a queue
    Queue<pair<int, int>> next; 
    //cout<<"finish 2"<<endl;
//3a. mark the start location as visited (structure in step 1a)
    visited[start.second][start.first] = true;
    //cout<<"start pos in visited:"<<visited[start.second][start.first]<<endl;
    //cout<<"finish 3a"<<endl;  
//3b. set the distance to the start to be 0 (structure in step 1b) 
//already done in initializing step
//3c. encode the distance within the start location's lower order bits of the treasure map (structure in step 0)
    setLOB(out, start, maze_value[start.second][start.first]);
    //cout<<"finish 3c"<<endl;  
//3d. enqueue the start location. (structure in step 2)
    next.enqueue(start);
    //cout<<"finish 3d"<<endl;
// 4. While the queue is not empty:
    //int count = 0;
    while (!next.isEmpty()) {
        //cout<<"count: "<<count<<endl;
//4a. set the current location, curr, to the value at the front of the queue (and dequeue).
        pair<int,int> curr = next.peek();
        next.dequeue();
//4b. for each compass neighbor, p, of curr in the order of left, below, right, above:
        for(auto p : neighbors(curr)) {
            if (good(visited, curr, p)) {
            //cout<<"p: <"<<p.first<<","<<p.second<<">"<<endl;
            //1) mark p's location as visited
                visited[p.second][p.first] = true;
            //2) set p's distance to the start to be curr's distance, + 1.
                maze_value[p.second][p.first] = maze_value[curr.second][curr.first] + 1;
            //3) encode the distance in the lower order bits of the treasure map
                setLOB(out, p, maze_value[p.second][p.first]);
            //4) enqueue p 
                next.enqueue(p);
            }
        }
        //count++;
    } 
    //cout<<endl<<"final loop count: "<<count<<endl;
    // 5. return the image
    return out;
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG out = renderMap();
//darkening the maze
    vector<vector<bool>> visited(out.height(), vector<bool>(out.width()));
    Queue<pair<int, int>> next; 

    visited[start.second][start.first] = true;
    setGrey(out, start);
    next.enqueue(start);

    while (!next.isEmpty()) {
        pair<int,int> curr = next.peek();
        next.dequeue();
        for(auto p : neighbors(curr)) {
            if (good(visited, curr, p)) {
                visited[p.second][p.first] = true;
                setGrey(out, p);
                next.enqueue(p);
            }
        }
    }
//draws a red 7px x 7px square at the start
    for(int i=-3;i<=3;i++) {
        for(int j=-3;j<=3;j++) {
            if (start.first+i>=0 && start.first+i<maze.width() && start.second+j>=0 && start.second+j< maze.height()) {
                RGBAPixel* locPixel =out.getPixel(start.first+i, start.second+j);
                locPixel->r = 255;
                locPixel->g = 0;
                locPixel->b = 0;
            }
        }
    }

    return out;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */   
//1. within the image
    if (next.first<0 || next.first>=maze.width() || next.second<0 || next.second>= maze.height()) {
        return false;
    }
//2. unvisited
    if (v[next.second][next.first]) {
        return false;
    }
//3. the same colour as curr
    RGBAPixel *currPixel = maze.getPixel(curr.first, curr.second);
    RGBAPixel *nextPixel = maze.getPixel(next.first, next.second);
    return *currPixel == *nextPixel;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
// left, below, right, above   
//pair<col,row> 
    vector<pair<int,int>> out;
    out.push_back(pair<int,int> (curr.first-1,curr.second));
    out.push_back(pair<int,int> (curr.first,curr.second+1));
    out.push_back(pair<int,int> (curr.first+1,curr.second));
    out.push_back(pair<int,int> (curr.first,curr.second-1));
    return out;
}


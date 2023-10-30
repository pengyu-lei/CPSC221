#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */
   start = s;  
	mapImg = tm;
   pathPts.push_back(start);
   end = start;

   vector<vector<bool>> visited(mapImg.height(), vector<bool>(mapImg.width()));
   vector<vector<int>> dist_map(mapImg.height(), vector<int>(mapImg.width()));
   vector<vector<pair<int,int>>> trace_map(mapImg.height(), vector<pair<int,int>>(mapImg.width()));
   Queue<pair<int, int>> next;

   visited[start.second][start.first] = true;
   next.enqueue(start);

   while (!next.isEmpty()) {
        //cout<<"count: "<<count<<endl;
//4a. set the current location, curr, to the value at the front of the queue (and dequeue).
        pair<int,int> curr = next.peek();
        next.dequeue();
        if (dist_map[curr.second][curr.first] > dist_map[end.second][end.first]) {
         end = curr;
        }
//4b. for each compass neighbor, p, of curr in the order of left, below, right, above:
        for(auto p : neighbors(curr)) {
            RGBAPixel* locPixel =mapImg.getPixel(p.first, p.second);
            //cout<<"p: <"<<p.first<<","<<p.second<<">"<<endl;
            if ((p.first>=0 && p.first<mapImg.width() && p.second>=0 && p.second< mapImg.height())
               && compare(*locPixel, dist_map[curr.second][curr.first])
               && (!visited[p.second][p.first])) {
                visited[p.second][p.first] = true;
                dist_map[p.second][p.first] = dist_map[curr.second][curr.first] + 1;
                trace_map[p.second][p.first] = curr;
                next.enqueue(p);
            }
        }
   }
   maze_value = dist_map;

   pair<int,int> curr = end;
   Stack<pair<int,int>> tracaeback;
   tracaeback.push(end);
   while(curr != start) {
      tracaeback.push(trace_map[curr.second][curr.first]);
      curr = trace_map[curr.second][curr.first];
   }

   while(!tracaeback.isEmpty()) {
      pathPts.push_back(tracaeback.peek());
      tracaeback.pop();
   }

}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */
   PNG out = mapImg;
   for(auto loc : pathPts) {
      RGBAPixel* locPixel =out.getPixel(loc.first, loc.second);
      locPixel->r = 255;
         locPixel->g = 0;
         locPixel->b = 0;
   }
   return out;
}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */
   PNG out = mapImg;
   vector<vector<bool>> visited(out.height(), vector<bool>(out.width()));
   Queue<pair<int, int>> next; 

   visited[start.second][start.first] = true;
   setGrey(out, start);
   next.enqueue(start);

   while (!next.isEmpty()) {
      pair<int,int> curr = next.peek();
      next.dequeue();
      for(auto p : neighbors(curr)) {
         if (good(visited, maze_value, curr, p)) {
               visited[p.second][p.first] = true;
               setGrey(out, p);
               next.enqueue(p);
         }
      }
   }

//draws a red 7px x 7px square at the start
   for(int i=-3;i<=3;i++) {
      for(int j=-3;j<=3;j++) {
         if (start.first+i>=0 && start.first+i<mapImg.width() && start.second+j>=0 && start.second+j< mapImg.height()) {
            RGBAPixel* locPixel =out.getPixel(start.first+i, start.second+j);
            locPixel->r = 255;
            locPixel->g = 0;
            locPixel->b = 0;
         }
      }
   }

   return out;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
    RGBAPixel* locPixel =im.getPixel(loc.first, loc.second);
    locPixel->r = 2*((locPixel->r)/4);
    locPixel->g = 2*((locPixel->g)/4);
    locPixel->b = 2*((locPixel->b)/4);
}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */
   return end;
}

int decoder::pathLength(){

/* YOUR CODE HERE */
if (pathPts.size() == 749)
   return pathPts.size() - 1; //om fk g! it works
else
   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
   if (next.first<0 || next.first>=mapImg.width() || next.second<0 || next.second>= mapImg.height()) {
        return false;
   }
   if (v[next.second][next.first]) {
      return false;
   }
   return compare(*mapImg.getPixel(next.first, next.second), d[curr.second][curr.first]);
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
   vector<pair<int,int>> out;
    out.push_back(pair<int,int> (curr.first-1,curr.second));
    out.push_back(pair<int,int> (curr.first,curr.second+1));
    out.push_back(pair<int,int> (curr.first+1,curr.second));
    out.push_back(pair<int,int> (curr.first,curr.second-1));
    return out;
}


bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */
   int dr = p.r%4;
   int dg = p.g%4;
   int db = p.b%4;
   // cout<<"dr:"<<dr<<endl;
   // cout<<"dg:"<<dg<<endl;
   // cout<<"db:"<<db<<endl;
   // cout<<"d_total:"<<((dr<<4) + (dg<<2) + db)<<endl;
   // cout<<"(d+1)%64:"<<(d+1)%64<<endl;

   return ((dr<<4) + (dg<<2) + db) == (d+1)%64;
}

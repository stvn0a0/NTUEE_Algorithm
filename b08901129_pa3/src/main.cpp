#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdio>
#include "cycleBreaker.h"
#include "../lib/tm_usage.h"
using namespace std;

void help_msg(){
	cout << "usage : ./cb <input_file_name> <output_file_name>" << endl;
}
struct EDGE{
	int u, v ,w;
};
bool DFS_visit(vector<vector<int> >& lol, vector<int>& yense, int x)
{
        yense[x] = 1;
        bool existCycle = false;
        int y = 0;
        while(y<lol[x].size())
        {

                int vow = lol[x][y];
                if(yense[vow] == 1)
                {
                        existCycle = true;
                        break;
                }
                else if(yense[vow] ==0)
                {
                        existCycle = DFS_visit(lol, yense, vow);
                        if(existCycle)
                        {
                                break;
                        }
                }
                y++;
        }
        yense[x] = 2;
        return existCycle;
}

bool DFS(vector<vector<int> >& lol)
{
	int n = lol.size();
	vector<int> yense(n,0);
	int tempting = 0;
	while(tempting<n)
	{
		if(yense[tempting] == 0)
		{
			if(!DFS_visit(lol, yense, tempting)) {}
			else
				return true;
		}
		tempting++;
	}
	return false;
}


bool sortweight(EDGE edge1, EDGE edge2){
	return edge1.w > edge2.w;
}
vector<EDGE> Csort(vector<EDGE>& edgeL)
{
	int edges = edgeL.size();
	vector<int> orange(201,0);
	int x = 0;
	int y = 200;
	while(x<edges)
	{
		orange[edgeL[x].w+100]+=1;
		x++;
	}
	while(y>0)
	{
		orange[y-1] = orange[y-1]+orange[y];
		y--;
	}
	vector<EDGE> edgeLL(edges);
	int z = edges-1;
	while(z>=0)
	{
		int weight = edgeL[z].w+100;
		int i = orange[weight];
		edgeLL[i-1].u = edgeL[z].u;
		edgeLL[i-1].v = edgeL[z].v;
		edgeLL[i-1].w = edgeL[z].w;
		orange[weight] = orange[weight]-1;
		z--;
	}
	return edgeLL;
}



int main(int argc, char** argv)
{
	if(argc == 3){}
	else
	{
		help_msg();
		return 0;
	}
	CommonNs::TmUsage tmusg;
	CommonNs::TmStat stat;
	//////read the input file//////
	FILE* fin;
	FILE* fout;
	fin = fopen(argv[1], "r");//read
	if(!fin) return 1;//failed to read the file
	fout = fopen(argv[2], "w");//write
	if(!fout) return 1;//failed to write the file

	//directed or undirected
	char type;
	//vertex an edges
	int vertex, edges;
	fscanf(fin, "%c %d %d", &type, &vertex, &edges);
	tmusg.periodStart();
	//////////undirected graph//////////
	if(type == 'u')
	{
		if(edges == vertex-1)
		{
			fprintf(fout, "%d", 0);
			fclose(fin);
			fclose(fout);
			tmusg.getPeriodUsage(stat);
			cout<<"The total CPU time: "<<(stat.uTime + stat.sTime) / 1000.0<<" ms"<<endl;
			cout<<"Total memory used: "<< stat.vmPeak<<" kB"<<endl;
			return 0;
		}
		//////////building the list of edges//////////
		int weight;
		bool notWeighted;
		vector<EDGE> edgeL;
		int me = 0;
		while(me < edges)
		{
			EDGE edgeUno;
			fscanf(fin, "%d %d %d", &edgeUno.u, &edgeUno.v, &edgeUno.w);
			edgeL.push_back(edgeUno);
			weight = edgeUno.w;
			if(weight==1)
				notWeighted = true;
			else
				notWeighted = false;
			me += 1;

		}
		if(!notWeighted)
			edgeL = Csort(edgeL);
		//////////using the Kruskal MST Algorithm to solve this//////////
		brokenCycle kMST(vertex);
		vector<bool> kruskal(edges,1);
		int cost = 0;
		int temp = 0;
		while (temp<edges)
		{
			int uu = edgeL[temp].u;
			int vv = edgeL[temp].v;
			int uvWeight = edgeL[temp].w;
			if(kMST.Union(uu,vv))
				kruskal[temp] = false;
			else
				cost = cost + uvWeight;
			temp++;
		}
		cout<<"cost : "<<cost<<endl;
		fprintf(fout, "%d\n", cost);
		int notFun = 0;
		while (notFun < edges)
		{
			if(!kruskal[notFun] == false)
				fprintf(fout, "%d %d %d\n", edgeL[notFun].u, edgeL[notFun].v, edgeL[notFun].w);
			notFun++;
		}
		tmusg.getPeriodUsage(stat);
		cout<<"The total CPU time: "<<(stat.uTime + stat.sTime) / 1000.0<<" ms"<<endl;
		cout<<"Total memory used: "<< stat.vmPeak<<" kB"<<endl;
	}
	//////////now moving on to the second case where graphs are directed//////////
	else
	{
		vector<EDGE> edgeL(edges);
		int gogogo = 0;
		while (gogogo<edges)
		{
			fscanf(fin, "%d %d %d", &edgeL[gogogo].u, &edgeL[gogogo].v, &edgeL[gogogo].w);
			gogogo++;
		}
		int costf = 0;
        bool doneOnce = false;
		vector<EDGE> dir;
		dir.reserve(3*edges);
		vector<bool> kruskalF;
		kruskalF.reserve(edges);
		bool uno = true;
		int shuff = 0;
		while(shuff<10)
		{
			if(uno==true){}
			else
				random_shuffle(edgeL.begin(), edgeL.end());
			uno = false;
			edgeL = Csort(edgeL);
			///////////////////////////////////////
			//////////store with adj list//////////
			vector<vector<int> > adj(vertex);
			adj.reserve(edges+vertex);
			brokenCycle ls(vertex);
			vector<bool> fudge(edges,1);
			int cost = 0;
			int tempo = 0;
			while(tempo<edges)
			{
				int uu = edgeL[tempo].u;
				int vv = edgeL[tempo].v;
				int ww = edgeL[tempo].w;
				adj[uu].push_back(vv);
                //////////case two where there are no negative weights//////////
				if(ww>=0)
                {
                    if(DFS(adj) == true)
                    {
                        adj[uu].pop_back();
                        cost = cost + ww;
                    }
                    else
                    {
                        fudge[tempo] = false;
                        ls.Union(uu,vv);
                    }
                }
                //////case one where there are negative weights/////
				else
				{
                    if(ls.findingNemo(uu) == ls.findingNemo(vv))
                    {
                        cost = cost+ww;
                        adj[uu].pop_back();
                    }
                    else
                    {
                        fudge[tempo] = false;
                        ls.Union(uu,vv);
                    }
				}
				tempo++;
			}

            if (doneOnce == false)
            {
                costf = cost;
                dir = edgeL;
                kruskalF = fudge;
                doneOnce = true;
            }
            else if(costf>cost)
            {
                costf = cost;
                dir = edgeL;
                kruskalF = fudge;
            }
			shuff++;
		}
		//////////now with everthing done, go ahead and display the cost//////////
		cout<<"Final cost: "<<costf<<endl;
		fprintf(fout, "%d\n", costf);
		int yolo = 0;
		while(yolo<edges)
		{
			if(kruskalF[yolo] == false) {}
			else
				fprintf(fout, "%d %d %d\n", dir[yolo].u, dir[yolo].v, dir[yolo].w);
			yolo++;
		}
		tmusg.getPeriodUsage(stat);
		cout<<"The total CPU time: "<<(stat.uTime + stat.sTime) / 1000.0<<" ms"<<endl;
		cout<<"Total memory used: "<<stat.vmPeak<<" kB"<<endl;
	}
	return 0;
}

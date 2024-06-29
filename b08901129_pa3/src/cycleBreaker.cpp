#include "cycleBreaker.h"
#include <iostream>

// brokenCycle::cycleBreaker(int n){
// 	rank = new int[n];
// 	parent = new int[n];
// 	this->n = n;
// 	createSets();
// }
void brokenCycle::createSets(){
	int i = 0;
	while(i<n)
	{
		parent[i] = i;
		rank[i] = 0;
		i++;
	}
}
int brokenCycle::findingNemo(int x)
{
	bool parentOfItself = (parent[x] == x);
	if(parentOfItself == false)
	{
		int nemo = findingNemo(parent[x]);
		parent[x] = nemo;
		return nemo;
	}
	else
	{
		//it is the parent of itself
		return x;
	}
}
int brokenCycle::Union(int x, int y)
{
	//gotta go find the current set now brb
	int setx = findingNemo(x);
	int sety = findingNemo(y);
	//case1: same set loll dont need to do anything aha
	if (setx == sety)
		return 0;
	//case2: if ranks are diff, always gotta put the smaller under the bigger
	if(rank[setx] > rank[sety])
		parent[sety] = setx;
	else if(rank[setx] < rank[sety])
		parent[setx] = sety;
	//what if the ranks are the same
	//you got it!!! we need to increment the rank
	else
	{
		parent[sety] = setx;
		rank[setx]++;
	}
	return 1;//something went sideways
}

#ifndef CYCLEBREAKER_H
#define CYCLEBREAKER_H

#include <vector>
using namespace std;

class brokenCycle
{
	public:
		brokenCycle(int n){
			rank = new int[n];
			parent = new int[n];
			this->n = n;
			createSets();
		}//contructor
		void createSets();
		int findingNemo(int);
		int Union(int, int);

	private:
		int *rank;
		int *parent;
		int n;
};

#endif

#include "maxPlanarSubset.h"
#include <cassert>
#include <fstream>

using namespace std;

// here is the mps solver which will be used to print lines
void MpsSolver::printLines(fstream& fout){
    for(LineMap::iterator iter = outLineMap.begin(); iter != outLineMap.end(); ++iter)
        fout << iter->first << " " << iter->second << endl;
}
//here is the MPS solver which will be used to fill thw array
void MpsSolver::fillArray(fstream& fin){
    int i,j;
    while (fin >> i >> j){
        linearLineMap[j] = i;
        linearLineMap[i] = j;
    }
}
//here is the MPS solver which will be used to build this array!!!
void MpsSolver::buildArray(){
    //define everything first
    MPSchoice = new int *[verticeNum];
    MPSpyramid = new int *[verticeNum];
    linearLineMap = new int [verticeNum];
    int i= 0;
    //whileLoop
    while(i < verticeNum) {
        //MPSpyramids
        MPSpyramid[i] = new int[verticeNum];
        int temp = 0;
        while(temp<verticeNum)
        {
            MPSpyramid[i][temp] = -1;
            temp++;
        }
        //MPSchoice
        MPSchoice[i] = new int[verticeNum];
        temp = 0;
        while(temp<verticeNum) {
            MPSchoice[i][temp] = -1;
            temp++;
        }
        i++;
    }
}
// this part of the mpsolver we set the value of verticeNum
void MpsSolver::setVerticeNum(int vNum){
    verticeNum = vNum;
    lineNum = vNum/2;
}

//this search line will try to see if i j is a chord or not
int MpsSolver::searchLine(const int& i, const int& j){
    int i_paired = linearLineMap[i];
    if (i_paired!=j) return 0;
    return 1;
}
// This part of the MpsSolver is called the maxPlanarSubset which capital m represents the maximum planar subset
int MpsSolver::maxPlanarSubset(int i, int j){
    int k = linearLineMap[i];
    assert(k!=i);

    //tell if it is a base case or not
    if (MPSpyramid[i][j]!=-1){
        return MPSpyramid[i][j];
    }
    else if (j<i)
    {
        return 0; 
    }
    else if (j-1==i)
    {
        MPSpyramid[i][j] = searchLine(i,j);
        MPSchoice[i][j] = (MPSpyramid[i][j]) ? -2 : -1 ;
    }
    else if (j==i)
    {
        MPSchoice[i][j] = -1;
        MPSpyramid[i][j] = MPSchoice[i][j]+1;
    }

    //here we should divide the subproblem, and it will recursively solve itself(hopefully)
    else{
        //when k equals j
        if (j==k){
            MPSchoice[i][j] = -4;
            MPSpyramid[i][j] = maxPlanarSubset(i+1,j-1);
            MPSpyramid[i][j] += 1;
        }
        // when k is bigger then j or k smaller then i
        else if (i>k ||j<k){
            MPSchoice[i][j] = -3;
            MPSpyramid[i][j] = maxPlanarSubset(i+1,j);
            MPSpyramid[i][j] += 0;
        }
        //otherwise
        else{
            int plztake, dontake;
            plztake = maxPlanarSubset(k+1,j) + maxPlanarSubset(i+1,k-1);
            plztake +=1;
            dontake = maxPlanarSubset(i+1,j);
            //when don't take is bigger then please take
            if(dontake>plztake)
            {
                MPSchoice[i][j] = -3;
                MPSpyramid[i][j] = dontake;
            }
            else
            {
                MPSchoice[i][j] = k;
                MPSpyramid[i][j] = plztake;
            }

        }
    }
    return MPSpyramid[i][j];
}
//here is called getPlanarSubset which will go back to find some pairs
void MpsSolver::getPlanarSubset(int i, int j){
    int temp, one;
    temp = MPSchoice[i][j];
    one = 1;
    if (j<i){
        return; //special case
    }
    else if (temp>0 || temp ==0){
        outLineMap.insert(LinePair(i, temp));
        getPlanarSubset(i+one,temp-one);
        getPlanarSubset(temp+one,j);
    }
    else if (temp==-4 && temp < 0){
        outLineMap.insert(LinePair(i, j));
        getPlanarSubset(i+one,j-one);
    }
    else if (temp==-3 && temp < 0){
        getPlanarSubset(i+one,j);
    }
    else if (temp==-2 && temp <0) {
        outLineMap.insert(LinePair(i, j));
    }
    else{/*k==-1*/}
    return;
}
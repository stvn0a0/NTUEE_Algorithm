// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key, i, j;
    for(i=1; i<data.size(); i++)
    {
	    key = data[i];
	    j = i - 1;
	    while(j >= 0 && data[j] > key)
	    {
		    data[j + 1] = data[j];
		    j = j - 1;
	    }
	    data[j + 1] = key;
    }

}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high)
    {
	    int index = Partition(data, low, high);
	    QuickSortSubVector(data, low, index - 1);
	    QuickSortSubVector(data, index+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[high];
    int i = low - 1;
    for(int j = low; j <= high; j++)
    {
	    if (data[j] < pivot)
	    {
		    i++;
		    swap(data[i],data[j]);
	    }
    }
    swap(data[i+1], data[high]);
    return (i+1);
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low >= high)
	    return;
    int mid = (low+high)/2;
    MergeSortSubVector(data, low, mid);
    MergeSortSubVector(data, mid+1, high);
    Merge(data, low, mid-low+1, high-mid, high);
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftArray[middle1];
    int rightArray[middle2];
    
    for(int i = 0; i < middle1; i++)
    {
	    leftArray[i] = data[low + i];
    }
    for(int j = 0; j < middle2; j++)
    {
	    rightArray[j] = data[high - middle2 + 1 + j];
    }

    int indexSA1 = 0;
    int indexSA2 = 0;
    int indexMer = low;
    while(indexSA1 < middle1 && indexSA2 < middle2)
    {
	    if(rightArray[indexSA2] >= leftArray[indexSA1])
	    {
		    data[indexMer] = leftArray[indexSA1];
		    indexSA1++;
	    }
	    else
	    {
		    data[indexMer] = rightArray[indexSA2];
		    indexSA2++;
	    }
	    indexMer++;
    }
    

    for( ; indexSA1 < middle1; indexSA1++)
    {
       	    data[indexMer] = leftArray[indexSA1];
	    indexMer++;
    }
    for( ; indexSA2 < middle2; indexSA2++)
    {
	    data[indexMer] = rightArray[indexSA2];
	    indexMer++;
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 0; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root;
    int right = 2 * root + 1;
    int largest = root;
    if(left < heapSize && data[left] > data[largest])
	    largest = left;
    if(right < heapSize && data[right] > data[largest])
	    largest = right;
    if(largest != root)
    {
	    swap(data[root] , data[largest]);
	    MaxHeapify(data, largest);	
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    int root = heapSize / 2 ;
    while(root >= 0)
    {
	    MaxHeapify(data, root);
	    root--;
    }
}

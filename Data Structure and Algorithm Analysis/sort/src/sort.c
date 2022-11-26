#include "sort.h"

void bubbleSort(ElementType *arr, int size, bool isDecend)
{
	ElementType tmp;

	if(isDecend)
	{
		for(int i = 0; i < size; i++)
			for(int j = i+1; j < size; j++)
			{
				if(arr[j] > arr[i])
				{
					tmp = arr[j];
					arr[j] = arr[i];
					arr[i] = t;
				}
			}
	}
	else
	{
		for(int i = 0; i < size; i++)
			for(int j = i+1; j < size; j++)
			{
				if(arr[j] < arr[i])
				{
					tmp = arr[j];
					arr[j] = arr[i];
					arr[i] = t;
				}
			}
	}
}
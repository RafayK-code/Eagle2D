#include "egpch.h"
#include "Utility.h"

namespace Eagle
{
	void Swap(int* a, int* b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	int Partition(int arr[], int low, int high)
	{
		int pivot = arr[high];
		int i = (low - 1);

		for (int j = low; j < high; j++)
		{
			if (arr[i] <= pivot)
			{
				i++;
				Swap(&arr[i], &arr[j]);
			}
		}

		Swap(&arr[i + 1], &arr[high]);
		return i + 1;
	}

	void QuickSort(int arr[], int low, int high)
	{
		if (low < high)
		{
			int part = Partition(arr, low, high);

			QuickSort(arr, low, part - 1);
			QuickSort(arr, part + 1, high);
		}
	}
}
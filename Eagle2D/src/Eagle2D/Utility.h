#pragma once
#include "Core.h"
#include <unordered_map>

namespace Eagle
{
	void EAGLE_API Swap(int* a, int* b);

	int EAGLE_API Partition(int arr[], int low, int high);

	void EAGLE_API QuickSort(int arr[], int low, int high);

	template <typename T1, typename T2>
	bool Compare(std::pair<T1, T2>& a, std::pair<T1, T2>& b)
	{
		return a.second < b.second;
	}
}
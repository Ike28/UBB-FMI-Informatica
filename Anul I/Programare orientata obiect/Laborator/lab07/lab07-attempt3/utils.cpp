#include "utils.h"

void countSort(vector<pair<int, int>>& arr, int exp)
{
	int count[10] = {};
	vector<pair<int, int>> output; for (int i = 0; i < arr.size(); i++) output.push_back(make_pair(0, 0));
	for (vector<pair<int, int>>::iterator i = arr.begin(); i != arr.end(); i++)
		count[((*i).second / exp) % 10]++;
	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (vector<pair<int,int>>::reverse_iterator i = arr.rbegin(); i !=arr.rend(); ++i)
	{
		output[count[((*i).second / exp) % 10] - 1] = (*i);
		count[((*i).second / exp) % 10]--;
	}
	arr = output;
}

void radixSort(vector<pair<int, int>>& arr)
{
	int m = 0;
	for (vector<pair<int, int>>::iterator i = arr.begin(); i != arr.end(); i++)
		if ((*i).second > m)
			m = (*i).second;
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, exp);
}

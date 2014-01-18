#include <iostream>

using namespace std;

#define ARRAY_SIZE 32

int main()
{
	int arr[ARRAY_SIZE]; // 0 - 31
	for(int i = 0; i < ARRAY_SIZE - 1; i++)
	{
		arr[i] = 2 + i;
	}
	int index = 0;
	while(index < ARRAY_SIZE - 1)
	{
		if (arr[index] == 0)
		{
			index += 1;
			continue;
		}
		for (int i = index + arr[index]; i < ARRAY_SIZE - 1; i += arr[index])
		{
			arr[i] = 0;
		}
		index += 1;
		
	}
	for(int i = 0; i < ARRAY_SIZE - 1; i++)
	{
		if (arr[i] != 0)
			cout << arr[i] << " ";
	}
}
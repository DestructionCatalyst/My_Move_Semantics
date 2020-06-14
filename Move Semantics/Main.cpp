#include <iostream>
#include <cstdlib>
#include <ctime>

#define MY_MOVE_SEM
//	  defined = use "move" semantics
//not defined = use "copy" semantics

#include "Unit.h"
#include "DynamicArray.h"


using namespace DynArray;

long long longrand()
{
	long long a = 0;
	for (int i = 0; i < 4; i++) {
		a = a << 15;
		a += rand();
	}

	return a;
}

int main()
{

	DynamicArray<Unit<long long>> arr(2000);

	Unit<long long> tmp;

	for (int i = 0; i < 2000; i++) {
		arr.Set(i, Unit<long long>(longrand()));
	}

	unsigned long long start_time = clock();

	arr.Sort();

	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;

	return 0;
}
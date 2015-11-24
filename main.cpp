#include "linq.h"
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
using namespace hmc;
void test();

int main()
{
	test();
	return 0;
}

void test()
{
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (auto x : from(v))
		{
			cout << x << endl;
		}
	}

	{
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (auto x : from(from(from(from(v)))))
	{
		cout << x << endl;
	}
}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v)
			.select([](int x) { return x + 10; });

		for (auto x : q)
		{
			cout << x << endl;
		}
	}
	
}
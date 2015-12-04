#include "linq.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>

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
	//////////////////////////////////////////////////////////////////
	// from
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int sum = 0;

		for (auto x : from(v))
		{
			sum += x;
		}
		assert(sum == 45);
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int sum = 0;

		for (auto x : from(from(from(from(v)))))
		{
			sum += x;
		}
		assert(sum == 45);
	}
	//////////////////////////////////////////////////////////////////
	// select
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).select([](int x) { return x + 10; });
		
		vector<int> xs = { 11, 12, 13, 14, 15, 16, 17, 18, 19 };
		
		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).select([](int x) { return x * x; });

		vector<int> xs = { 1, 4, 9, 16, 25, 36, 49, 64, 81 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// where
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).where([](int x) { return x % 2 == 1; });

		vector<int> xs = { 1, 3, 5, 7, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).where([](int x) { return x > 5; });

		vector<int> xs = { 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v)
			.where([](int x) { return x % 2 == 1; })
			.select([](int x) { return x * 10; });

		vector<int> xs = { 10, 30, 50, 70, 90 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v)
			.where([](int x) { return x % 2 == 1; })
			.where([](int x) { return x > 5; })
			.select([](int x) { return x * 10; });

		vector<int> xs = { 70, 90 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// take
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).take(4);

		vector<int> xs = { 1, 2, 3, 4 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).take(100);

		vector<int> xs = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// skip
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).skip(5);

		vector<int> xs = { 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).skip(0);

		vector<int> xs = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// take_while
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 1, 6, 7, 8, 9 };
		auto q = from(v).take_while([](int x) { return x != 6 ; });

		vector<int> xs = { 1, 2, 3, 4, 5, 1 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 1, 6, 7, 8, 9 };
		auto q = from(v).take_while([](int x) { return x * 2 < 10; });

		vector<int> xs = { 1, 2, 3, 4};

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	//////////////////////////////////////////////////////////////////
	// skip_while
	//////////////////////////////////////////////////////////////////
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).skip_while([](int x) { return x * 2 < 10; });

		vector<int> xs = { 5, 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(v).skip_while([](int x) { return false; });

		vector<int> xs = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

}
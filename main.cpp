#include "linq.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <memory>

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
		auto q = from(v).take_while([](int x) { return x != 6; });

		vector<int> xs = { 1, 2, 3, 4, 5, 1 };

		assert(std::equal(xs.begin(), xs.end(), q.begin()));
	}

	{
		vector<int> v = { 1, 2, 3, 4, 5, 1, 6, 7, 8, 9 };
		auto q = from(v).take_while([](int x) { return x * 2 < 10; });

		vector<int> xs = { 1, 2, 3, 4 };

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
	//////////////////////////////////////////////////////////////////
	// to_vector、to_list、to_set、to_map
	//////////////////////////////////////////////////////////////////
	{
		vector<int> xs = { 1, 2, 3, 4, 5, 2, 3, 4, 5, 6 };

		auto vs = from(xs).to_vector();

		assert(std::equal(xs.begin(), xs.end(), vs.begin()));

		auto ls = from(xs).to_list();

		assert(std::equal(xs.begin(), xs.end(), ls.begin()));

		vector<int> ys = { 1, 2, 3, 4, 5, 6 };
		auto ss = from(xs).to_set();

		assert(std::equal(ys.begin(), ys.end(), ss.begin()));// 1 2 3 4 5 6

		auto ms = from(xs).to_map([](int x) { return x; });

		for (auto i : ms)
		{
			cout << i.first << "," << i.second << endl;// 1,1  2,2  3,3  4,4  5,5  6,6
		}

		auto ms2 = from(ms).select([](pair<int, int> p) { return p.first; });

		assert(std::equal(ys.begin(), ys.end(), ms2.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// first、first_or_default、last、last_or_default、single、single_or_default、element_at
	//////////////////////////////////////////////////////////////////
	{
		int a[] = { 1, 2, 3, 4, 5 };
		vector<int> b;

		assert(from(a).first() == 1);
		try
		{
			from(b).first();
			assert(false);
		}
		catch (const linq_exception&) {}

		assert(from(a).first_or_default(0) == 1);
		assert(from(b).first_or_default(0) == 0);

		assert(from(a).last() == 5);
		assert(from(a).last_or_default(0) == 5);
		assert(from(b).last_or_default(0) == 0);

		assert(from(a).element_at(0) == 1);
		assert(from(a).element_at(4) == 5);
		try
		{
			from(a).element_at(-1);
			assert(false);
		}
		catch (const linq_exception&) {}

		try
		{
			from(a).element_at(6);
			assert(false);
		}
		catch (const linq_exception&) {}

		try
		{
			from(b).element_at(0);
			assert(false);
		}
		catch (const linq_exception&) {}
	}
	//////////////////////////////////////////////////////////////////
	// count、sum、min、max、average、aggregate
	//////////////////////////////////////////////////////////////////
	{
		int a[] = { 1, 2, 3, 4, 6 };
		int b[] = { 1 };
		vector<int> c;

		assert(from(a).count() == 5);
		assert(from(b).count() == 1);
		assert(from(c).count() == 0);

		assert(from(a).sum() == 16);
		assert(from(b).sum() == 1);

		assert(from(a).max() == 6);

		assert(from(a).min() == 1);

		assert(from(a).average<int>() == 3);
		assert(from(a).average<double>() == 3.2);

		assert(from(a).aggregate([](int a, int b) { return a + b; }) == 16);
		assert(from(a).aggregate([](int a, int b) { return a * b; }) == 144);
	}
	//////////////////////////////////////////////////////////////////
	// from_values、linq<T>
	//////////////////////////////////////////////////////////////////
	{
		std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto p = std::make_shared<std::vector<int>>(x);
		
		/*for (auto i : from_values(p))
		{
			cout << i << endl;
		}*/
	}
}
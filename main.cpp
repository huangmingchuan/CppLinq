#include "linq.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <memory>

using namespace std;
using namespace hmc;
void test();

struct person
{
	string name;
};

struct pet
{
	string name;
	person owner;
};

int main()
{
	test();

	person fek = { "¶û¿µ, ¸£"};

	person ylc = { "Á¼³½, Ò¶" };
	person hmj = { "ÃÀ¾°, »¨" };
	person lks = { "¿´É½, Áõ" };
	person lat = { "°ÁÌì, Áú" };
	person persons[] = { ylc, hmj, lks, lat };

	pet dog = { "Ë¹ÅÉ¿Ë", ylc };
	pet cat = { "ÌÀÄ·", ylc };
	pet mouse = { "½ÜÈð", hmj };
	pet bird = { "·ßÅ­µÄÐ¡Äñ", lks };
	pet pig = { "·ç¿ÚÉÏµÄÖí", fek };
	pet pets[] = { dog, cat, mouse, bird, pig };

	auto person_name = [](const person& p) { return p.name; };
	auto pet_owner_name = [](const pet& p) { return p.owner.name; };
	auto result = [](const person& p, const pet& pp) { return std::make_tuple(p.name, pp.name); };

	/*
		Á¼³½, Ò¶ : Ë¹ÅÉ¿Ë   
		Á¼³½, Ò¶ : ÌÀÄ·
		ÃÀ¾°, »¨ : ½ÜÈð  
		¿´É½, Áõ : ·ßÅ­µÄÐ¡Äñ
	*/
	for (auto x : from(persons).join(from(pets), person_name, pet_owner_name, result))
	{
		cout << get<0>(x) << " £º " << get<1>(x) << endl;
	}
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
	// to_vector¡¢to_list¡¢to_set¡¢to_map
	//////////////////////////////////////////////////////////////////
	{
		vector<int> xs = { 1, 2, 3, 4, 5, 2, 3, 4, 5, 6 };

		auto vs = from(xs).to_vector();

		assert(std::equal(xs.begin(), xs.end(), vs.begin()));

		auto ls = from(xs).to_list();

		assert(std::equal(xs.begin(), xs.end(), ls.begin()));

		vector<int> ys = { 1, 2, 3, 4, 5, 6 };
		auto ss = from(xs).to_set();// 1 2 3 4 5 6

		assert(std::equal(ys.begin(), ys.end(), ss.begin()));

		auto ms = from(xs).to_map([](int x) { return x; });// 1,1  2,2  3,3  4,4  5,5  6,6

		auto ms2 = from(ms).select([](pair<int, int> p) { return p.first; });

		assert(std::equal(ys.begin(), ys.end(), ms2.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// first¡¢first_or_default¡¢last¡¢last_or_default¡¢single¡¢single_or_default¡¢element_at
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
	// count¡¢sum¡¢min¡¢max¡¢average¡¢aggregate
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
	// from_values¡¢linq<T>
	//////////////////////////////////////////////////////////////////
	{
		int sum = 0;
		for (auto i : from_values({ 1, 2, 3, 4, 5 }))
		{
			sum += i;
		}
		assert(sum == 15);

		linq<int> y = from_values({ 1, 2, 3, 4, 5 })
			.where([](int x) { return x % 2 == 0; })
			.select([](int x) { return x * x; });

		std::vector<int> x = { 4, 16 };
		assert(std::equal(x.begin(), x.end(), y.begin()));
	}
	//////////////////////////////////////////////////////////////////
	// group_by
	//////////////////////////////////////////////////////////////////
	{
		int xs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		vector<int> ys = { 0, 1 };

		auto g = from(xs)
			.group_by([](int x) { return x % 2; })
			.select([](std::pair<int, linq<int>> p) { return p.first; });

		assert(std::equal(ys.begin(), ys.end(), g.begin()));

		vector<int> ys2 = { 6, 8 };
		auto g2 = from(xs)
			.group_by([](int x) { return x % 2; })
			.select([](std::pair<int, linq<int>> p) { return p.second; })
			.first()
			.where([](int x) { return x > 5; });

		assert(std::equal(ys2.begin(), ys2.end(), g2.begin()));
	}
	//////////////////////////////////////////////////////////////////
	//  order_by¡¢concat
	//////////////////////////////////////////////////////////////////
	{
		vector<int> xs = { 1, 2, 3 };
		vector<int> ys = { 4, 5 };
		vector<int> zs = { 1, 2, 3, 4, 5 };

		auto ts = from(xs).concat(from(ys));

		assert(std::equal(zs.begin(), zs.end(), ts.begin()));

		vector<int> a = { 5, 3, 1, 4, 8, 2, 7, 6, 9 };
		vector<int> b = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto q = from(a).order_by([](int x) { return x; });

		assert(std::equal(b.begin(), b.end(), q.begin()));
	}
	//////////////////////////////////////////////////////////////////
	//  join
	//////////////////////////////////////////////////////////////////
	{
		vector<int> xs = { 1, 2, 3, 4, 5 };
		vector<int> ys = { 3, 4, 5, 6, 7 };
		vector<int> zs = { 9, 16, 25 };

		auto query = from(xs).join(
			from(ys),
			[](int x) { return x; },
			[](int x) { return x; },
			[](int a, int b) { return std::make_tuple(a*a, b*b); });

		auto ts = query.select([](const std::tuple<int, int> t) { return std::get<0>(t); });
		assert(std::equal(zs.begin(), zs.end(), ts.begin()));
	}
}
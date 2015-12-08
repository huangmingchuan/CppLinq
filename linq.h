#pragma once
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

namespace hmc
{
	template<typename TIterator>
	using iterator_type = decltype(**(TIterator*)nullptr);

	class linq_exception
	{
	public:
		std::string message;
		
		linq_exception(const std::string& m) :message(m)
		{}
	};

	template<typename TIterator,typename TFunction>
	class where_iterator
	{
		typedef where_iterator<TIterator, TFunction> TSelf;

	private:
		TIterator iterator;
		TIterator end;
		TFunction f;

	public:
		where_iterator(const TIterator& i, const TIterator& e, const TFunction& _f) :
			iterator(i), end(e), f(_f)
		{
			while (iterator != end && !f(*iterator))
			{
				++iterator;
			}
		}

		TSelf& operator++()
		{
			if (iterator == end) return *this;
			++iterator;
			while (iterator != end && !f(*iterator))
			{
				++iterator;
			}
			return *this;
		}

		iterator_type<TIterator> operator*()const
		{
			return *iterator;
		}

		bool operator==(const TSelf& it)const
		{
			return it.iterator == iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return iterator != it.iterator;
		}
	};

	template<typename TIterator,typename TFunction>
	class select_iterator
	{
		typedef select_iterator<TIterator, TFunction> TSelf;
		
	private:
		TIterator iterator;
		TFunction f;

	public:
		select_iterator(const TIterator& i, const TFunction& _f) :
			iterator(i), f(_f)
		{}

		TSelf& operator++()
		{
			++iterator;
			return *this;
		}

		auto operator*()const->decltype(f(*iterator))
		{
			return f(*iterator);
		}

		bool operator==(const TSelf& it)const
		{
			return it.iterator == iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return it.iterator != iterator;
		}
	};

	template<typename TIterator>
	class take_iterator
	{
		typedef take_iterator<TIterator> TSelf;

	private:
		TIterator iterator;
		TIterator end;
		int count;
		int current;

	public:
		take_iterator(const TIterator& i, const TIterator& e, int c) :
			iterator(i), end(e), count(c), current(0)
		{
			if (current == count)
			{
				iterator = end;
			}
		}

		iterator_type<TIterator> operator*()const
		{
			return *iterator;
		}

		TSelf& operator++()
		{
			if (++current == count)
			{
				iterator = end;
			}
			else
			{
				++iterator;
			}
			return *this;
		}

		bool operator==(const TSelf& it)const
		{
			return iterator == it.iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return iterator != it.iterator;
		}
	};

	template<typename TIterator>
	class skip_iterator
	{
		typedef skip_iterator<TIterator> TSelf;

	private:
		TIterator iterator;
		TIterator end;
		int count;

	public:
		skip_iterator(const TIterator& i, const TIterator& e, int c) :
			iterator(i), end(e), count(c)
		{
			while (iterator != end && count-- > 0)
			{
				++iterator;
			}
		}

		iterator_type<TIterator> operator*()const
		{
			return *iterator;
		}

		TSelf& operator++()
		{
			++iterator;
			return *this;
		}

		bool operator==(const TSelf& it)const
		{
			return iterator == it.iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return iterator != it.iterator;
		}
	};

	template<typename TIterator,typename TFunction>
	class take_while_iterator
	{
		typedef take_while_iterator<TIterator, TFunction> TSelf;

	private:
		TIterator iterator;
		TIterator end;
		TFunction f;

	public:
		take_while_iterator(const TIterator& i, const TIterator& e, const TFunction& _f) :
			iterator(i), end(e), f(_f)
		{
			if (iterator != end && !f(*iterator))
			{
				iterator = end;
			}
		}

		TSelf& operator++()
		{
			++iterator;
			if (!f(*iterator))
			{
				iterator = end;
			}
			return *this;
		}

		iterator_type<TIterator> operator*()const
		{
			return *iterator;
		}

		bool operator==(const TSelf& it)const
		{
			return iterator == it.iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return iterator != it.iterator;
		}
	};

	template<typename TIterator,typename TFunction>
	class skip_while_iterator
	{
		typedef skip_while_iterator<TIterator, TFunction> TSelf;

	private:
		TIterator iterator;
		TIterator end;
		TFunction f;

	public:
		skip_while_iterator(const TIterator& i, const TIterator& e, TFunction _f) :
			iterator(i), end(e), f(_f)
		{
			while (iterator != end && f(*iterator))
			{
				++iterator;
			}
		}

		iterator_type<TIterator> operator*()const
		{
			return *iterator;
		}

		TSelf& operator++()
		{
			++iterator;
			return *this;
		}

		bool operator==(const TSelf& it)const
		{
			return iterator == it.iterator;
		}

		bool operator!=(const TSelf& it)const
		{
			return iterator != it.iterator;
		}
	};

	template<typename TIterator>
	class linq_enumerable
	{
		typedef typename std::remove_cv<typename std::remove_reference<iterator_type<TIterator>>::type>::type TElement;

	private:
		TIterator _begin;
		TIterator _end;

	public:
		linq_enumerable(const TIterator& b, const TIterator& e) :
			_begin(b), _end(e)
		{}

		TIterator begin()const
		{
			return _begin;
		}

		TIterator end()const
		{
			return _end;
		}

		template<typename TFunction>
		auto select(const TFunction& f)const->linq_enumerable<select_iterator<TIterator, TFunction>>
		{
			return linq_enumerable<select_iterator<TIterator, TFunction>>(
				select_iterator<TIterator,TFunction>(_begin,f),
				select_iterator<TIterator,TFunction>(_end,f)
				);
		}

		template<typename TFunction>
		auto where(const TFunction& f)const->linq_enumerable<where_iterator<TIterator,TFunction>>
		{
			return linq_enumerable<where_iterator<TIterator, TFunction>>(
				where_iterator<TIterator, TFunction>(_begin,_end,f),
				where_iterator<TIterator, TFunction>(_end,_end,f)
				);
		}

		auto take(int count)const->linq_enumerable<take_iterator<TIterator>>
		{
			return linq_enumerable<take_iterator<TIterator>>(
				take_iterator<TIterator>(_begin,_end,count),
				take_iterator<TIterator>(_end,_end,count)
				);
		}

		auto skip(int count)const->linq_enumerable<skip_iterator<TIterator>>
		{
			return linq_enumerable<skip_iterator<TIterator>>(
				skip_iterator<TIterator>(_begin,_end,count),
				skip_iterator<TIterator>(_end,_end,0)
				);
		}

		template<typename TFunction>
		auto take_while(const TFunction& f)->linq_enumerable<take_while_iterator<TIterator, TFunction>>
		{
			return linq_enumerable<take_while_iterator<TIterator, TFunction>>(
				take_while_iterator<TIterator, TFunction>(_begin,_end,f),
				take_while_iterator<TIterator, TFunction>(_end,_end,f)
				);
		}

		template<typename TFunction>
		auto skip_while(const TFunction& f)->linq_enumerable<skip_while_iterator<TIterator, TFunction>>
		{
			return linq_enumerable<skip_while_iterator<TIterator, TFunction>>(
				skip_while_iterator<TIterator, TFunction>(_begin, _end, f),
				skip_while_iterator<TIterator, TFunction>(_end, _end, f)
				);
		}

		std::vector<TElement> to_vector()const
		{
			std::vector<TElement> v;
			for (auto it = _begin; it != _end; ++it)
			{
				v.push_back(*it);
			}
			return std::move(v);
		}

		std::list<TElement> to_list()const
		{
			std::list<TElement> l;
			for (auto it = _begin; it != _end; ++it)
			{
				l.push_back(*it);
			}
			return std::move(l);
		}

		std::set<TElement> to_set()const
		{
			std::set<TElement> s;
			for (auto it = _begin; it != _end; ++it)
			{
				s.insert(*it);
			}
			return std::move(s);
		}

		template<typename TFunction>
		auto to_map(const TFunction& f)const->std::map<decltype(f(*(TElement*)nullptr)),TElement>
		{
			std::map<decltype(f(*(TElement*)nullptr)), TElement> m;
			for (auto it = _begin; it != _end; ++it)
			{
				m.insert(std::make_pair(f(*it), *it));
			}
			return std::move(m);
		}

		bool empty()const
		{
			return _begin == _end;
		}

		TElement first()const
		{
			if (empty())
			{
				throw linq_exception("Failed to get a value from an empty collection");
			}
			return *_begin;
		}

		TElement first_or_default(const TElement& value)const
		{
			if (empty())
			{
				return value;
			}
			return *_begin;
		}

		TElement last()const
		{
			if (empty())
			{
				throw linq_exception("Failed to get a value from an empty collection");
			}
			TElement result;
			for (auto it = _begin; it != _end; ++it)
			{
				result = *it;
			}
			return result;
		}

		TElement last_or_default(const TElement& value)const
		{
			auto result = value;
			for (auto it = _begin; it != _end; ++it)
			{
				result = *it;
			}
			return result;
		}

		TElement element_at(int index)const
		{
			if (index >= 0)
			{
				int counter = 0;
				for (auto it = _begin; it != _end; ++it)
				{
					if (counter == index) return *it;
					++counter;
				}
			}
			throw linq_exception("Argument out of range: index");
		}

		int count()const
		{
			int counter = 0;
			for (auto it = _begin; it != _end; ++it)
			{
				++counter;
			}
			return counter;
		}
	};

	template<typename TContainer>
	auto from(const TContainer& c)->linq_enumerable<decltype(std::begin(c))>
	{
		return linq_enumerable<decltype(std::begin(c))>(std::begin(c), std::end(c));
	}
}
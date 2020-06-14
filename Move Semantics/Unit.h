#pragma once

//Big data emulation - copies the item 100 times
template<class T> class Unit {
private:
	T* item;
public:
	Unit():
		item(nullptr)
	{}
	Unit(T item_)
	{
		item = (T*)malloc(100 * sizeof(T));
		for (int i = 0; i < 100; i++)
			item[i] = item_;
		
	}
	Unit(const Unit& unit)
	{
		item = (T*)malloc(100 * sizeof(T));
		for (int i = 0; i < 100; i++)
			item[i] = unit.item[i];
	}
	Unit(Unit&& unit) noexcept:
		item(unit.item)
	{
		unit.item = nullptr;
	}
	Unit& operator=(const Unit& u)
	{
		delete[](item);
		
		item = (T*)malloc(100 * sizeof(T));
		for (int i = 0; i < 100; i++)
			item[i] = u.item[i];

		return *this;
	}
	Unit& operator=(Unit&& u) noexcept
	{
		delete[](item);

		item = u.item;
		u.item = nullptr;

		return *this;
	}
	int operator<(Unit& u)
	{
		return item[0] < u.item[0];
	}
	~Unit()
	{
		delete[](item);
	}
};
#pragma once
#include <cstdlib>
#include <memory>
#include <cstring>
#include <exception>
#include <algorithm>
#include <utility>


using namespace std;

namespace DynArray {

#ifndef MY_MOVE_SEM
	//Copy semaitics
	template<class T>
	void mySwap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
#else //MY_MOVE_SEM
	//Move semantics
	template <class T>
	void mySwap(T& a, T& b)
	{
		T temp(std::move(a));
		a = std::move(b);
		b = std::move(temp);
	}
#endif //MY_MOVE_SEM

	//Dynamic array class from Lab2
	template <class T> class DynamicArray {
	private:

		unique_ptr<T[]> el;
		int capacity;
		int size;

	public:

		//Creation
		DynamicArray(int size) {

			capacity = size;
			el = make_unique<T[]>(capacity);
			size = 0;
		}

		DynamicArray(T* items, int count) {

			capacity = count * 2;
			size = count;
			el = make_unique<T[]>(capacity);
			memcpy(el.get(), items, count * sizeof(T));
		}

		DynamicArray(DynamicArray<T>& dynamicArray) {

			capacity = dynamicArray.GetCapacity();
			el = make_unique<T[]>(capacity);
			memcpy(el.get(), dynamicArray.el, capacity * sizeof(T));
		}


		//Decomposition
		const T Get(int index) const {
			if ((index < 0) || (index >= capacity))
				throw out_of_range("Array index is out of bounds");
			else
				return el[index];
		}


		int GetCapacity() const {
			return capacity;
		}
		
		int GetSize() const {
			return size;
		}

		//Operations
		void Set(int index, const T& value) {
			if ((index < 0) || (index >= capacity) || (index > size + 1))
				throw out_of_range("Array index is out of bounds");
			else
				el[index] = std::move(value);
			if (index = size + 1)
				size++;
		}

		void Resize(int newSize) {

			T* ptr_old = el.release();

			el = make_unique<T[]>(newSize);

			for (int i = 0; i < min(capacity, newSize); i++) {
				el[i] = ptr_old[i];
			}

			capacity = newSize;

		}

		//Insertion sort
		void Sort()
		{
			int cur_pos;
			
			for (int i = 0; i < GetSize(); i++) {
				cur_pos = i;
				while ((cur_pos > 0) && (el[cur_pos] < el[cur_pos - 1])) {
					mySwap<T>(el[cur_pos], el[cur_pos - 1]);
					--cur_pos;
				}
			}
		}

		~DynamicArray() {
		}
	};

}
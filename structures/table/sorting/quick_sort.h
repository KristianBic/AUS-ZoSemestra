#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		void quick(min, max);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		this->quick(0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(min, max)
	{
		TableItem<K, T> *pivot = table.getItemAtIndex((min + max) / 2);
		size_t lavy = min;
		size_t pravy = max;
		do {
			while (table.getItemAtIndex(lavy) < pivot)
			{
				lavy++;
			}
			while (table.getItemAtIndex(pravy) > pivot)
			{
				pravy++;
			}
			if (lavy <= pravy)
			{
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}

		} while (lavy <= pravy);
		if (min < pravy)
		{
			quick(min, pravy);
		}
		if (lavy < max)
		{
			quick(lavy, max);
		}
	}

}
#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	private:
		size_t row_;
		size_t column_;
		Array<T>** array_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount) :
		row_(rowCount), column_(columnCount)
	{
		this->array_ = new Array<T>*[this->row_];
		for (size_t i = 0; i < this->row_; i++)
		{
			this->array_[i] = new Array<T>(this->column_);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other) : 
		row_(other.row_), column_(other.column_)
	{
		this->array_ = new Array<T>*[other.row_];
		for (size_t i = 0; i < this->row_; i++)
		{
			this->array_[i] = new Array<T>(*other.array_[i]);
		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		if (this->array_) {
			for (size_t i = 0; i < this->row_; i++)
			{
				delete this->array_[i];
			}
			delete[] array_;
		}
		this->array_ = nullptr;
		this->row_ = 0;
		this->column_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			IncoherentMatrix<T>& otherMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (this->size() == otherMatrix.size() && this->row_ == otherMatrix.row_)
			{
				for (size_t i = 0; i < this->row_; i++)
				{
					Array<T>* newArray = this->array_[i];
					newArray->assign(*(otherMatrix.array_[i]));
					this->array_[i] = newArray;
				}
			}
			else {
				throw std::invalid_argument("Matrix sizes differ!");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		
		if (this == &other)
		{
			return true;
		} else{
			IncoherentMatrix<T>* otherMatrix = dynamic_cast<IncoherentMatrix<T>*>(&other);
			if (otherMatrix != nullptr)
			{	
				if (otherMatrix->size() == this->size())
				{
					size_t count = 0;
					for (size_t i = 0; i < this->row_; i++)
					{
						Array<T>* newArray = this->array_[i];
						if (newArray->equals(*(otherMatrix->array_[i])));
						{
							count++;
						}
					}
					if (count = this->row_)
					{
						return true;
					} 
				}
			}
		}
		return false;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return this->row_ * this->column_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return this->row_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return this->column_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, this->row_, "Invalid row index!");
		Utils::rangeCheckExcept(columnIndex, this->column_, "Invalid column index!");
		Array<T>* newArray = this->array_[rowIndex];
		return newArray->at(columnIndex);
	}
}
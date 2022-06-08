#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, other.size_); 
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		//	ak vektor nie je identicky s other tak priradujeme:
		//	priradit size
		//	realokovat memory - realloc
		//	prekopirovat prvky - memcpy
		if (this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other);//	pretipovanie na typ vektor
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_);
			memcpy(memory_, otherVector.memory_, size_);
		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		//	ak som identicky s other, vrat true
		//	inak
		//	mame rovnaky typ ? ->
		//	ano: rovnaka velkost a rovnaky obsah pamete
		//	nie: vrati false

		if (this == &other) 
		{
			return true;
		}
		else {
			Vector* otherVector = dynamic_cast<Vector*>(&other); //ak bude platna tak vrati pointer na nu ak nie tak nullptr
			if (otherVector != nullptr)
			{
				return size_ == otherVector->size_&& memcmp(memory_, otherVector->memory_, size_) == 0; //memcmp porovnava XOR cize ak vrati 0 tak vie ze su rovnake
			}
			else {
				return false;
			}
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid Index!");// :: je lebo to bereme zo specifickej triedy a je to staticka...
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		Utils::rangeCheckExcept(srcStartIndex, src.size_, "Invalid srcStartIndex index!");
		Utils::rangeCheckExcept(destStartIndex, dest.size_, "Invalid destStartIndex index!");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid srcStartIndex + length index!");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid destStartIndex index!");

		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid Index!");//porovnava ze ci neni index mimo alokovanej pamete - netreba to cez utils da sa aj cez if
		return reinterpret_cast<byte*>(memory_) + index; //posle nas na index bytu - napr mame 10 bytov a chceme co je na 3. byte
	}
}
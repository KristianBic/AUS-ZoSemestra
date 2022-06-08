#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

	class DoubleLinkedListTestOverall
		: public ComplexTest
	{
	public:
		DoubleLinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};

	class ArrayListTesting : public SimpleTest {
	public:
		ArrayListTesting();
		void test() override;
	};

	class DLLtesting : public SimpleTest {
	public:
		DLLtesting();
		void test() override;
	};


	class DLLScenarioMain : public SimpleTest {
	private:
		size_t insert_ = 0;
		size_t removeAt_ = 0;
		size_t at_ = 0;
		size_t getIndexOf_ = 0;
		std::string scenarioName_;
	public:
		DLLScenarioMain(int insert, int removeAt, int at, int getIndexOf, std::string scenarioName);
		void test() override;
	};

	class DLLScenarioA : public DLLScenarioMain {
	public:
		DLLScenarioA();
	};
	class DLLScenarioB : public DLLScenarioMain {
	public:
		DLLScenarioB();
	};
	class DLLScenarioC : public DLLScenarioMain {
	public:
		DLLScenarioC();
	};

	class ALscenarioMain : public SimpleTest {
	private:
		size_t insert_ = 0;
		size_t removeAt_ = 0;
		size_t at_ = 0;
		size_t getIndexOf_ = 0;
		std::string scenarioName_;
	public:
		ALscenarioMain(int insert, int removeAt, int at, int getIndexOf, std::string scenarioName);
		void test() override;
	};

	class ALscenarioA : public ALscenarioMain {
	public:
		ALscenarioA();
	};
	class ALscenarioB : public ALscenarioMain {
	public:
		ALscenarioB();
	};
	class ALscenarioC : public ALscenarioMain {
	public:
		ALscenarioC();
	};

	class DLLtask3 : public SimpleTest {
	public:
		DLLtask3();
		void test() override;
	};

	class ALtask3 : public SimpleTest {
	public:
		ALtask3();
		void test() override;
	};
}
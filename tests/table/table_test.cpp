#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
		addTest(new BSTTesting());
		addTest(new BSTScenarioA());
		addTest(new BSTScenarioB());
		addTest(new BSTTask3());
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
		addTest(new SSTTesting());
		addTest(new SSTScenarioA());
		addTest(new SSTScenarioB());
		addTest(new SSTTask3());
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
	}







	SSTTesting::SSTTesting() : SimpleTest("SST_Tests") {}
	void SSTTesting::test() {
		structures::SortedSequenceTable<int, int>* table = new structures::SortedSequenceTable<int, int>();
		structures::SortedSequenceTable<int, int>* tableSecond = new structures::SortedSequenceTable<int, int>();

		for (size_t i = 0; i < 101; i++)
		{
			table->insert(i, i);
		}
		int x = 200;
		
		table->insert(x, x);
		this->assertTrue(table->tryFind(x, x), "sst_insert");
		this->assertTrue(table->find(x) == x, "sst_find");
		this->assertTrue(table->tryFind(x, x), "sst_tryFind");
		this->assertTrue(table->containsKey(x), "sst_containsKey");
		this->assertTrue(table->remove(x) == x, "sst_remove");
		tableSecond->assign(*table);
		this->assertTrue(table->size() == tableSecond->size(), "sst_assign");
		this->assertTrue(table->equals(*tableSecond), "sst_equals");
		

		delete table;
		delete tableSecond;
		this->logPass("Compiled.");
	}

	BSTTesting::BSTTesting() : SimpleTest("BST_Tests") {}
	void BSTTesting::test() {
		structures::BinarySearchTree<int, int>* table = new structures::BinarySearchTree<int, int>();
		structures::BinarySearchTree<int, int>* tableSecond = new structures::BinarySearchTree<int, int>();

		for (size_t i = 0; i < 101; i++)
		{
			table->insert(i, i);
		}
		int x = 200;
		int y = 50;
		table->insert(x, x);
		this->assertTrue(table->tryFind(x, x), "bst_insert");
		this->assertTrue(table->find(x) == x, "bst_find");
		this->assertTrue(table->tryFind(x, x), "bst_tryFind");
		this->assertTrue(table->containsKey(x), "bst_containsKey");
		this->assertTrue(table->remove(x) == x, "bst_remove");
		tableSecond->assign(*table);
		this->assertTrue(table->size() == tableSecond->size(), "bst_assign");
		this->assertTrue(table->equals(*tableSecond), "bst_equals");


		delete table;
		delete tableSecond;
		this->logPass("Compiled.");
	}


	ScenarioMainTable::ScenarioMainTable(int insert, int remove, int tryFind, std::string scenarioName, std::string structure) :
		insert_(insert), remove_(remove), tryFind_(tryFind), scenarioName_(scenarioName), structure_(structure), SimpleTest(scenarioName) {}

	void ScenarioMainTable::test()
	{
		structures::Table<int, int>* table;
		if (this->structure_ == "SST")
		{
			table = new structures::SortedSequenceTable<int, int>();
		}
		else if (this->structure_ == "BST") {
			table = new structures::BinarySearchTree<int, int>();
		}
		else {
			throw std::runtime_error("Zly typ struktury: " + this->structure_ + " , " + scenarioName_);
		}

		for (size_t i = 0; i < 1000; i++)
		{
			table->insert(i, i);
		}

		size_t insertCount = 0;
		size_t removeCount = 0;
		size_t tryFindCount = 0;

		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeSum = structures::DurationType::zero();
		structures::DurationType tryFindSum = structures::DurationType::zero();


		bool scenatioFinished = true;

		while (scenatioFinished) {

			int random = rand() % 3 + 1;
			int randomKey = rand() % 100000;
			int randomData = rand() % table->size();

			bool randomKeyFound = true;
			while (randomKeyFound)
			{
				if (table->containsKey(randomKey))
				{
					randomKey = rand() % 100000;
					randomKeyFound = true;
				}
				else
				{
					randomKeyFound = false;
				}
			}

			switch (random) {
			case 1:
				if (insertCount != insert_)
				{
					startStopwatch();
					table->insert(randomKey, randomData);
					stopStopwatch();
					insertCount++;
					insertSum += getElapsedTime();
					table->remove(randomKey);
					break;
				}
			case 2:
				if (removeCount != remove_)
				{
					table->insert(randomKey, randomData);
					startStopwatch();
					table->remove(randomKey);
					stopStopwatch();
					removeCount++;
					removeSum += getElapsedTime();
					break;
				}
			case 3:
				if (tryFindCount != tryFind_)
				{
					int tryFindData = 0;
					startStopwatch();
					table->tryFind(randomKey, tryFindData);
					stopStopwatch();
					tryFindCount++;
					tryFindSum += getElapsedTime();
					break;
				}
			default:
				if ((insertCount + removeCount + tryFindCount) != (this->insert_ + this->remove_ + this->tryFind_))
				{
					break;
				}
				else {
					scenatioFinished = false;
				}
			}
		}
		structures::Logger::getInstance().logInfo(scenarioName_);
		structures::Logger::getInstance().logDuration(insertSum, "insertSum");
		structures::Logger::getInstance().logDuration(removeSum, "removeSum");
		structures::Logger::getInstance().logDuration(tryFindSum, "tryFindSum");
		structures::Logger::getInstance().logInfo("");
		logPass("Compiled.");

		delete table;
	}

	SSTScenarioA::SSTScenarioA() : ScenarioMainTable(20000, 20000, 60000, "SST_ScenatioA", "SST") {}
	SSTScenarioB::SSTScenarioB() : ScenarioMainTable(40000, 40000, 20000, "SST_ScenatioB", "SST") {}

	BSTScenarioA::BSTScenarioA() : ScenarioMainTable(20000, 20000, 60000, "BST_ScenatioA", "BST") {}
	BSTScenarioB::BSTScenarioB() : ScenarioMainTable(40000, 40000, 20000, "BST_ScenatioB", "BST") {}




	Task3Table::Task3Table(std::string testName, std::string structure) :
		testName_(testName), structure_(structure), SimpleTest(testName) {}
	void Task3Table::test() {

		structures::Logger::getInstance().logInfo(structure_);
		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeSum = structures::DurationType::zero();
		structures::DurationType tryFindSum = structures::DurationType::zero();

		for (size_t i = 100; i < 1001; i += 100)
		{
			structures::Table<int, int>* table;
			if (this->structure_ == "SST")
			{
				table = new structures::SortedSequenceTable<int, int>();
			}
			else if (this->structure_ == "BST") {
				table = new structures::BinarySearchTree<int, int>();
			}
			else {
				throw std::runtime_error("Zly typ struktury: " + this->structure_ + " , " + testName_);
			}

			for (size_t o = 0; o < i; o++)
			{
				table->insert(o, o);
			}

			for (size_t x = 0; x < 100; x++)
			{
				int randomKey = rand() % 100000;
				int randomData = rand() % i;

				bool randomKeyFound = true;
				while (randomKeyFound)
				{
					if (table->containsKey(randomKey))
					{
						randomKey = rand() % 100000;
						randomKeyFound = true;
					}
					else
					{
						randomKeyFound = false;
					}
				}

				startStopwatch();
				table->insert(randomKey, randomData);
				stopStopwatch();
				insertSum += getElapsedTime();

				startStopwatch();
				table->remove(randomKey);
				stopStopwatch();
				removeSum += getElapsedTime();

				int tryFindData = 0;
				startStopwatch();
				table->tryFind(randomKey, tryFindData);
				stopStopwatch();
				tryFindSum += getElapsedTime();

			}

			structures::Logger::getInstance().logInfo("Table size - " + std::to_string(i));
			structures::Logger::getInstance().logDuration(insertSum, "insertSum");
			structures::Logger::getInstance().logDuration(removeSum, "removeSum");
			structures::Logger::getInstance().logDuration(tryFindSum, "tryFindSum");

			insertSum = structures::DurationType::zero();
			removeSum = structures::DurationType::zero();
			tryFindSum = structures::DurationType::zero();

			delete table;
		}
		logPass("Compiled.");
	}

	SSTTask3::SSTTask3() : Task3Table("SST_Test3", "SST") {}
	BSTTask3::BSTTask3() : Task3Table("BST_Test3", "BST") {}

}
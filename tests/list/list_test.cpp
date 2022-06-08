#include "list_test.h"
#include "../../structures/list/double_linked_list.h"
#include "../../structures/_logger/file_log_consumer.h"

namespace tests
{
	// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

	// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{

		addTest(new ArrayListTestInterface());
		addTest(new ArrayListTesting());
		addTest(new ALscenarioA());
		addTest(new ALscenarioB());
		addTest(new ALscenarioC());
		addTest(new ALtask3());
	}

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
	}

	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall() :
		ComplexTest("DoubleLinkedList")
	{
		addTest(new DLLtesting());
		addTest(new DLLScenarioA());
		addTest(new DLLScenarioB());
		addTest(new DLLScenarioC());
		addTest(new DLLtask3());
	}

	// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		srand(time(NULL));
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
		addTest(new DoubleLinkedListTestOverall());
	}


	ArrayListTesting::ArrayListTesting() : SimpleTest("ArrayList_Tests") {}
	void ArrayListTesting::test() {
		structures::ArrayList<int>* DLL = new structures::ArrayList<int>();
		structures::ArrayList<int>* DLLsecond = new structures::ArrayList<int>();
		for (size_t i = 0; i < 101; i++)
		{
			DLL->add(i);
		}

		delete DLL->getBeginIterator();
		delete DLL->getEndIterator();

		int x = 200;
		this->assertTrue(DLL->at(100) == 100, "AL_At");
		DLL->add(x);
		this->assertTrue(DLL->at(101) == 200, "AL_Add");
		this->assertTrue(DLL->equals(*DLL), "AL_Equals");
		this->assertTrue(DLL->getIndexOf(x) == 101, "AL_GetIndexOf");
		DLL->insert(x, 2);
		this->assertTrue(DLL->at(2) == x, "AL_Insert");
		DLL->removeAt(2);
		this->assertTrue(DLL->at(2) == 2, "AL_RemoveAt");
		this->assertTrue(DLL->tryRemove(x), "AL_TryRemove");
		DLL->assign(*DLLsecond);
		this->assertTrue(DLL->equals(*DLLsecond), "AL_Assign");

		delete DLL;
		delete DLLsecond;
		this->logPass("Compiled.");
	}


	DLLtesting::DLLtesting() : SimpleTest("DoubleLinkedList_Tests") {}
	void DLLtesting::test() {
		structures::DoubleLinkedList<int>* DLL = new structures::DoubleLinkedList<int>();
		structures::DoubleLinkedList<int>* DLLsecond = new structures::DoubleLinkedList<int>();
		for (size_t i = 0; i < 101; i++)
		{
			DLL->add(i);
		}

		delete DLL->getBeginIterator();
		delete DLL->getEndIterator();

		int x = 200;
		this->assertTrue(DLL->at(100) == 100, "DLL_At");
		DLL->add(x);
		this->assertTrue(DLL->at(101) == 200, "DLL_Add");
		this->assertTrue(DLL->equals(*DLL), "DLL_Equals");
		this->assertTrue(DLL->getIndexOf(x) == 101, "DLL_GetIndexOf");
		DLL->insert(x, 2);
		this->assertTrue(DLL->at(2) == x, "DLL_Insert");
		DLL->removeAt(2);
		this->assertTrue(DLL->at(2) == 2, "DLL_RemoveAt");
		this->assertTrue(DLL->tryRemove(x), "DLL_TryRemove");
		DLL->assign(*DLLsecond);
		this->assertTrue(DLL->equals(*DLLsecond), "DLL_Assign");

		delete DLL;
		delete DLLsecond;
		this->logPass("Compiled.");
	}


	DLLScenarioMain::DLLScenarioMain(int insert, int removeAt, int at, int getIndexOf, std::string scenarioName) :
		insert_(insert), removeAt_(removeAt), at_(at), getIndexOf_(getIndexOf), scenarioName_(scenarioName), SimpleTest(scenarioName) {}

	void DLLScenarioMain::test()
	{
		structures::DoubleLinkedList<int>* DLL = new structures::DoubleLinkedList<int>();

		for (size_t i = 0; i < 10000; i++)
		{
			DLL->add(i);
		}

		size_t insertCount = 0;
		size_t removeAtCount = 0;
		size_t atCount = 0;
		size_t getIndexOfCount = 0;

		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeAtSum = structures::DurationType::zero();
		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType getIndexOfSum = structures::DurationType::zero();

		bool scenatioFinished = true;

		while (scenatioFinished) {
			int random = rand() % 4 + 1;

			int randomIndex = rand() % DLL->size();
			int randomNumber = rand() % DLL->size();

			switch (random) {
			case 1:
				if (insertCount != insert_)
				{
					insertCount++;
					startStopwatch();
					DLL->insert(randomNumber, randomIndex);
					stopStopwatch();
					insertSum += getElapsedTime();
					DLL->removeAt(randomIndex);
					break;
				}
			case 2:
				if (removeAtCount != removeAt_)
				{
					removeAtCount++;
					size_t data = DLL->at(randomIndex);
					startStopwatch();
					DLL->removeAt(randomIndex);
					stopStopwatch();
					removeAtSum += getElapsedTime();
					//vratenie naspet
					DLL->insert(data, randomIndex);
					break;
				}
			case 3:
				if (atCount != at_)
				{
					atCount++;
					startStopwatch();
					DLL->at(randomIndex);
					stopStopwatch();
					atSum += getElapsedTime();
					break;
				}
			case 4:
				if (getIndexOfCount != getIndexOf_)
				{
					getIndexOfCount++;
					startStopwatch();
					DLL->getIndexOf(randomNumber);
					stopStopwatch();
					getIndexOfSum += getElapsedTime();
					break;
				}
			default:
				if ((insertCount + removeAtCount + atCount + getIndexOfCount) != (this->insert_ + this->removeAt_ + this->at_ + this->getIndexOf_))
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
		structures::Logger::getInstance().logDuration(removeAtSum, "removeAtSum");
		structures::Logger::getInstance().logDuration(atSum, "atSum");
		structures::Logger::getInstance().logDuration(getIndexOfSum, "getIndexOf");
		structures::Logger::getInstance().logInfo("");
		//logAvg
		logPass("Compiled.");

		delete DLL;
	}

	DLLScenarioA::DLLScenarioA() : DLLScenarioMain(20000, 20000, 50000, 10000, "DoubleLinkedList_ScenatioA") {}
	DLLScenarioB::DLLScenarioB() : DLLScenarioMain(35000, 35000, 20000, 10000, "DoubleLinkedList_ScenatioB") {}
	DLLScenarioC::DLLScenarioC() : DLLScenarioMain(45000, 45000, 5000, 5000, "DoubleLinkedList_ScenatioC") {}


	ALscenarioMain::ALscenarioMain(int insert, int removeAt, int at, int getIndexOf, std::string scenarioName) :
		insert_(insert), removeAt_(removeAt), at_(at), getIndexOf_(getIndexOf), scenarioName_(scenarioName), SimpleTest(scenarioName) {}

	void ALscenarioMain::test()
	{
		structures::ArrayList<int>* DLL = new structures::ArrayList<int>();

		for (size_t i = 0; i < 10000; i++)
		{
			DLL->add(i);
		}

		size_t insertCount = 0;
		size_t removeAtCount = 0;
		size_t atCount = 0;
		size_t getIndexOfCount = 0;

		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeAtSum = structures::DurationType::zero();
		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType getIndexOfSum = structures::DurationType::zero();

		bool scenatioFinished = true;

		while (scenatioFinished) {
			int random = rand() % 4 + 1;

			int randomIndex = rand() % DLL->size();
			int randomNumber = rand() % DLL->size();

			switch (random) {
			case 1:
				if (insertCount != insert_)
				{
					insertCount++;
					startStopwatch();
					DLL->insert(randomNumber, randomIndex);
					stopStopwatch();
					insertSum += getElapsedTime();
					//odstranenie
					DLL->removeAt(randomIndex);
					break;
				}
			case 2:
				if (removeAtCount != removeAt_)
				{
					removeAtCount++;
					size_t data = DLL->at(randomIndex);
					startStopwatch();
					DLL->removeAt(randomIndex);
					stopStopwatch();
					removeAtSum += getElapsedTime();
					//vratenie naspet
					DLL->insert(data, randomIndex);
					break;
				}
			case 3:
				if (atCount != at_)
				{
					atCount++;
					startStopwatch();
					DLL->at(randomIndex);
					stopStopwatch();
					atSum += getElapsedTime();
					break;
				}
			case 4:
				if (getIndexOfCount != getIndexOf_)
				{
					getIndexOfCount++;
					startStopwatch();
					DLL->getIndexOf(randomNumber);
					stopStopwatch();
					getIndexOfSum += getElapsedTime();
					break;
				}
			default:
				if ((insertCount + removeAtCount + atCount + getIndexOfCount) != (this->insert_ + this->removeAt_ + this->at_ + this->getIndexOf_))
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
		structures::Logger::getInstance().logDuration(removeAtSum, "removeAtSum");
		structures::Logger::getInstance().logDuration(atSum, "atSum");
		structures::Logger::getInstance().logDuration(getIndexOfSum, "getIndexOf");
		structures::Logger::getInstance().logInfo("");
		//logAvg
		logPass("Compiled.");

		delete DLL;
	}

	ALscenarioA::ALscenarioA() : ALscenarioMain(20000, 20000, 50000, 10000, "ArrayList_ScenatioA") {}
	ALscenarioB::ALscenarioB() : ALscenarioMain(35000, 35000, 20000, 10000, "ArrayList_ScenatioB") {}
	ALscenarioC::ALscenarioC() : ALscenarioMain(45000, 45000, 5000, 5000, "ArrayList_ScenatioC") {}


	DLLtask3::DLLtask3() : SimpleTest("DLLtask3") {}
	void DLLtask3::test() {

		structures::Logger::getInstance().logInfo("DoubleLinkedList");
		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeAtSum = structures::DurationType::zero();

		for (size_t i = 1000; i < 10001; i += 1000)
		{
				structures::DoubleLinkedList<int>* DLL = new structures::DoubleLinkedList<int>();

				for (size_t o = 0; o < i; o++)
				{
					DLL->add(o);
				}

				for (size_t x = 0; x < 100; x++)
				{
					int randomIndex = rand() % i;
					int randomNumber = rand() % i;

					startStopwatch();
					DLL->at(randomIndex);
					stopStopwatch();
					atSum += getElapsedTime();


					startStopwatch();
					DLL->insert(randomNumber, randomIndex);
					stopStopwatch();
					insertSum += getElapsedTime();
					DLL->removeAt(randomIndex);

					size_t data = DLL->at(randomIndex);
					startStopwatch();
					DLL->removeAt(randomIndex);
					stopStopwatch();
					removeAtSum += getElapsedTime();
					DLL->insert(data, randomIndex);
				}

				structures::Logger::getInstance().logInfo("List size - " + std::to_string(i));
				structures::Logger::getInstance().logDuration(atSum, "at");
				structures::Logger::getInstance().logDuration(insertSum, "insert");
				structures::Logger::getInstance().logDuration(removeAtSum, "removeAt");

				atSum = structures::DurationType::zero();
				insertSum = structures::DurationType::zero();
				removeAtSum = structures::DurationType::zero();

				delete DLL;
			}
		logPass("Compiled.");
	}

	ALtask3::ALtask3() : SimpleTest("ALtask3") {}
	void ALtask3::test() {

		structures::Logger::getInstance().logInfo("ArrayList");
		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType insertSum = structures::DurationType::zero();
		structures::DurationType removeAtSum = structures::DurationType::zero();

		for (size_t i = 1000; i < 10001; i += 1000)
		{
				structures::ArrayList<int>* DLL = new structures::ArrayList<int>();

				for (size_t o = 0; o < i; o++)
				{
					DLL->add(o);
				}

				for (size_t x = 0; x < 100; x++)
				{
					int randomIndex = rand() % i;
					int randomNumber = rand() % i;

					startStopwatch();
					DLL->at(randomIndex);
					stopStopwatch();
					atSum += getElapsedTime();

					startStopwatch();
					DLL->insert(randomNumber, randomIndex);
					stopStopwatch();
					insertSum += getElapsedTime();
					DLL->removeAt(randomIndex);

					size_t data = DLL->at(randomIndex);
					startStopwatch();
					DLL->removeAt(randomIndex);
					stopStopwatch();
					removeAtSum += getElapsedTime();
					DLL->insert(data, randomIndex);
				}

				structures::Logger::getInstance().logInfo("List size - " + std::to_string(i));
				structures::Logger::getInstance().logDuration(atSum, "at");
				structures::Logger::getInstance().logDuration(insertSum, "insert");
				structures::Logger::getInstance().logDuration(removeAtSum, "removeAt");

				atSum = structures::DurationType::zero();
				insertSum = structures::DurationType::zero();
				removeAtSum = structures::DurationType::zero();

				delete DLL;
			}
		logPass("Compiled.");
	}

}
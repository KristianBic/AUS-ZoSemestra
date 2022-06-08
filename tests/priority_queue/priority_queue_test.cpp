#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
		addTest(new PriorityQueueTwoListsTesting());
		addTest(new PQTLScenarioA());
		addTest(new PQTLScenarioB());
		addTest(new PQTLScenarioC());
		addTest(new PqtlTask3());
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
		addTest(new HeapTesting());
		addTest(new HeapScenarioA());
		addTest(new HeapScenarioB());
		addTest(new HeapScenarioC());
		addTest(new HeapTask3());
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }


	HeapTesting::HeapTesting() : SimpleTest("Heap_Tests") {}
	void HeapTesting::test() {
		structures::Heap<int>* heap = new structures::Heap<int>();
		structures::Heap<int>* heapSecond = new structures::Heap<int>();

		for (size_t i = 0; i < 101; i++)
		{
			heap->push(i, i);
		}
		int x = 200;
		this->assertTrue(heap->peek() == 0, "Heap_peek");
		heap->push(x, x);
		this->assertTrue(heap->peek() == 0, "Heap_push");
		this->assertTrue(heap->peekPriority() == 0, "Heap_peekPriority");
		this->assertTrue(heap->pop() == 0, "Heap_pop");
		heap->assign(*heapSecond);
		this->assertTrue(heap->size() == heapSecond->size(), "Heap_assign");

		delete heap;
		delete heapSecond;
		this->logPass("Compiled.");
	}

	PriorityQueueTwoListsTesting::PriorityQueueTwoListsTesting() : SimpleTest("PriorityQueueTwoLists_Tests") {}
	void PriorityQueueTwoListsTesting::test() {
		structures::PriorityQueueTwoLists<int>* PQTL = new structures::PriorityQueueTwoLists<int>();
		structures::PriorityQueueTwoLists<int>* PQTLSecond = new structures::PriorityQueueTwoLists<int>();

		for (size_t i = 0; i < 101; i++)
		{
			PQTL->push(i, i);
		}
		this->logInfo(std::to_string(PQTL->size()));
		int x = 200;
		this->assertTrue(PQTL->peek() == 0, "PQTL_peek");
		PQTL->push(x, x);
		this->assertTrue(PQTL->peek() == 0, "PQTL_push");
		this->assertTrue(PQTL->peekPriority() == 0, "PQTL_peekPriority");
		this->assertTrue(PQTL->pop() == 0, "PQTL_pop");
		PQTL->assign(*PQTLSecond);
		this->assertTrue(PQTL->size() == PQTLSecond->size(), "PQTL_assign");

		delete PQTL;
		delete PQTLSecond;
		this->logPass("Compiled.");
	}


	ScenarioMain::ScenarioMain(int push, int pop, int peek, std::string scenarioName, std::string structure) :
		push_(push), pop_(pop), peek_(peek), scenarioName_(scenarioName) , structure_(structure), SimpleTest(scenarioName) {}

	void ScenarioMain::test()
	{
		structures::PriorityQueue<int>* priorityQueue;
		if (this->structure_ == "HEAP")
		{
			priorityQueue = new structures::Heap<int>();
		}
		else if (this->structure_ == "PQTL") {
			priorityQueue = new structures::PriorityQueueTwoLists<int>();
		}
		else {
			throw std::runtime_error("Zly typ struktury: " + this->structure_ +" , "+ scenarioName_);
		}

		for (size_t i = 0; i < 1000; i++)
		{
			priorityQueue->push(i, i);
		}
		
		size_t pushCount = 0;
		size_t popCount = 0;
		size_t peekCount = 0;

		structures::DurationType pushSum = structures::DurationType::zero();
		structures::DurationType popSum = structures::DurationType::zero();
		structures::DurationType peekSum = structures::DurationType::zero();


		bool scenatioFinished = true;

		while (scenatioFinished) {

			int random = rand() % 3 + 1;
			int randomPriority = rand() % priorityQueue->size();
			int randomData = rand() % priorityQueue->size();

			switch (random) {
			case 1:
				if (pushCount != push_)
				{
					pushCount++;
					startStopwatch();
					priorityQueue->push(randomPriority, randomData);
					stopStopwatch();
					pushSum += getElapsedTime();
					priorityQueue->pop();
					break;
				}
			case 2:
				if (popCount != pop_)
				{
					popCount++;
					startStopwatch();
					priorityQueue->pop();
					stopStopwatch();
					popSum += getElapsedTime();
					priorityQueue->push(randomPriority, randomData);
					break;
				}
			case 3:
				if (peekCount != peek_)
				{
					peekCount++;
					startStopwatch();
					priorityQueue->peek();
					stopStopwatch();
					peekSum += getElapsedTime();
					break;
				}
			default:
				if ((pushCount + popCount + peekCount) != (this->push_ + this->pop_ + this->peek_))
				{
					break;
				}
				else {
					scenatioFinished = false;
				}
			}
		}
		structures::Logger::getInstance().logInfo(scenarioName_);
		structures::Logger::getInstance().logDuration(pushSum, "pushSum");
		structures::Logger::getInstance().logDuration(popSum, "popSum");
		structures::Logger::getInstance().logDuration(peekSum, "peekSum");
		structures::Logger::getInstance().logInfo("");
		logPass("Compiled.");

		delete priorityQueue;
	}

	HeapScenarioA::HeapScenarioA() : ScenarioMain(35000, 35000, 30000, "Heap_ScenatioA", "HEAP") {}
	HeapScenarioB::HeapScenarioB() : ScenarioMain(50000, 30000, 20000, "Heap_ScenatioB", "HEAP") {}
	HeapScenarioC::HeapScenarioC() : ScenarioMain(70000, 25000, 5000, "Heap_ScenatioC", "HEAP") {}

	PQTLScenarioA::PQTLScenarioA() : ScenarioMain(35000, 35000, 30000, "PQTL_ScenatioA", "PQTL") {}
	PQTLScenarioB::PQTLScenarioB() : ScenarioMain(50000, 30000, 20000, "PQTL_ScenatioB", "PQTL") {}
	PQTLScenarioC::PQTLScenarioC() : ScenarioMain(70000, 25000, 5000, "PQTL_ScenatioC", "PQTL") {}




	Task3::Task3(std::string testName, std::string structure) : 
		testName_(testName), structure_(structure), SimpleTest(testName) {}
	void Task3::test() {

		structures::Logger::getInstance().logInfo(structure_);
		structures::DurationType pushSum = structures::DurationType::zero();
		structures::DurationType popSum = structures::DurationType::zero();
		structures::DurationType peekSum = structures::DurationType::zero();

		for (size_t i = 1000; i < 10001; i += 1000)
		{
			structures::PriorityQueue<int>* priorityQueue;
			if (this->structure_ == "HEAP")
			{
				priorityQueue = new structures::Heap<int>();
			}
			else if (this->structure_ == "PQTL") {
				priorityQueue = new structures::PriorityQueueTwoLists<int>();
			}
			else {
				throw std::runtime_error("Zly typ struktury: " + this->structure_ + " , " + testName_);
			}

			for (size_t o = 0; o < i; o++)
			{
				priorityQueue->push(o, o);
			}

			for (size_t x = 0; x < 100; x++)
			{
				int randomPriority = rand() % i;
				int randomData = rand() % i;

				startStopwatch();
				priorityQueue->push(randomPriority, randomData);
				stopStopwatch();
				pushSum += getElapsedTime();

				startStopwatch();
				priorityQueue->pop();
				stopStopwatch();
				popSum += getElapsedTime();

				startStopwatch();
				priorityQueue->peek();
				stopStopwatch();
				peekSum += getElapsedTime();

			}

			structures::Logger::getInstance().logInfo("List size - " + std::to_string(i));
			structures::Logger::getInstance().logDuration(pushSum, "push");
			structures::Logger::getInstance().logDuration(popSum, "pop");
			structures::Logger::getInstance().logDuration(peekSum, "peek");

			pushSum = structures::DurationType::zero();
			popSum = structures::DurationType::zero();
			peekSum = structures::DurationType::zero();

			delete priorityQueue;
		}
		logPass("Compiled.");
	}

	HeapTask3::HeapTask3() : Task3("Heap_Test3", "HEAP") {}
	PqtlTask3::PqtlTask3() : Task3("PQTL_Test3", "PQTL") {}
}
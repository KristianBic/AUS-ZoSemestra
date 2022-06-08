#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"
#include "../../structures/_logger/file_log_consumer.h"

using namespace std;
namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;	
	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new CoherentMatrixTestTask1());
		addTest(new CoherentMatrixTestTask2ScenarioA());
		addTest(new CoherentMatrixTestTask2ScenarioB());
		addTest(new CoherentMatrixTestTask2ScenarioC());
		addTest(new CoherentMatrixTestTask2ScenarioD());
		addTest(new CoherentMatrixTestTask3());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentMatrixTestTask1());
		addTest(new IncoherentMatrixTestTask2ScenarioA());
		addTest(new IncoherentMatrixTestTask2ScenarioB());
		addTest(new IncoherentMatrixTestTask2ScenarioC());
		addTest(new IncoherentMatrixTestTask2ScenarioD());
		addTest(new IncoherentMatrixTestTask3());
	}

	CoherentMatrixTestTask1::CoherentMatrixTestTask1() : SimpleTest("Task1Coherent") {}
	void CoherentMatrixTestTask1::test() {
		structures::CoherentMatrix<int>* matrix = new structures::CoherentMatrix<int>(3, 4);
		structures::CoherentMatrix<int>* secondMatrix = new structures::CoherentMatrix<int>(3, 4);
		structures::CoherentMatrix<int>* thirdMatrix = new structures::CoherentMatrix<int>(*matrix);
		
		size_t count = 0;
		for (size_t i = 0; i < secondMatrix->getRowCount(); i++)
		{
			for (size_t j = 0; j < secondMatrix->getColumnCount(); j++)
			{
				secondMatrix->at(i, j) = count;
				count++;
			}
		}
		
		this->logInfo("Task1CoherentMatrix");
		this->assertTrue(matrix->equals(*thirdMatrix), "Coherent_Copy");
		this->assertTrue(matrix->size() == 3 * 4, "Coherent_size");
		this->assertTrue(matrix->getRowCount() == 3, "Coherent_getRowCount");
		this->assertTrue(matrix->getColumnCount() == 4, "Coherent_getColumnCount");
		this->assertTrue(matrix->at(2, 2) == 0, "Coherent_at");
		matrix->assign(*secondMatrix);
		this->assertTrue(matrix->equals(*secondMatrix) == true, "Coherent_equals_assign");
		
		delete matrix;
		delete secondMatrix;
		delete thirdMatrix;
	}

	IncoherentMatrixTestTask1::IncoherentMatrixTestTask1() : SimpleTest("Task1Incoherent") {}
	void IncoherentMatrixTestTask1::test() {
		structures::IncoherentMatrix<int>* matrix = new structures::IncoherentMatrix<int>(3, 4);
		structures::IncoherentMatrix<int>* secondMatrix = new structures::IncoherentMatrix<int>(3, 4);
		structures::IncoherentMatrix<int>* thirdMatrix = new structures::IncoherentMatrix<int>(*matrix);

		size_t count = 0;
		for (size_t i = 0; i < secondMatrix->getRowCount(); i++)
		{
			for (size_t j = 0; j < secondMatrix->getColumnCount(); j++)
			{
				secondMatrix->at(i, j) = count;
				count++;
			}
		}
		this->logInfo("Task1IncoherentMatrix");
		this->assertTrue(matrix->equals(*thirdMatrix), "Coherent_Copy");
		this->assertTrue(matrix->size() == 3 * 4, "Incoherent_size");
		this->assertTrue(matrix->getRowCount() == 3, "Incoherent_getRowCount");
		this->assertTrue(matrix->getColumnCount() == 4, "Incoherent_getColumnCount");
		this->assertTrue(matrix->at(2, 2) == 0, "Incoherent_at");
		this->assertTrue(matrix->equals(*secondMatrix) == true, "Incoherent_equals");
		matrix->assign(*secondMatrix);
		this->assertTrue(matrix->equals(*secondMatrix) == true, "Incoherent_equals_assign");
		delete matrix;
		delete secondMatrix;
		delete thirdMatrix;
	}


	CoherentMatrixTestTask2Main::CoherentMatrixTestTask2Main(int x, int y, int getRowMax, int getColumnMax, int atMax, std::string scenarioName) : SimpleTest(scenarioName) {
		x_ = x;
		y_ = y;
		getRow_ = getRowMax;
		getColumn_ = getColumnMax;
		at_ = atMax;
		scenarioName_ = scenarioName;
	}

	void CoherentMatrixTestTask2Main::test() {

		structures::CoherentMatrix<int>* matrix = new structures::CoherentMatrix<int>(x_, y_);

		size_t getRowCount = 0;
		size_t getColumnCount = 0;
		size_t atCount = 0;

		structures::DurationType getRowSum = structures::DurationType::zero();
		structures::DurationType getColumnSum = structures::DurationType::zero();
		structures::DurationType atSum = structures::DurationType::zero();

		bool scenatioFinished = true;

		while (scenatioFinished) {
			int random = rand() % 3 + 1;
			int randomRow = rand() % x_;
			int randomColumn = rand() % y_;
			switch (random) {
			case 1:
				if (getRowCount != getRow_)
				{
					getRowCount++;
					startStopwatch();
					matrix->getRowCount();
					stopStopwatch();
					getRowSum += getElapsedTime();
					break;
				}
			case 2:
				if (getColumnCount != getColumn_)
				{
					getColumnCount++;
					startStopwatch();
					matrix->getColumnCount();
					stopStopwatch();
					getColumnSum += getElapsedTime();
					break;
				}
			case 3:
				if (atCount != at_)
				{
					atCount++;
					startStopwatch();
					matrix->at(randomRow, randomColumn);
					stopStopwatch();
					atSum += getElapsedTime();
					break;
				}
			default:
				if ((getRowCount != getRow_) && (getColumnCount != getColumn_) && (atCount != at_))
				{
					break;
				}
				else {
					scenatioFinished = false;
				}
			}
		}
		
		structures::Logger::getInstance().logInfo(scenarioName_);
		structures::Logger::getInstance().logDuration(getRowSum, "getRowSum");
		structures::Logger::getInstance().logDuration(getColumnSum, "getColumnSum");
		structures::Logger::getInstance().logDuration(atSum, "atSum");
		structures::Logger::getInstance().logInfo(" ");
		logPass("Compiled.");
		delete matrix;
	}

	IncoherentMatrixTestTask2Main::IncoherentMatrixTestTask2Main(int x, int y, int getRowMax, int getColumnMax, int atMax, std::string scenarioName) : SimpleTest(scenarioName) {
		x_ = x;
		y_ = y;
		getRow_ = getRowMax;
		getColumn_ = getColumnMax;
		at_ = atMax;
		scenarioName_ = scenarioName;
	}

	void IncoherentMatrixTestTask2Main::test() {

		structures::IncoherentMatrix<int>* matrix = new structures::IncoherentMatrix<int>(x_, y_);

		size_t getRowCount = 0;
		size_t getColumnCount = 0;
		size_t atCount = 0;

		structures::DurationType getRowSum = structures::DurationType::zero();
		structures::DurationType getColumnSum = structures::DurationType::zero();
		structures::DurationType atSum = structures::DurationType::zero();

		bool scenatioFinished = true;

		while (scenatioFinished) {
			int random = rand() % 3 + 1;
			int randomRow = rand() % x_;
			int randomColumn = rand() % y_;
			switch (random) {
			case 1:
				if (getRowCount != getRow_)
				{
					getRowCount++;
					startStopwatch();
					matrix->getRowCount();
					stopStopwatch();
					getRowSum += getElapsedTime();
					break;
				}
			case 2:
				if (getColumnCount != getColumn_)
				{
					getColumnCount++;
					startStopwatch();
					matrix->getColumnCount();
					stopStopwatch();
					getColumnSum += getElapsedTime();
					break;
				}
			case 3:
				if (atCount != at_)
				{
					atCount++;
					startStopwatch();
					matrix->at(randomRow, randomColumn);
					stopStopwatch();
					atSum += getElapsedTime();
					break;
				}
			default:
				if ((getRowCount != getRow_) && (getColumnCount != getColumn_) && (atCount != at_))
				{
					break;
				}
				else {
					scenatioFinished = false;
				}
			}
		}
		structures::Logger::getInstance().logInfo(scenarioName_);
		structures::Logger::getInstance().logDuration(getRowSum, "getRowSum");
		structures::Logger::getInstance().logDuration(getColumnSum, "getColumnSum");
		structures::Logger::getInstance().logDuration(atSum, "atSum");
		structures::Logger::getInstance().logInfo(" ");
		logPass("Compiled.");
		delete matrix;
	}

	CoherentMatrixTestTask2ScenarioA::CoherentMatrixTestTask2ScenarioA() : CoherentMatrixTestTask2Main(10, 50, 50000, 50000, 900000, "Task2CoherentScenarioA") {}
	CoherentMatrixTestTask2ScenarioB::CoherentMatrixTestTask2ScenarioB() : CoherentMatrixTestTask2Main(2000, 500, 50000, 50000, 900000, "Task2CoherentScenarioB") {}
	CoherentMatrixTestTask2ScenarioC::CoherentMatrixTestTask2ScenarioC() : CoherentMatrixTestTask2Main(50, 10, 100000, 300000, 600000, "Task2CoherentScenarioC") {}
	CoherentMatrixTestTask2ScenarioD::CoherentMatrixTestTask2ScenarioD() : CoherentMatrixTestTask2Main(500, 2000, 100000, 300000, 600000, "Task2CoherentScenarioD") {}

	IncoherentMatrixTestTask2ScenarioA::IncoherentMatrixTestTask2ScenarioA() : IncoherentMatrixTestTask2Main(10, 50, 50000, 50000, 900000, "Task2IncoherentScenarioA") {}
	IncoherentMatrixTestTask2ScenarioB::IncoherentMatrixTestTask2ScenarioB() : IncoherentMatrixTestTask2Main(2000, 500, 50000, 50000, 900000, "Task2IncoherentScenarioB") {}
	IncoherentMatrixTestTask2ScenarioC::IncoherentMatrixTestTask2ScenarioC() : IncoherentMatrixTestTask2Main(50, 10, 100000, 300000, 600000, "Task2IncoherentScenarioC") {}
	IncoherentMatrixTestTask2ScenarioD::IncoherentMatrixTestTask2ScenarioD() : IncoherentMatrixTestTask2Main(500, 2000, 100000, 300000, 600000, "Task2IncoherentScenarioD") {}

	CoherentMatrixTestTask3::CoherentMatrixTestTask3() : SimpleTest("Task3Coherent") {}
	void CoherentMatrixTestTask3::atANDassign(int i, int j)
	{

		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType assignSum = structures::DurationType::zero();

		structures::CoherentMatrix<int>* matrix = new structures::CoherentMatrix<int>(i, j);
		structures::CoherentMatrix<int>* secondMatrix = new structures::CoherentMatrix<int>(i, j);

		
		for (size_t x = 0; x < 100; x++)
		{
			int randomRow = rand() % i;
			int randomColumn = rand() % j;

			startStopwatch();
			matrix->at(randomRow, randomColumn);
			stopStopwatch();
			atSum += getElapsedTime();

			startStopwatch();
			matrix->assign(*secondMatrix);
			stopStopwatch();
			assignSum += getElapsedTime();
		}

		structures::Logger::getInstance().logInfo("Matrix " + to_string(i) + "-" + to_string(j));
		structures::Logger::getInstance().logDuration(atSum, "at");
		structures::Logger::getInstance().logDuration(assignSum, "assign");
		
		delete matrix;
		delete secondMatrix;
	}
	void CoherentMatrixTestTask3::test() {
		structures::Logger::getInstance().logInfo("---CoherentMatrix---");
		for (size_t i = 0; i < 1001; i += 100)
		{
			for (size_t j = 0; j < 1001; j += 100)
			{
				if (i == 0 && j == 0)
				{
					atANDassign(1, 1);
				}
				else if (i == 0 && j != 0){
					atANDassign(1, j);
				}
				else if (i != 0 && j == 0) {
					atANDassign(i, 1);
				}
				else {
					atANDassign(i, j);
				}
			}
		}
		logPass("Compiled.");
	}


	IncoherentMatrixTestTask3::IncoherentMatrixTestTask3() : SimpleTest("Task3Incoherent") {}
	void IncoherentMatrixTestTask3::atANDassign(int i, int j)
	{

		structures::DurationType atSum = structures::DurationType::zero();
		structures::DurationType assignSum = structures::DurationType::zero();

		structures::IncoherentMatrix<int>* matrix = new structures::IncoherentMatrix<int>(i, j);
		structures::IncoherentMatrix<int>* secondMatrix = new structures::IncoherentMatrix<int>(i, j);


		for (size_t x = 0; x < 100; x++)
		{
			int randomRow = rand() % i;
			int randomColumn = rand() % j;

			startStopwatch();
			matrix->at(randomRow, randomColumn);
			stopStopwatch();
			atSum += getElapsedTime();

			startStopwatch();
			matrix->assign(*secondMatrix);
			stopStopwatch();
			assignSum += getElapsedTime();
		}

		structures::Logger::getInstance().logInfo("Matrix " + to_string(i) + "-" + to_string(j));
		structures::Logger::getInstance().logDuration(atSum, "at");
		structures::Logger::getInstance().logDuration(assignSum, "assign");
		
		delete matrix;
		delete secondMatrix;
	}
	void IncoherentMatrixTestTask3::test() {
		structures::Logger::getInstance().logInfo("---IncoherentMatrix---");
		for (size_t i = 0; i < 1001; i += 100)
		{
			for (size_t j = 0; j < 1001; j += 100)
			{
				if (i == 0 && j == 0)
				{
					atANDassign(1, 1);
				}
				else if (i == 0 && j != 0) {
					atANDassign(1, j);
				}
				else if (i != 0 && j == 0) {
					atANDassign(i, 1);
				}
				else {
					atANDassign(i, j);
				}
			}
		}
		logPass("Compiled.");
	}


	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		srand(time(NULL));
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}
	
}

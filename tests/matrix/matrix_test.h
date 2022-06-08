#pragma once

#include "../test.h"
#include "../../structures/matrix/matrix.h"



namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;


	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};


	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};

	class CoherentMatrixTestTask1 : public SimpleTest {
	public:
		CoherentMatrixTestTask1();
		void test() override;
	};

	class IncoherentMatrixTestTask1 : public SimpleTest {
	public:
		IncoherentMatrixTestTask1();
		void test() override;
	};

	class CoherentMatrixTestTask2Main : public SimpleTest {
	private:
		size_t x_ = 0;
		size_t y_ = 0;
		size_t getRow_ = 0;
		size_t getColumn_ = 0;
		size_t at_ = 0;
		std::string scenarioName_;
	public:
		CoherentMatrixTestTask2Main(int x, int y, int getRowMax, int getColumnMax, int atMax, std::string scenarioName);
		void test() override;
	};

	class IncoherentMatrixTestTask2Main : public SimpleTest {
	private:
		size_t x_ = 0;
		size_t y_ = 0;
		size_t getRow_ = 0;
		size_t getColumn_ = 0;
		size_t at_ = 0;
		std::string scenarioName_;
	public:
		IncoherentMatrixTestTask2Main(int x, int y, int getRowMax, int getColumnMax, int atMax, std::string scenarioName);
		void test() override;
	};

	class CoherentMatrixTestTask2ScenarioA : public CoherentMatrixTestTask2Main {
	public:
		CoherentMatrixTestTask2ScenarioA();
	};

	class CoherentMatrixTestTask2ScenarioB : public CoherentMatrixTestTask2Main {
	public:
		CoherentMatrixTestTask2ScenarioB();
	};

	class CoherentMatrixTestTask2ScenarioC : public CoherentMatrixTestTask2Main {
	public:
		CoherentMatrixTestTask2ScenarioC();
	};

	class CoherentMatrixTestTask2ScenarioD : public CoherentMatrixTestTask2Main {
	public:
		CoherentMatrixTestTask2ScenarioD();
	};

	class IncoherentMatrixTestTask2ScenarioA : public IncoherentMatrixTestTask2Main {
	public:
		IncoherentMatrixTestTask2ScenarioA();
	};

	class IncoherentMatrixTestTask2ScenarioB : public IncoherentMatrixTestTask2Main {
	public:
		IncoherentMatrixTestTask2ScenarioB();
	};

	class IncoherentMatrixTestTask2ScenarioC : public IncoherentMatrixTestTask2Main {
	public:
		IncoherentMatrixTestTask2ScenarioC();
	};

	class IncoherentMatrixTestTask2ScenarioD : public IncoherentMatrixTestTask2Main {
	public:
		IncoherentMatrixTestTask2ScenarioD();
	};



	class CoherentMatrixTestTask3 : public SimpleTest {
	public:
		CoherentMatrixTestTask3();
		void atANDassign(int i, int j);
		void test() override;
	};

	class IncoherentMatrixTestTask3 : public SimpleTest {
	public:
		IncoherentMatrixTestTask3();
		void atANDassign(int i, int j);
		void test() override;
	};

	
	
}
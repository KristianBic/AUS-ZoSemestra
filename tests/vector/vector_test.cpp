#include "vector_test.h"
#include "../../structures/vector/vector.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    {
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
        structures::Vector::copy(*vector, 0, *vector, 0, 1);
        delete vector;
        SimpleTest::logPass("Compiled.");
    }
    //VectorTestAt
    VectorTestAt::VectorTestAt() : 
        SimpleTest("Vector::at(int)")
    {
    }
    void VectorTestAt::test()
    {
        structures::Vector* testVector = new structures::Vector(10); // namiesto structures mozme dat aj - using namespace structures
        SimpleTest::assertTrue(testVector->size() == 10, "testVector->size()");

        for (int i = 0; i < 10; i++)
        {
            testVector->at(i) = i;
        }
        for (int i = 0; i < 10; i++)
        {
            SimpleTest::assertTrue(testVector->at(i) == i, "testVector->at("+ std::to_string(i) + ")");
            SimpleTest::assertTrue(*(testVector->getBytePointer(i)) == i, "getBytePointer->at(" + std::to_string(i) + ")");
        }
        delete testVector;
    }

// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        addTest(new VectorTestInterface());
        addTest(new VectorTestAt());
    }
  
}
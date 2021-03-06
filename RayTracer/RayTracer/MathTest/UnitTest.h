#pragma once
#include "Vec3.h"

class UnitTest
{
public:
	UnitTest();
	~UnitTest();
	void ConstructionTest();
	void MathematicalOperatorsTest();
	void LogicalOperatorTest();
	void LengthOperationsTest();
	void Check(float test, bool expression);

private:
};


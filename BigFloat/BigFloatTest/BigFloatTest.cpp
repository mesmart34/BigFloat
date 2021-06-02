#include "pch.h"
#include "CppUnitTest.h"

#include "../BigFloat/BigFloat.cpp"
#include "../BigFloat/BigFloat.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigFloatTest
{
	TEST_CLASS(BigFloatTest)
	{
	public:
		
		//Addition
		TEST_METHOD(TestMethod1)
		{
			auto a = BigFloat("10.0");
			auto b = BigFloat("50.0");
			auto actual = a + b;
			auto expected = BigFloat("60.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod2)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("50.0");
			auto actual = a + b;
			auto expected = BigFloat("40.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod3)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("-5.0");
			auto actual = a + b;
			auto expected = BigFloat("-15.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod4)
		{
			auto a = BigFloat("10.2525");
			auto b = BigFloat("-10.62626162");
			auto actual = a + b;
			auto expected = BigFloat("-0.37376162");
			Assert::IsTrue(actual == expected);
		}

		//Substraction
		TEST_METHOD(TestMethod5)
		{
			auto a = BigFloat("10.0");
			auto b = BigFloat("50.0");
			auto actual = a - b;
			auto expected = BigFloat("-40.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod6)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("50.0");
			auto actual = a - b;
			auto expected = BigFloat("-60.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod7)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("-5.0");
			auto actual = a - b;
			auto expected = BigFloat("-5.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod8)
		{
			auto a = BigFloat("10.2525");
			auto b = BigFloat("-10.62626162");
			auto actual = a - b;
			auto expected = BigFloat("20.87876162");
			Assert::IsTrue(actual == expected);
		}

		//Division
		TEST_METHOD(TestMethod9)
		{
			auto a = BigFloat("10.0");
			auto b = BigFloat("50.0");
			auto actual = a / b;
			auto expected = BigFloat("0.2");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod10)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("50.0");
			auto actual = a / b;
			auto expected = BigFloat("-0.2");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod11)
		{
			auto a = BigFloat("256.256");
			auto b = BigFloat("12.521");
			auto actual = a / b;
			auto expected = BigFloat("20.466");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod12)
		{
			auto a = BigFloat("10.2525");
			auto b = BigFloat("-10.62626162");
			auto actual = a / b;
			auto expected = BigFloat("-0.96482661");
			Assert::IsTrue(actual == expected);
		}

		//Multiplication
		TEST_METHOD(TestMethod13)
		{
			auto a = BigFloat("10.12");
			auto b = BigFloat("50.2");
			auto actual = a * b;
			auto expected = BigFloat("508.024");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod14)
		{
			auto a = BigFloat("-10.0");
			auto b = BigFloat("50.0");
			auto actual = a * b;
			auto expected = BigFloat("-500.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod15)
		{
			auto a = BigFloat("256.256");
			auto b = BigFloat("12.521");
			auto actual = a * b;
			auto expected = BigFloat("3208.581376");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod16)
		{
			auto a = BigFloat("10.2525");
			auto b = BigFloat("-10.62626162");
			auto actual = a * b;
			auto expected = BigFloat("-108.94574725905");
			Assert::IsTrue(actual == expected);
		}

		//Euclid
		TEST_METHOD(TestMethod17)
		{
			auto a = BigFloat("256.0");
			auto b = BigFloat("128.0");
			auto actual = BigFloat::GCD(a, b);
			auto expected = BigFloat("128.0");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod18)
		{
			auto a = BigFloat("256.0");
			auto b = BigFloat("128.0");
			auto divider = BigFloat::GCD(a, b);
			auto actual = (a / divider) / (b / divider);
			auto expected = a / b;
			Assert::IsTrue(actual == expected);
		}

		//Periodic to common
		
		TEST_METHOD(TestMethod19)
		{
			auto a = BigFloat("256.0(2)");
			auto b = BigFloat("128.0(2)");
			auto actual = a / b;
			auto expected = BigFloat("256.022222222222222222222") / BigFloat("128.022222222222222222222");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod20)
		{
			auto a = BigFloat("1256.0(256)");
			auto b = BigFloat("8.0(128)");
			auto actual = a / b;
			auto expected = BigFloat("1256.0256256256256256256") / BigFloat("8.0128128128128128128");
			Assert::IsTrue(actual == expected);
		}

		//Common to periodic

		TEST_METHOD(TestMethod21)
		{
			auto a = BigFloat("256.022222222222222222222");
			auto b = BigFloat("128.022222222222222222222");
			auto actual = a / b;
			auto expected = BigFloat("256.0(2)") / BigFloat("128.0(2)");
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod22)
		{
			auto a = BigFloat("1256.0256256256256256256");
			auto b = BigFloat("8.0128128128128128128");
			auto actual = a / b;
			auto expected = BigFloat("1256.0(256)") / BigFloat("8.0(128)");
			Assert::IsTrue(actual == expected);
		}
	};
}

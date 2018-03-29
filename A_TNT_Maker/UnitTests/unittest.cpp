#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

_declspec(dllimport) char* GetTeam();
_declspec(dllimport) bool SetMaze(const int** data, int width, int height);
_declspec(dllimport) int** GetMaze(int& width, int& height);
_declspec(dllimport) bool GetNextPosition(int& xpos, int& ypos);
_declspec(dllimport) bool SetStart(int xpos, int ypos);
_declspec(dllimport) bool GetStart(int& xpos, int& ypos);
_declspec(dllimport) bool SetEnd(int xpos, int ypos);
_declspec(dllimport) bool GetEnd(int& xpos, int& ypos);

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestGetMazeBadData)
		{
			//Test that GetMaze returns false when maze's data isn't set
			int x;
			int y;
			bool ret = GetMaze(x, y);
			Assert::IsFalse(ret);
		}
		
		TEST_METHOD(TestSetMazeBadX)
		{
			//Test that SetMaze method returns false with bad X value
			int** a = new int*[10];

			for (int x = 0; x < 10; x++) //Loop to fill in the maze array
			{
				a[x] = new int[10]; //Initialize maze
			}

			bool ret = SetMaze((const int**)a, -1, 2);
			Assert::IsFalse(ret);

			delete[] a;
		}

		TEST_METHOD(TestSetMazeBadY)
		{
			//Test that SetMaze method returns false with bad Y value
			int** a = new int*[10];

			for (int x = 0; x < 10; x++) //Loop to fill in the maze array
			{
				a[x] = new int[10]; //Initialize maze
			}

			bool ret = SetMaze((const int**)a, 2, -1);
			Assert::IsFalse(ret);

			delete[] a;
		}

		TEST_METHOD(TestGetNextPosition)
		{

		}

		TEST_METHOD(TestSetStartBadX)
		{
			//Test that SetStart method returns false with bad X value
			bool ret = SetStart(-1, 4);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TestSetStartBadY)
		{
			//Test that SetStart method returns false with bad X value
			bool ret = SetStart(4, -1);
			Assert::IsFalse(ret);
		}
		
		TEST_METHOD(TestGetStart)
		{
			//Test that GetStart return false with invalid values
			int x = -1;
			int y = -1;
			bool ret = GetStart(x, y);
			Assert::IsFalse(ret);
		}
		
		TEST_METHOD(TestSetEndBadX)
		{
			//Test that SetEnd method returns false with bad X value
			bool ret = SetEnd(-1, 4);
			Assert::IsFalse(ret);
		}
		
		TEST_METHOD(TestSetEndBadY)
		{
			//Test that SetEnd method returns false with bad X value
			bool ret = SetEnd(-1, 4);
			Assert::IsFalse(ret);
		}
		
		TEST_METHOD(TestGetEnd)
		{
			//Test that GetEnd return false with invalid values
			int x = -1;
			int y = -1;
			bool ret = GetEnd(x, y);
			Assert::IsFalse(ret);
		}
	};
}
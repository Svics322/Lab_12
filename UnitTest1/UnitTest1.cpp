#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_PDS\Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestShortestPath)
		{
			Graph graph(5);
			graph.addEdge(0, 1, 2);
			graph.addEdge(0, 2, 4);
			graph.addEdge(1, 2, 1);
			graph.addEdge(1, 3, 7);
			graph.addEdge(2, 4, 3);
			graph.addEdge(3, 4, 1);

			vector<int> dist = graph.djikstra(0);
			Assert::AreEqual(0, dist[0]);
			Assert::AreEqual(2, dist[1]);
			Assert::AreEqual(3, dist[2]);
			Assert::AreEqual(9, dist[3]);
			Assert::AreEqual(6, dist[4]);
		}

		TEST_METHOD(TestUnreachable)
		{
			Graph graph(4);
			graph.addEdge(0, 1, 5);
			graph.addEdge(1, 2, 10);

			vector<int> dist = graph.djikstra(0);
			Assert::AreEqual(0, dist[0]);
			Assert::AreEqual(5, dist[1]);
			Assert::AreEqual(15, dist[2]);
			Assert::AreEqual(numeric_limits<int>::max(), dist[3]);
		}

	};
}

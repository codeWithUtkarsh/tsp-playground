#include "tests.hpp"

#include <iostream>
#include "Timer.hpp"
#include "graphGenerator.hpp"
#include "FileUtils.hpp"
#include "printColor.hpp"
#include "TestResult.hpp"
#include "Path.hpp"
#include "branchAndBound.hpp"

void Tests::fileInstanceTest(GraphMatrix *graph, int iterCount, std::string instanceName, std::string outputPath)
{
    FileUtils::writeInstanceTestHeader(outputPath);
    Timer timer;
    const int startingVertex = 0;

    for (int i = 0; i < iterCount; ++i)
    {
        timer.start();
        Path path = BranchAndBound::execute(graph, startingVertex);
        const unsigned long elapsedTime = timer.getElapsedNs();

        bool isCorrect = path.weight == graph->optimum;

        TestResult testResult(instanceName, elapsedTime, path, isCorrect);

        FileUtils::appendTestResult(outputPath, testResult);
    }
}

void Tests::randomInstanceTest(int minSize, int maxSize, int iterCountPerInstance, int instanceCountPerSize, std::string outputPath)
{
    const int startingVertex = 0;
    FileUtils::writeRandomInstanceTestHeader(outputPath);
    Timer timer;
    GraphMatrix *graph;
    printf("%i, %i\n", iterCountPerInstance, instanceCountPerSize);

    for (int vertexCount = minSize; vertexCount <= maxSize; vertexCount++)
    {
        srand(1);
        // Average time for all instances of this size
        long unsigned averageTime = 0;
        for (int i = 0; i < instanceCountPerSize; ++i)
        {
            graph = graphGenerator::getRandom(vertexCount, 10);

            for (int j = 0; j < iterCountPerInstance; ++j)
            {
                timer.start();
                BranchAndBound::execute(graph, startingVertex);

                averageTime += timer.getElapsedNs();
            }
            delete graph;
            graph = NULL;
        }
        averageTime /= iterCountPerInstance * instanceCountPerSize;
        FileUtils::appendRandomInstanceTestResult(outputPath, vertexCount, averageTime);
    }
    printf("Done. Saved to file.\n");
}

void Tests::testAlgorithm(std::vector<std::string> instances)
{
    const int startingVertex = 0;

    for (std::string instanceName : instances)
    {
        GraphMatrix *graph;
        graph = FileUtils::loadGraph(instanceName);

        Path path = BranchAndBound::execute(graph, startingVertex);
        const bool correctRes = path.weight == graph->optimum;

        printf("%14s", instanceName.c_str());

        if (correctRes)
        {
            printColor(" PASS\n", GREEN, BOLD, BOLD);
        }
        else
        {
            printColor(" FAIL\n", RED, BOLD, BOLD);
        }

        delete graph;
        graph = NULL;
    }
}

#include "../headers/allHeaders.h"

#include <filesystem>
#include <iostream>



int main(int argc, char** argv)
{
    std::cout << "Execution started" << std::endl;

    //!Hard coding all the file Names;
    std::vector<std::string> fileNames;
    //fileNames.emplace_back("tinyEWD.txt");
    //fileNames.emplace_back("mediumEWD.txt");
//fileNames.emplace_back("largeEWD.txt");
    //fileNames.emplace_back("1000EWD.txt");
 //fileNames.emplace_back("10000EWD.txt");
 fileNames.emplace_back("WikiTalk.txt");


    //!Getting the current path
    auto currPath = std::filesystem::current_path().string();

    for(size_t fileCount = 0; fileCount < fileNames.size(); ++fileCount)    //!Do all operations in this loop
    {
        auto currFileName = fileNames[fileCount];
        std::string currFileNameAppended =  std::string("/data/") + currFileName;

        std::cout << "Reading graph from " << currFileNameAppended <<std::endl;

        std::string fullFilePath = currPath + currFileNameAppended;
        Graph currGraph(fullFilePath);

        std::cout << "Reached Here" << std::endl;
        //!Create a new log file here
        std::string fulLogPath = currPath + std::string("/test/log_") + currFileName;

        std::cout << "Reached Here 1" << std::endl;

        std::fstream fileStream(fulLogPath, std::ios::app);
        fileStream << " " << std::endl;
        fileStream << " " << std::endl;
        fileStream << " " << std::endl;
        fileStream << " " << std::endl;
        fileStream << "================" << std::endl;
        fileStream << "================" << std::endl;
        fileStream << "New Run" << std::endl;

        Test test;
        test.DoTestingOnThisGraph(currGraph, fulLogPath);

        int tempDebugVar = 0;
    }
    std::cout << "Exited into main fxn" << std::endl;

    return 0;
}

// int main(int argc, char** argv)
// {
//     if(argc == 1)
//     {
//         std::cout<<"No user input. Exiting..."<<std::endl;
//         return 0;
//     }
//     long graphNumber = strtol(argv[1], NULL, 10);
//     std::cout << "Entered into main fxn" << std::endl;


//     auto currPath = std::filesystem::current_path().string();
//     std::string fileName = currPath + std::string("/test/tempGraph.json");
//     std::vector<int> vertices;
//     std::vector<std::pair<int,int>> edges;
//     AuxFxns::LoadGraphFromJason(graphNumber, fileName, vertices, edges);
//     VertexIdTracker * g_vidManager = VertexIdTracker::getInstance();


//     Graph graph;

//     std::unordered_map<int, int> table_dataValueToUniqueId;
//     for(int nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
//     {
//         std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
//         graph.AddNodeInGraph(g_vidManager->GetLastGeneratedIdIndex(), newVertex);
//         table_dataValueToUniqueId.insert({newVertex->getDataValue(),g_vidManager->GetLastGeneratedIdIndex()});
//     }
//     for(int edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
//     {
//         std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[edges[edgeIndex].first],
//                                                                     table_dataValueToUniqueId[edges[edgeIndex].second],
//                                                                     1.);
//         graph.AddEdgeInGraph(currEdge); 
//     }

//     Test test;
//     test.TestBFS(graph, 0);
//     //!Destroying the singlton objects
//     g_vidManager->DestroyIdManager();

//     std::cout << "Exited into main fxn" << std::endl;

//     return 0;
// }
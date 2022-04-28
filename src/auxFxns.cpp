#include "../headers/allHeaders.h"


bool AuxFxns::LoadGraphFromJason(long graphNumber, const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges)
{
    //Graph name
    std::string name = "Graph";
    name += std::to_string(graphNumber); 
    std::cout<<"Loading "<<name<<std::endl;
	// Load json data from scene file
	json data;
	std::ifstream in(filename);
	in >> data;

    //!Count
    long nodesCount = data[name]["VertexCount"][0];
    long edgesCount = data[name]["EdgeCount"][0];

    for(int i = 0; i < nodesCount; ++i)
    {
        vertices.push_back(int(data[name]["Vertex"][i]));
    }

    for(int i = 0; i < edgesCount; ++i)
    {
        int s = data[name]["Edge"][i][0];
        int e = data[name]["Edge"][i][1];
        edges.push_back(std::make_pair(s, e));
    }
    return true;
}




bool AuxFxns::LoadGraphFromTxtFiles(long graphNumber, 
                                    const std::string &filename, 
                                    std::vector<int> &vertices, 
                                    std::vector<std::pair<int, int> > &edges,
                                    std::vector<double> &weights)
{
    //!Import Text File and Read it
    std::ifstream graphStream(filename);
    if(graphStream.is_open() == false)
        return false;

    std::string currLine;

    std::getline(graphStream,currLine);
    int verticesCount = std::stoi(currLine);
    std::getline(graphStream,currLine);
    int edgesCount = std::stoi(currLine);
    
    vertices.clear();
    edges.clear();
    weights.clear();


    vertices.reserve(verticesCount);
    edges.reserve(edgesCount);
    weights.reserve(edgesCount);

    //!Initial vertieces with element value equal to element index
    for(int i = 0; i < verticesCount; ++i)
    {
        vertices.emplace_back(i);
    }

    int lineNo = 1;
    while (lineNo <= edgesCount)
    {
        std::getline(graphStream,currLine);
        std::istringstream currLineStrem(currLine);
        int node1 =0, node2 =0;
        double weight =0.;

        currLineStrem >> node1 >> node2 >> weight;

        edges.emplace_back(node1, node2);
        weights.emplace_back(weight);

        lineNo++;        
    }
    return true;    




}

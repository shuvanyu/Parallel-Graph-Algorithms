#include "../headers/allHeaders.h"


Graph::Graph()
{
    VertexIdTracker::getInstance();
}

Graph::~Graph()
{
    VertexIdTracker::getInstance()->DestroyIdManager();
}

Graph::Graph(std::string &fileName)
{
    VertexIdTracker::getInstance();

    std::vector<int> vertices;
    std::vector<std::pair<int,int> > edges;
    std::vector<double> weights;
    bool readingSuccess = AuxFxns::LoadGraphFromTxtFiles(0, 
                                                         fileName, 
                                                         vertices, 
                                                         edges,
                                                         weights);

    //!Hash table fetching node id from node value
    std::unordered_map<int, int> table_dataValueToUniqueId;
    //!Adding vertices to the graph
    for(int nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
    {
        std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
        AddNodeInGraph(VertexIdTracker::getInstance()->GetLastGeneratedIdIndex(), newVertex);
        table_dataValueToUniqueId.insert({newVertex->getDataValue(),VertexIdTracker::getInstance()->GetLastGeneratedIdIndex()});
    }
    //!Adding edges to the graph and stoding vertex neighbourhood
    for(int edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
    {
        int firstNodeDataValue = edges[edgeIndex].first;
        int secondNodeDataValue = edges[edgeIndex].second;
        double weight = weights[edgeIndex];
        std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[firstNodeDataValue],
                                                                    table_dataValueToUniqueId[secondNodeDataValue],
                                                                    weight);
        AddEdgeInGraph(currEdge);
    }
}

bool Graph::AddNodeInGraph(int uniqueNodeId, std::shared_ptr<Vertex> &node)
{
    p_table_uniqueNodeToVertex.insert({uniqueNodeId, node});
    return true;
} 

bool Graph::AddEdgeInGraph(std::shared_ptr<Edge> &edge) //Done 
{
    p_edges.push_back(edge);
    Edge e = *edge;
    Vertex *start = getVertexPointer(e.getStartVertexId());
    Vertex *end = getVertexPointer(e.getEndVertexId());
    start->addOutDegree(end->getId());
    end->addInDegree(start->getId());
    return true;
}

Vertex Graph::getVertex(long v) const
{
    return *p_table_uniqueNodeToVertex.at(v);
}

Vertex* Graph::getVertexPointer(long v) const
{
    return p_table_uniqueNodeToVertex.at(v).get();
}

long Graph::getNumberVertices() const
{
    return p_table_uniqueNodeToVertex.size();
}
long Graph::getNumberEdges() const
{
    return p_edges.size();
}

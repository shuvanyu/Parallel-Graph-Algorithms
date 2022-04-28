#include "../headers/allHeaders.h"
#include <algorithm>
#define N_THREADS 128

std::set<long> Interface::convertToSet(std::vector<long> &v)
{
    v.erase(std::unique(v.begin(), v.end()), v.end());


    std::set<long> s;
    for (auto &x : v) 
        s.insert(x);
    return s;
}

void Interface::RemoveDuplicates(VertexSubset &U) //TO DO: This function removes the duplicates from a vector
{
    U.getVertexSubset().erase(std::unique(U.getVertexSubset().begin(), U.getVertexSubset().end()), U.getVertexSubset().end());
    
    // std::set<long> s = convertToSet(U.getVertexSubset());
    // U.getVertexSubset.clear
    // U.getVertexSubset().assign(s.begin(), s.end());
    // return;
}


VertexSubset Interface::EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C, long threshold)
{
    // if(U.getVertexSubsetLength() + U.getVertexSubsetOutDegree(graph) > threshold)
    //     return EdgeMapDense(graph, U, F, C);
    // else
        return EdgeMapSparse(graph, U, F, C);
}


VertexSubset Interface::EdgeMapSparse(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out; 
    //TO DO: parallel
        #pragma omp parallel num_threads(N_THREADS)
        {
            
                #pragma omp for nowait
                for(long v = 0; v < U.getVertexSubsetLength(); v++)
                {
                    long curr = U.getVertexAt(v);
                    Vertex* v_ = graph.getVertexPointer(curr);

                        //TO DO: parallel
                        long oSize = v_->getOutDegree();
                       // #pragma omp for nowait
                        for(long ngh = 0; ngh < oSize; ngh++)
                        //for(auto ngh = v_->getOutNeighboursBegin(); ngh < v_->getOutNeighboursEnd(); ngh++)
                        {   
                                if(C(v_->getOutNeighboursEl(ngh)) && F(curr, v_->getOutNeighboursEl(ngh)))
                                {
                                    #pragma omp critical
                                    Out.addVertex(v_->getOutNeighboursEl(ngh));
                                }  
                            

                        }
                        
                }
            
        }
        

    
    //std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    //Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());
    //RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}

//To Do: Does it need to iterate from i = 1...|V| or can we do it in the way it is stored in the map


VertexSubset Interface::EdgeMapDense(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out;
    //TO DO: Parallel
    for(long i = 0; i < graph.getNumberVertices(); i++)
    {
        Vertex* v = graph.getVertexPointer(i);
        if (C(i) == 1)
            for(auto ngh = v->getInNeighboursBegin(); ngh < v->getInNeighboursEnd(); ngh++)
            {
                if(std::find(U.getVertexSubsetBegin(), U.getVertexSubsetEnd(), *ngh) != U.getVertexSubsetEnd() && F(*ngh, i))
                    Out.addVertex(i);
                if(C(i) == 0)
                    break;

            }
    }
    return Out;
    
}

VertexSubset Interface::EdgeMapDenseWrite(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out;
    // TO DO: parallel
    for(long i = 0; i < graph.getNumberVertices(); i++)
    {

        if(std::find(U.getVertexSubsetBegin(), U.getVertexSubsetEnd(), i) != U.getVertexSubsetEnd())
        {
            //TO DO: parallel
            Vertex* v = graph.getVertexPointer(i);
            for(auto ngh = v->getOutNeighboursBegin(); ngh < v->getOutNeighboursEnd(); ngh++)
            {
                if(C(*ngh) && F(i, *ngh))
                    Out.addVertex(*ngh);
            }
        }
    }
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());    
    return Out;
}

VertexSubset Interface::VertexMap(const VertexSubset &U,
                                  const std::function<bool(long vertexIndex)> &F)
{
    VertexSubset Out;
    //TO DO: parallel: Method 1: without critical section
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            for(auto v = U.getVertexSubsetBegin(); v < U.getVertexSubsetEnd(); v++)
            {
                #pragma omp task
                {
                    if(F(*v))
                        Out.addVertex(*v);
                }

            }
        }

    }

    //std::cout<<std::endl;
    return Out;
}   
//
//  Graph.h
//  Graph
//
//  Created by Justin Luna on 11/30/15.
//  Copyright © 2015 Justin Luna. All rights reserved.
//
#include <iostream>

#include "SafeArray.h"

using namespace std;
template <class T>

class Graph
{
    
public:
    Graph();
    ~Graph();
    void addVertex(T& v);
    void setEdge(T& from, T& to, int weight);
    void topSort(); //top sort only works when there are no cycles in the Graph
    int size();
    bool isEmpty();
    //bool getEdge(const T& fromVertex, const T& toVertex);
    int getEdgeWeight(const T& fromVertex, const T& toVertex);
    SafeArray < T* > getIncomingNeighbors(const T& vertex);
    SafeArray < T*> getOutgoingNeighbors(const T& vertex);
    void print(); //print each vertex and all of its incoming and outgoing neighbors
    void printRoutingTable(); //print the total weight and next hop to get to each vertex
    
private:
    SafeArray<SafeArray<int>> adjList;
    SafeArray<T> vertices;
    SafeArray<T> getNeighbors(const T &vertex, int placeHolder);
    
};

template < class T >
Graph <T>::Graph()
{
    //setting each value in the 2-Dimensional array to 0
    for(int i = 0; i < adjList.size(); i++)
    {
        for (int j = 0; j < adjList[i].size(); j++)
        {
            adjList[i][j] = 0;
        }
    }
}
template<class T>
Graph<T>::~Graph()
{

}
template < class T >
void Graph < T >::addVertex(T &v)
{
    vertices.push_back(v);
}
template < class T >
void Graph < T >::setEdge(T &from, T &to, int weight)
{
    int locationFrom = -1;
    int locationTo = -1;
    
    //finding the place with that value
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == from)
        {
            locationFrom = i;
            break;
        }
    }
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == to)
        {
            locationTo = i;
            
            break;
        }
    }
    
    //check to see that location was found
    if (locationFrom == -1 || locationTo == -1)
    {
        cout << "Location not found" << endl;
        exit(0);
    }
    
    adjList[locationFrom][locationTo] = weight;
}
template < class T >
void Graph < T >::topSort()
{
    //top sort algorithm -
    //1. pick a course that has no incoming edges in which there are 2
    //2. erase all the edges
    //3. store the label
    
    SafeArray<SafeArray<int>> adjList2(adjList.size());
    
    for (int i = 0; i < adjList2.size(); i++)
    {
        adjList2[i].resize(adjList[i].size());
    }
    
    //copy info
    for (int i = 0; i < adjList2.size(); i++)
    {
        for(int j = 0; j < adjList2[i].size(); j++)
        {
            adjList2[i][j] = adjList[i][j];
        }
    }
    
    SafeArray<T> topSort;
    
    while (topSort.size() < vertices.size())
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (getIncomingNeighbors(vertices[i]).size() == 0)
            {
                topSort.push_back(vertices[i]);
                
                for (int j = 0; j < adjList[i].size(); j++)
                {
                    adjList[i][j] = 0;
                }
                
                adjList[i][i] = -1;
            }
        }
    }
    
    for (int i = 0; i < adjList.size(); i++)
    {
        adjList[i].resize(adjList2[i].size());
    }
    
    //copy info over
    for (int i = 0; i < adjList.size(); i++)
    {
        for(int j = 0; j < adjList[i].size(); j++)
        {
            adjList[i][j] = adjList2[i][j];
        }
    }
    // trying to find the path through the actual Graph
    cout << "Finding a path through Graph: " << endl;
    
    topSort.printSafeArray();
    /*for(int i = 0; i < vertices.size();i++)
    {
        cout<< " " << topSort[i] << " " << endl;
    }*/
}
template < class T >
int Graph< T >::size()
{
    return vertices.size();
}

template < class T >
bool Graph< T >::isEmpty()
{
    return(vertices.size() == 0);
}
/*template<class T>
bool Graph<T>::getEdge(const T& fromVertex, const T& toVertex)
{
    int locationFromVertex;
    int locationToVertex;
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == fromVertex)
        {
            locationFromVertex = i;
            break;
        }
    }
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == toVertex)
        {
            locationToVertex = i;
            break;
        }
    }

    
    if(isEmpty() == false)
    {
        if(vertices[locationFromVertex][locationToVertex] > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
}*/
template < class T >
int Graph< T >::getEdgeWeight(const T &fromVertex, const T &toVertex)
{
    int locationFromVertex;
    int locationToVertex;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == fromVertex)
        {
            locationFromVertex = i;
            break;
        }
    }
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == toVertex)
        {
            locationToVertex = i;
            break;
        }
    }
    return adjList[locationFromVertex][locationToVertex];
}
template < class T >
SafeArray<T*> Graph< T >::getIncomingNeighbors(const T &vertex)
{
    SafeArray<T*> incomingNeighbors;
    
    int location;
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == vertex)
        {
            location = i;
            break;
        }
    }
    
    for (int i = 0; i < adjList[location].size(); i++)
    {
        //INCOMING
        if (adjList[i][location] != 0)
        {
            incomingNeighbors.push_back(&vertices[i]);
        }
    }
  
    
    return incomingNeighbors;
}
template < class T >
SafeArray<T*> Graph<T>::getOutgoingNeighbors(const T &vertex)
{
    SafeArray<T*> outGoingNeighbors;
    
    int location;
    
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == vertex)
        {
            location = i;
            break;
        }
    }
    
    for (int i = 0; i < adjList[location].size(); i++)
    {
        //OUTGOING
        if (adjList[location][i] != 0)
        {
            outGoingNeighbors.push_back(&vertices[i]);
        }
    }
    
    return outGoingNeighbors;
}
template < class T >
void Graph < T >::print()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        //use this with our size
        cout << "*********************************" << endl;
        
        cout << vertices[i] << " : " << endl;
        
        //printing incoming neighbors
        cout << "Incoming Neighbors:" << endl;
        
        /*SafeArray<T> incoming(getIncomingNeighbors(vertices[i]));
        SafeArray<T> outcoming(getOutgoingNeighbors(vertices[i]));
        
        if(incoming.isEmpty() == false)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                cout << " " << incoming(vertices[j]);
            }
        }*/
        getIncomingNeighbors(vertices[i]).printSafeArray();
        
        //printing outgoing neighbors
        cout << "Outgoing Neighbors:" << endl;
        
        /*if(outcoming(vertices[i]) == false)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                cout << " " << outcoming(vertices[j]);
            }
        }*/
        
        getOutgoingNeighbors(vertices[i]).printSafeArray();

    
        cout << "*********************************" << endl;
    }
}
template < class T >
void Graph< T >::printRoutingTable()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i] << " to: " << endl;
        
        
        bool isChanged = true;
        int* weights = new int (vertices.size());
        int* nextHop = new int (vertices.size());
        
        for (int j = 0; j < vertices.size(); j++)
        {
            weights[j] = adjList[i][j];
        }
        
        for (int j = 0; j < vertices.size(); j++)
        {
            nextHop[j] = -1;
            
            if(adjList[i][j] > 0)
            {
                nextHop[j] = j;
            }
        }
        
        while (isChanged)
        {
            isChanged = false;
            for (int l = 0; l < vertices.size(); l++)
            {
                for (int j = 0; j < vertices.size(); j++)
                {
                    if (adjList[j][i] > 0)
                    {
                        for (int k = 0; k < vertices.size(); k++)
                        {
                            if(adjList[l][k] > 0)
                            {
                                if (adjList[j][l] + adjList[l][k] < weights[k] || weights[k] == 0)
                                {
                                    weights[k] = adjList[j][k] + adjList[l][k];
                                    
                                    
                                    // here is is change
                                    isChanged = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        for (int s = 0; s < vertices.size(); s++)
        {
            if (nextHop[s] > -1)
            {
                cout << vertices[s] << " " << "Total weight: " << vertices[weights[s]] << " ";
                cout << weights[s] << " " << " Next Hop: " << vertices[nextHop[s]] << " " << endl;
            }
        }
        cout << endl;
        
        delete [] weights;
        delete [] nextHop;
    }
}

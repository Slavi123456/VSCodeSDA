#include <vector>
#include <map>
#include <iostream>

class DfsTraversalCollection
{
    enum class TypeEdge
    {
        Tree,
        Back,
        Forward,
        Cross
    };
    enum class NodeType
    {
        Finished,
        Untraveled,
        Traveled,
    };
    unsigned int begNode;
    std::vector<std::vector<int>> graph;

    std::map<std::pair<int, int>, TypeEdge> edgeMap;
    std::vector<int> dfsNodes;

    std::vector<unsigned> timeOfTraversed;
    int count = 0;

    void dfsHelper(unsigned currNode, std::vector<NodeType> &stateNode)
    {
        dfsNodes.push_back(currNode);
        stateNode[currNode] = NodeType::Traveled;
        timeOfTraversed[currNode] = count;
        count++;

        for (int el : graph[currNode])
        {
            if (stateNode[el] == NodeType::Untraveled)
            {
                edgeMap[{currNode, el}] = TypeEdge::Tree;
                dfsHelper(el, stateNode);
            }
            else if (stateNode[el] == NodeType::Traveled)
            {
                edgeMap[{currNode, el}] = TypeEdge::Back;
            }
            else if (stateNode[el] == NodeType::Finished)
            {
                if (timeOfTraversed[currNode] < timeOfTraversed[el])
                    edgeMap[{currNode, el}] = TypeEdge::Forward;
                else
                    edgeMap[{currNode, el}] = TypeEdge::Cross;
            }
        }
        stateNode[currNode] = NodeType::Finished;
    }
    void dfsTraversal()
    {
        std::vector<NodeType> stateNode(graph.size(), NodeType::Untraveled);
        dfsHelper(begNode, stateNode); // what happens when the graph have disconnected nodes
    }

public:
    DfsTraversalCollection(std::vector<std::vector<int>> &graph, unsigned int begNode)
    {
        this->graph = graph;
        this->begNode = begNode;
        timeOfTraversed.resize(graph.size(), -1);
        dfsTraversal();
    }
    DfsTraversalCollection(const DfsTraversalCollection &other) = delete;
    DfsTraversalCollection(DfsTraversalCollection &&other) = delete;
    DfsTraversalCollection operator==(const DfsTraversalCollection &other) = delete;
    DfsTraversalCollection operator==(DfsTraversalCollection &&other) = delete;

    void print()
    {
        std::cout << "{ ";
        for (int el : dfsNodes)
        {
            std::cout << el << " ";
        }
        std::cout << "}" << std::endl;

        for (const std::pair<std::pair<int, int>, TypeEdge> edge : edgeMap)
        {
            std::cout << edge.first.first << " --> " << edge.first.second << " : " << (int)edge.second << std::endl;
        }
    }
    std::vector<std::pair<int, int>> crossEdge()
    {
        std::vector<std::pair<int, int>> result;
        for (const std::pair<std::pair<int, int>, TypeEdge> edge : edgeMap)
        {
            if (edge.second == TypeEdge::Cross)
                result.push_back(edge.first);
        }
        std::cout << std::endl
                  << "Cross edge";
        for (std::pair<int, int> edge : result)
        {
            std::cout << edge.first << " --> " << edge.second << std::endl;
        }
        return result;
    }
    std::vector<std::pair<int, int>> forwardEdge()
    {
        std::vector<std::pair<int, int>> result;
        for (const std::pair<std::pair<int, int>, TypeEdge> edge : edgeMap)
        {
            if (edge.second == TypeEdge::Forward)
                result.push_back(edge.first);
        }
        std::cout << std::endl
                  << "Forward edge";

        for (std::pair<int, int> edge : result)
        {
            std::cout << edge.first << " --> " << edge.second << std::endl;
        }
        return result;
    }
    std::vector<std::pair<int, int>> backEdge()
    {
        std::vector<std::pair<int, int>> result;
        for (const std::pair<std::pair<int, int>, TypeEdge> edge : edgeMap)
        {
            if (edge.second == TypeEdge::Back)
                result.push_back(edge.first);
        }
        std::cout << std::endl
                  << "Back edge";
        for (std::pair<int, int> edge : result)
        {
            std::cout << edge.first << " --> " << edge.second << std::endl;
        }
        return result;
    }
    std::vector<std::pair<int, int>> treeEdge()
    {
        std::vector<std::pair<int, int>> result;
        for (const std::pair<std::pair<int, int>, TypeEdge> edge : edgeMap)
        {
            if (edge.second == TypeEdge::Tree)
                result.push_back(edge.first);
        }

        std::cout << std::endl
                  << "Tree edge";
        for (std::pair<int, int> edge : result)
        {
            std::cout << edge.first << " --> " << edge.second << std::endl;
        }
        return result;
    }

    class Iterator
    {
        friend DfsTraversalCollection;
        DfsTraversalCollection &dfsGraph;
        int *value;

    public:
        Iterator(DfsTraversalCollection &dfs, int *currEl = nullptr) : dfsGraph(dfs), value(currEl) {}
        int &operator*() { return *value; }
        int *operator->() { return value; }
        Iterator &operator++()
        {
            if (value)
            {
                value++;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator copy = *this;
            ++(*this);
            return copy;
        }
        Iterator &operator--(int)
        {
            if (value)
            {
                value--;
            }
            return *this;
        }
        Iterator operator--()
        {
            Iterator copy(*this);
            --(*this);
            return copy;
        }

        bool operator==(const Iterator &rhs) { return value == rhs.value; }
        bool operator!=(const Iterator &rhs) { return !(value == rhs.value); }
    };

    Iterator begin()
    {
        return Iterator(*this, dfsNodes.data());
    }
    Iterator end()
    {
        return Iterator(*this, dfsNodes.data() + dfsNodes.size());
    }
};
std::ostream &operator<<(std::ostream &os, DfsTraversalCollection &output)
{
    os << "{ ";
    for (int el : output)
    {
        os << el << " ";
    }
    os << "}";
    return os;
}
bool operator<(DfsTraversalCollection &lhs, DfsTraversalCollection &rhs)
{
    DfsTraversalCollection::Iterator lhsIt = lhs.begin();
    DfsTraversalCollection::Iterator rhsIt = rhs.begin();

    while (lhsIt != lhs.end() && rhsIt != rhs.end())
    {
        if (*lhsIt < *rhsIt)
            return true;
        else if (*lhsIt > *rhsIt)
            return false;
        ++lhsIt;
        ++rhsIt;
    }
    if (lhsIt == lhs.end() && rhsIt == rhs.end())
        return true;
    else if (rhsIt == rhs.end())
        return false;
    else if (lhsIt == lhs.end())
        return true;
}
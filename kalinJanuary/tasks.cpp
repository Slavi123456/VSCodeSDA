#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>

using WGraph = std::unordered_map<int, std::map<int, std::string>>;

void allWordsHelper(int currNode, int endNode, WGraph &wGraph, std::vector<std::string> &res, std::string &currWord, std::vector<bool> &traveled)
{
    if (currNode == endNode)
    {
        res.push_back(currWord);
        return;
    }
    traveled[currNode] = true;
    for (const auto &edge : wGraph[currNode])
    {
        int V = edge.first;
        std::string word = edge.second;
        if (!traveled[V])
        {
            for (char ch : word)
            {
                currWord.push_back(ch);
                allWordsHelper(V, endNode, wGraph, res, currWord, traveled);
                currWord.pop_back();
            }
        }
    }
    traveled[currNode] = false;
}
void allWordsWithSize(int currNode, int wantedSize, WGraph &wGraph, std::vector<std::string> &res, std::string &currWord)
{
    if (currWord.size() >= wantedSize)
    {
        res.push_back(currWord);
        return;
    }
    for (const auto &edge : wGraph[currNode])
    {
        int V = edge.first;
        std::string word = edge.second;
        for (char ch : word)
        {
            currWord.push_back(ch);
            allWordsWithSize(V, wantedSize, wGraph, res, currWord);
            currWord.pop_back();
        }
    }
}
std::vector<std::string> allWords(WGraph &wgraph)
{
    std::vector<bool> traveled(wgraph.size(), false);
    std::string currWord = "";
    std::vector<std::string> allWords;
    // allWordsHelper(0, 4, wgraph, allWords, currWord, traveled);
    allWordsWithSize(0, 4, wgraph, allWords, currWord);
    return allWords;
}

int smallestCycle(WGraph &wGraph) //word that can be made by the smalles cycle //it is used map for saving the path 
{
    std::vector<bool> traveled(wGraph.size(), false);
    int sizeCycle = 0;
    std::queue<int> que;
    que.push(0);
    traveled[0] = true;

    while (!que.empty())
    {
        for (int i = 0; i < que.size(); i++)
        {
            int currNode = que.front();
            que.pop();
            for (const auto &edge : wGraph[currNode])
            {
                int V = edge.first;
                if (traveled[V])
                {
                    return sizeCycle;
                }
                traveled[V] = true;
                que.push(V);
            }
        }
        sizeCycle++;
    }
    return -1;
}

int main()
{
    WGraph graph;
    graph[0] = {{1, "ab"}, {2, "cd"}};
    graph[1] = {{0, "ef"}};
    graph[2] = {{3, "gh"}};
    graph[3] = {{4, "ij"}};
    graph[4] = {};

    std::vector<std::string> result = allWords(graph);
    //std::cout << smallestCycle(graph) << std::endl;
    for (const std::string &word : result)
    {
        std::cout << word << "\n";
    }

    return 0;
}
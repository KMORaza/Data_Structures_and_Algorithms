#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
class TarjanSCC {
public:
    TarjanSCC(int vertices) : numVertices(vertices), index(0) {
        adjList.resize(vertices);
        inStack.resize(vertices, false);
        lowLink.resize(vertices, -1);
        indexInStack.resize(vertices, -1);
    }
    void addEdge(int from, int to) {
        adjList[from].push_back(to);
    }
    void findSCCs() {
        for (int i = 0; i < numVertices; ++i) {
            if (indexInStack[i] == -1) {
                dfs(i);
            }
        }
    }
    void printSCCs() {
        std::cout << "Strongly Connected Components:" << std::endl;
        for (const auto& scc : stronglyConnectedComponents) {
            for (int vertex : scc) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    int numVertices;
    std::vector<std::vector<int>> adjList;
    std::vector<bool> inStack;
    std::vector<int> lowLink;
    std::vector<int> indexInStack;
    std::vector<std::vector<int>> stronglyConnectedComponents;
    std::stack<int> dfsStack;
    int index;
    void dfs(int vertex) {
        indexInStack[vertex] = index;
        lowLink[vertex] = index;
        index++;
        dfsStack.push(vertex);
        inStack[vertex] = true;
        for (int neighbor : adjList[vertex]) {
            if (indexInStack[neighbor] == -1) {
                dfs(neighbor);
                lowLink[vertex] = std::min(lowLink[vertex], lowLink[neighbor]);
            } else if (inStack[neighbor]) {
                lowLink[vertex] = std::min(lowLink[vertex], indexInStack[neighbor]);
            }
        }
        if (lowLink[vertex] == indexInStack[vertex]) {
            std::vector<int> scc;
            int top;
            do {
                top = dfsStack.top();
                dfsStack.pop();
                inStack[top] = false;
                scc.push_back(top);
            } while (top != vertex);
            stronglyConnectedComponents.push_back(scc);
        }
    }
};
int main() {
    TarjanSCC tarjan(7);
    tarjan.addEdge(0, 1);
    tarjan.addEdge(1, 2);
    tarjan.addEdge(1, 3);
    tarjan.addEdge(3, 4);
    tarjan.addEdge(4, 5);
    tarjan.addEdge(5, 3);
    tarjan.addEdge(6, 0);
    tarjan.addEdge(6, 5);
    tarjan.findSCCs();
    tarjan.printSCCs();
    return 0;
}

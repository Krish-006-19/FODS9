#include <iostream>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

#define MAX_VERTICES 100

int get_integer_input() {
    int num;
    while (true) {
        cin >> num;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num;
        }
    }
}

class Graph {
private:
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

public:
    Graph() {
        numVertices = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
            for (int j = 0; j < MAX_VERTICES; j++)
                adjMatrix[i][j] = 0;
    }

    void createGraph() {
        cout << "Enter number of vertices (max " << MAX_VERTICES << "): ";
        numVertices = get_integer_input();
        if (numVertices <= 0 || numVertices > MAX_VERTICES) {
            cout << "Invalid number of vertices.\n";
            numVertices = 0;
            return;
        }

        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = 0;

        cout << "Enter number of edges: ";
        int numEdges = get_integer_input();

        cout << "Enter edges as pairs (u v):\n";
        for (int i = 0; i < numEdges; i++) {
            int u, v;
            cout << "Edge " << i + 1 << ": ";
            cin >> u >> v;
            if (u < 0 || v < 0 || u >= numVertices || v >= numVertices || u == v) {
                cout << "Invalid edge! Try again.\n";
                i--;
            } else {
                adjMatrix[u][v] = 1;
                adjMatrix[v][u] = 1;
            }
        }

        cout << "Graph created successfully.\n";
    }

    void displayMatrix() const {
        if (numVertices == 0) {
            cout << "Graph not created yet.\n";
            return;
        }

        cout << "\nAdjacency Matrix:\n   ";
        for (int i = 0; i < numVertices; i++)
            cout << i << " ";
        cout << "\n  ";
        for (int i = 0; i < numVertices; i++)
            cout << "--";
        cout << "\n";

        for (int i = 0; i < numVertices; i++) {
            cout << i << "| ";
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    void addVertex() {
        if (numVertices >= MAX_VERTICES) {
            cout << "Maximum vertex limit reached.\n";
            return;
        }

        for (int i = 0; i <= numVertices; i++) {
            adjMatrix[i][numVertices] = 0;
            adjMatrix[numVertices][i] = 0;
        }
        numVertices++;
        cout << "Vertex " << numVertices - 1 << " added.\n";
    }

    void addEdge() {
        int u, v;
        cout << "Enter first vertex: ";
        u = get_integer_input();
        cout << "Enter second vertex: ";
        v = get_integer_input();

        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices || u == v) {
            cout << "Invalid vertices.\n";
            return;
        }

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
        cout << "Edge added between " << u << " and " << v << ".\n";
    }

    void deleteVertex() {
        if (numVertices == 0) {
            cout << "No vertices to delete.\n";
            return;
        }

        cout << "Enter vertex to delete (0–" << numVertices - 1 << "): ";
        int k = get_integer_input();
        if (k < 0 || k >= numVertices) {
            cout << "Invalid vertex.\n";
            return;
        }

        for (int i = k; i < numVertices - 1; i++)
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = adjMatrix[i + 1][j];

        for (int j = k; j < numVertices - 1; j++)
            for (int i = 0; i < numVertices; i++)
                adjMatrix[i][j] = adjMatrix[i][j + 1];

        numVertices--;
        cout << "Vertex " << k << " deleted. Remaining vertices reindexed.\n";
    }

    void deleteEdge() {
        int u, v;
        cout << "Enter first vertex: ";
        u = get_integer_input();
        cout << "Enter second vertex: ";
        v = get_integer_input();

        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            cout << "Invalid vertices.\n";
            return;
        }

        if (adjMatrix[u][v] == 0) {
            cout << "Edge does not exist.\n";
        } else {
            adjMatrix[u][v] = 0;
            adjMatrix[v][u] = 0;
            cout << "Edge deleted between " << u << " and " << v << ".\n";
        }
    }

    void DFS(int start) {
        if (start < 0 || start >= numVertices) {
            cout << "Invalid starting vertex.\n";
            return;
        }

        bool visited[MAX_VERTICES] = {false};
        stack<int> s;
        s.push(start);

        cout << "DFS Traversal: ";
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
                for (int i = numVertices - 1; i >= 0; i--)
                    if (adjMatrix[v][i] && !visited[i])
                        s.push(i);
            }
        }
        cout << "\n";
    }

    void BFS(int start) {
        if (start < 0 || start >= numVertices) {
            cout << "Invalid starting vertex.\n";
            return;
        }

        bool visited[MAX_VERTICES] = {false};
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[v][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << "\n";
    }

    int getNumVertices() const { return numVertices; }
};

int main() {
    Graph g;
    int choice;

    while (true) {
        cout << "\n--- Graph Menu ---\n"
             << "1. Create Graph\n"
             << "2. Display Matrix\n"
             << "3. Add Vertex\n"
             << "4. Add Edge\n"
             << "5. Delete Vertex\n"
             << "6. Delete Edge\n"
             << "7. DFS Traversal\n"
             << "8. BFS Traversal\n"
             << "9. Exit\n"
             << "Enter choice: ";

        choice = get_integer_input();

        switch (choice) {
            case 1: g.createGraph(); break;
            case 2: g.displayMatrix(); break;
            case 3: g.addVertex(); break;
            case 4: g.addEdge(); break;
            case 5: g.deleteVertex(); break;
            case 6: g.deleteEdge(); break;
            case 7:
                cout << "Enter start vertex for DFS: ";
                g.DFS(get_integer_input());
                break;
            case 8:
                cout << "Enter start vertex for BFS: ";
                g.BFS(get_integer_input());
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

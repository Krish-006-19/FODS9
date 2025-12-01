#include <iostream>
#include <limits>
using namespace std;

#define MAX 10

int adj[MAX][MAX];   
int visited[MAX];    
int vertexCount = 0;

class Stack {
public:
    int items[MAX];
    int top;

    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }

    void push(int value) {
        if (top == MAX - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        items[++top] = value;
    }

    int pop() {
        if (isEmpty()) return -1;
        return items[top--];
    }
};

class Queue {
public:
    int items[MAX];
    int front, rear;

    Queue() {
        front = rear = 0;
    }

    bool isEmpty() {
        return front == rear;
    }

    void enqueue(int value) {
        if (rear == MAX) {
            cout << "Queue Overflow!\n";
            return;
        }
        items[rear++] = value;
    }

    int dequeue() {
        if (isEmpty()) return -1;
        return items[front++];
    }
};

void resetVisited() {
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;
}

int get_integer_input() {
    int value;
    while (true) {
        cin >> value;
        if (!cin.fail()) {
            return value;
        }
        cout << "Invalid input! Please enter a whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void addVertex() {
    if (vertexCount == MAX) {
        cout << "Maximum vertices reached!\n";
        return;
    }

    vertexCount++;
    cout << "Vertex " << vertexCount - 1 << " added.\n";
}

void addEdge(int src, int dest) {
    if (src >= vertexCount || dest >= vertexCount) {
        cout << "Invalid vertex number\n";
        return;
    }

    adj[src][dest] = 1;
    adj[dest][src] = 1;

    cout << "Edge " << src << " -- " << dest << " added\n";
}

void displayGraph() {
    cout << "\nAdjacency Matrix:\n  ";

    for (int i = 0; i < vertexCount; i++)
        cout << i << " ";
    cout << "\n";

    for (int i = 0; i < vertexCount; i++) {
        cout << i << " ";
        for (int j = 0; j < vertexCount; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
}

void DFS(int start) {
    if (start >= vertexCount) {
        cout << "Invalid starting vertex\n";
        return;
    }

    Stack s;
    resetVisited();

    cout << "DFS: ";
    s.push(start);

    while (!s.isEmpty()) {
        int v = s.pop();

        if (!visited[v]) {
            visited[v] = 1;
            cout << v << " ";

            for (int i = 0; i < vertexCount; i++) {
                if (adj[v][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }

    cout << "\n";
}

void BFS(int start) {
    if (start >= vertexCount) {
        cout << "Invalid starting vertex\n";
        return;
    }

    Queue q;
    resetVisited();

    cout << "BFS: ";
    q.enqueue(start);
    visited[start] = 1;

    while (!q.isEmpty()) {
        int v = q.dequeue();
        cout << v << " ";

        for (int i = 0; i < vertexCount; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                q.enqueue(i);
                visited[i] = 1;
            }
        }
    }

    cout << "\n";
}

int main() {
    int choice, src, dest, start;

    while (true) {
        cout << "\n===== GRAPH MENU =====\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Display Graph (Matrix)\n";
        cout << "4. DFS (Iterative)\n";
        cout << "5. BFS\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        choice = get_integer_input();

        switch (choice) {
            case 1:
                addVertex();
                break;

            case 2:
                cout << "Enter source vertex: ";
                src = get_integer_input();

                cout << "Enter destination vertex: ";
                dest = get_integer_input();

                addEdge(src, dest);
                break;

            case 3:
                displayGraph();
                break;

            case 4:
                cout << "Enter starting vertex for DFS: ";
                start = get_integer_input();
                DFS(start);
                break;

            case 5:
                cout << "Enter starting vertex for BFS: ";
                start = get_integer_input();
                BFS(start);
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

#include <iostream>
using namespace std;

// Node structure for the queue
struct QueueNode {
    int data;
    QueueNode* next;
};

// Queue implementation
struct Queue {
    QueueNode* front;
    QueueNode* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int value) {
        QueueNode* newNode = new QueueNode{value, nullptr};
        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = rear;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int value = front->data;
        QueueNode* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        return value;
    }
};

// Graph representation using adjacency matrix
class Graph {
    int vertices;
    int** adjMatrix;

public:
    Graph(int v) : vertices(v) {
        adjMatrix = new int*[v];
        for (int i = 0; i < v; i++) {
            adjMatrix[i] = new int[v];
            for (int j = 0; j < v; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For an undirected graph
    }

    void bfs(int start) {
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }

        Queue q;
        visited[start] = true;
        q.enqueue(start);

        cout << "BFS Traversal: ";
        while (!q.isEmpty()) {
            int node = q.dequeue();
            cout << node << " ";

            // Enqueue all unvisited neighbors
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.enqueue(i);
                }
            }
        }

        delete[] visited;
    }

    ~Graph() {
        for (int i = 0; i < vertices; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

int main() {
    int vertices = 6;
    Graph g(vertices);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Perform BFS starting from node 0
    g.bfs(0);

    return 0;
}

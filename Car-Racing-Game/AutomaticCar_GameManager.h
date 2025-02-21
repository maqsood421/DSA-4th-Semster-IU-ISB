#ifndef AUTOMATICCAR_GAMEMANAGER_H
#define AUTOMATICCAR_GAMEMANAGER_H


#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include "Stack.h"
#include "PriorityQueue.h"
#include "Objects_Manager.h"
#include "Queue.h"
#include "BFSQueue.h"
using namespace std;
// #pragma comment(lib, "winmm.lib")

int main();
void PathNodesPrint();

struct AutoCarGraphNode
{
    string name;
    int vertex;
    int* edges;
    int* weights;
    int edgeCount;
};

class AutoCarGraph
{
private:
    AutoCarGraphNode* adjList;
    Queue<Object*> objectQueue;
    int vertexCount;
    int score = 0;
    int objectCount = 0;

public:
    AutoCarGraph(int V) : vertexCount(V)
    {
        adjList = new AutoCarGraphNode[V * V];
        for (int i = 0; i < V * V; ++i)
        {
            if (i == 0)
            {
                adjList[i].name = "<\033[32m|S|\033[35m>";
            }
            else if (i == V * V - 1)
            {
                adjList[i].name = "<\033[32m|E|\033[35m>";
            }
            else
            {
                adjList[i].name = "<<+>>";
            }
            adjList[i].vertex = i;
            adjList[i].edges = new int[V * V];
            adjList[i].weights = new int[V * V];
            adjList[i].edgeCount = 0;
        }
    }

    void addEdge(int x1, int y1, int x2, int y2, int weight)
    {
        if (x1 < 0 || x1 >= vertexCount || y1 < 0 || y1 >= vertexCount || x2 < 0 || x2 >= vertexCount || y2 < 0 || y2 >= vertexCount)
        {
            cout << "Invalid edge!\n";
            return;
        }

        int v = x1 * vertexCount + y1;
        int w = x2 * vertexCount + y2;

        adjList[v].edges[adjList[v].edgeCount] = w;
        adjList[v].weights[adjList[v].edgeCount] = weight;
        adjList[v].edgeCount++;

        adjList[w].edges[adjList[w].edgeCount] = v;
        adjList[w].weights[adjList[w].edgeCount] = weight;
        adjList[w].edgeCount++;
    }

    void updateWeights(int x, int y, int weight)
    {
        if (x < 0 || x >= vertexCount || y < 0 || y >= vertexCount)
        {
            cout << "Invalid edge!\n";
            return;
        }

        int v = x * vertexCount + y;
        for (int i = 0; i < adjList[v].edgeCount; ++i)
        {
            adjList[v].weights[i] = weight;
        }
    }

    void addObject(Object* obj)
    {
        if (objectCount >= vertexCount * vertexCount - 2)
        {
            // The grid is full, so don't try to add more objects
            return;
        }

        int pos;
        do
        {
            pos = rand() % (vertexCount * vertexCount);
        } while (pos == 0 || pos == vertexCount * vertexCount - 1 || adjList[pos].name != "<<+>>");

        objectQueue.Push(obj);
        adjList[pos].name = obj->Create_Object();
        objectQueue.Pop();
        objectCount++;
    }

    void makeGrid(int n)
    {
        srand(time(0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (rand() % 10 < 6.5) // 65% chance to add a horizontal edge
                {
                    if (j < n - 1) // Don't add a horizontal edge for the last column
                    {
                        addEdge(i, j, i, j + 1, 10); // Random weight between 1 and 10
                    }
                }
                if (rand() % 10 < 6.5) // 65% chance to add a vertical edge
                {
                    if (i < n - 1) // Don't add a vertical edge for the last row
                    {
                        addEdge(i, j, i + 1, j, 10); // Random weight between 1 and 10
                    }
                }
            }
        }
        Object_Factory factory;
        for (int i = 0; i < ((n * n) / 3); ++i)
        {
            int decide = rand() % 3 + 1;
            addObject(factory.Create_Object(decide)); // Add a random object to the grid
            if (adjList[i].edgeCount == 0)
            {
                int x = i / n;
                int y = i % n;
                if (decide == 1)
                {
                    updateWeights(x, y, 100);
                }
                else if (decide == 2)
                {
                    updateWeights(x, y, 5);
                }
                else if (decide == 3)
                {
                    updateWeights(x, y, 8);
                }

            }
        }
    }

    void car(int n)
    {
        if (n == 1)
        {
            cout << "\033[33m\\o=o>\033[0m";
        }
        if (n == 2)
        {
            cout << "\033[33mLo=o>\033[0m";
        }
        if (n == 3)
        {
            cout << "\033[33mCo=o>\033[0m";
        }
    }

    void SelectCar(int selectedOption)
    {
        const char* options[] = { "\\o=o>", "Lo=o>", "Co=o>" };
        const int numOptions = sizeof(options) / sizeof(options[0]);

        // Get the console size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Print the game name in the center
        PathNodesPrint(); cout << "\n\n";

        cout << string((width - 10) / 2, ' ') << "\033[34mSelect Your Car\033[0m" << endl;

        // Print the options in the center
        for (int i = 0; i < numOptions; ++i)
        {
            if (i == selectedOption)
            {
                cout << string((width - strlen(options[i])) / 2, ' ') << "\033[33m> " << options[i] << "\n\033[0m";
            }
            else
            {
                cout << string((width - strlen(options[i])) / 2, ' ') << "  " << options[i] << "\n";
            }
        }
    }

    void moveCar(int m)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int Scorewidth = csbi.srWindow.Right - (csbi.srWindow.Left / 2) + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int newlines = (height - vertexCount * 2) / 2;
    // Print the newlines
    cout << string(newlines, '\n');
    int selectCar = 0;
    int key, n;

    // PlaySound(TEXT("WhileGamming.wav"), NULL, SND_ASYNC | SND_LOOP);
    while (true)
    {
        system("cls");
        SelectCar(selectCar);
        key = _getch(); // Capture the arrow key input
        if (key == 72) selectCar = (selectCar - 1 + 3) % 3; // Up arrow key
        else if (key == 80) selectCar = (selectCar + 1) % 3; // Down arrow key
        else if (key == 13) break; // Enter key
    }
    if (selectCar == 0) { n = 1; }
    if (selectCar == 1) { n = 2; }
    if (selectCar == 2) { n = 3; }

    system("cls");

    AutoCarGraph g(m); // Create a graph with m*m vertices
    //makeGrid(m);

    system("cls");
    cout << string(newlines, '\n');
    cout << string((width - 33 ) / 2, ' ') << "\033[32mGive us the finishing line (xy): \033[0m";
    int endnode;
    cin >> endnode;

    adjList[m* m - 1].name = "<<+>>";
    adjList[endnode].name = "<\033[32m|E|\033[35m>";

    // Run BFS to ensure there's at least one path from start to end
    while (true)
    {
        makeGrid(m);
        if (bfs(0, endnode, m))
            break;
    }

    int* distances = new int[m * m];
    int* previous = new int[m * m];
    dijkstra(0, m * m - 1, distances, previous);

    // int start = 0; // starting node
    // int end = m * m - 1; // destination node
    // int* distances = new int[m * m];
    // int* previous = new int[m * m];
    // int** graph = autoGraph(m); // function to create your graph

    // AStar(start, end, distances, previous, graph, m * m, m);

    if (distances[m * m - 1] != INT_MAX)
    {
        moveCarAutomatically(0, endnode, previous, m, n);
        system("cls");
        cout << string(newlines, '\n');
        cout << string((Scorewidth - 8) / 2, ' ') << "\033[32mYou win!\033[0m" << endl;
        cout << string((Scorewidth - 33) / 2, ' ') << "Press ESC to return to main menu!" << endl;
        int key = _getch();
        if (key == 27)
        {
            system("cls");
            main();
        }
        else
        {
            cout << string(newlines, '\n');
            cout << string((Scorewidth - 33) / 2, ' ') << "\033[31mInvalid key! Returning to main manu automatically\033[0m" << endl;
            Sleep(2000);
            system("cls");
            main();
        }
    }
    else
    {
        cout << string(newlines, '\n');
        cout << string((Scorewidth - 33) / 2, ' ') << "No path found from start to end. Returning..." << endl;
        Sleep(2000);
        system("cls");
        main();
    }

    delete[] distances;
    delete[] previous;
    //deleteGraph(graph, m);
}

    void moveCarAutomatically(int start, int end, int* previous, int m, int n)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int Scorewidth = csbi.srWindow.Right - (csbi.srWindow.Left / 2) + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int newlines = (height - vertexCount * 2) / 2;
        // Print the newlines
        cout << string(newlines, '\n');
        // Use a stack to reverse the path from end to start
        Stack path;
        for (int node = end; node != start; node = previous[node])
        {
            path.push(node);
        }
        path.push(start); // Don't forget to add the start node

        // Move the car along the path
        auto start_time = chrono::high_resolution_clock::now();
        bool isPaused = false;
        while (!path.isEmpty())
        {
            if(_kbhit())
            {
                int ch = _getch();
                if (ch == 27) { // 27 is the ASCII value of the ESC key
                    if (isPaused)
                    {
                        cout << string((Scorewidth - 13) / 2, ' ') << "Game resumed!" << endl;
                    }
                    else
                    {
                        cout << endl << string((Scorewidth - 130) / 2, ' ') << string((50) / 2, ' ') << "\033[33mESC = Resume" << string((50) / 2, ' ') << "\033[34mGame paused!" << string((49) / 2, ' ') << "\033[31mR = Main Menu\033[0m" << endl;
                        int key = _getch();
                        if (key == 27)
                        {
                            isPaused = !isPaused;
                        }
                        else if (key == 114)
                        {
                            system("cls");
                            main();
                        }
                    }
                    isPaused = !isPaused;
                }
            }
            if (!isPaused)
            {
                int node = path.peek();
                path.pop();
                // start time
                this->printCar(m, node, n, start_time);
                Sleep(1000);
            }
        }
    }

    void dijkstra(int start, int end, int* distances, int* previous)
    {
        PriorityQueue queue(this->vertexCount * this->vertexCount);
        for (int i = 0; i < this->vertexCount * this->vertexCount; ++i)
        {
            if (i == start)
            {
                distances[i] = 0;
            }
            else
            {
                distances[i] = INT_MAX;
            }
            previous[i] = -1;
            queue.push(i, distances[i]);
        }
        while (!queue.empty())
        {
            int node = queue.pop();
            for (int i = 0; i < this->adjList[node].edgeCount; ++i)
            {
                int neighbor = this->adjList[node].edges[i];
                int altDist = distances[node] + this->adjList[node].weights[i];
                if (altDist < distances[neighbor])
                {
                    distances[neighbor] = altDist;
                    previous[neighbor] = node;
                    queue.push(neighbor, altDist);
                }
            }
        }
    }

    bool bfs(int source, int destination, int m)
    {
        bool* visited = new bool[m * m];
        for (int i = 0; i < m * m; i++) visited[i] = false;
        int n = m * m;
        BFSQueue q(n);
        q.push(source);
        visited[source] = true;
        while (!q.empty())
        {
            int u = q.peek();
            q.pop();
            if (u == destination)
            {
                delete[] visited;
                return true; // We found a path to the destination
            }
            for (int i = 0; i < adjList[u].edgeCount; i++)
            {
                int v = adjList[u].edges[i];
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        delete[] visited;
        return false; // No path found to the destination
    }

    /*
    int** autoGraph(int n)
    {
        int** graph = new int* [n * n];
        for (int i = 0; i < n * n; ++i)
        {
            graph[i] = new int[n * n];
            for (int j = 0; j < n * n; ++j)
            {
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < n * n; ++i)
        {
            for (int j = 0; j < adjList[i].edgeCount; ++j)
            {
                graph[i][adjList[i].edges[j]] = adjList[i].weights[j];
            }
        }
        return graph;
    }

    void deleteGraph(int** graph, int n)
    {
        for (int i = 0; i < n * n; ++i)
        {
            delete[] graph[i];
        }
        delete[] graph;
    }

         void AStar(int start, int end, int* distances, int* previous, int** graph, int numNodes, int m) {
         bool* closedSet = new bool[numNodes];
         bool* openSet = new bool[numNodes];
         int* gScore = new int[numNodes];
         int* fScore = new int[numNodes];

         for (int i = 0; i < numNodes; i++) {
             openSet[i] = false;
             closedSet[i] = false;
             gScore[i] = INT_MAX;
             fScore[i] = INT_MAX;
             previous[i] = -1;
         }

         openSet[start] = true;
         gScore[start] = 0;
         fScore[start] = heuristic(start, end, m);

         while (true) {
             int current = -1;
             for (int i = 0; i < numNodes; i++) {
                 if (openSet[i] && (current == -1 || fScore[i] < fScore[current])) {
                     current = i;
                 }
             }

             if (current == -1) {
                 break;
             }

             if (current == end) {
                 reconstructPath(previous, current);
                 break;
             }

             openSet[current] = false;
             closedSet[current] = true;

             for (int i = 0; i < numNodes; i++) {
                 if (graph[current][i] > 0 && !closedSet[i]) {
                     int tentativeGScore = gScore[current] + graph[current][i];
                     if (!openSet[i]) {
                         openSet[i] = true;
                     } else if (tentativeGScore >= gScore[i]) {
                         continue;
                     }

                     previous[i] = current;
                     gScore[i] = tentativeGScore;
                     fScore[i] = gScore[i] + heuristic(i, end, m); // Update fScore considering the heuristic
                 }
             }
         }

         delete[] closedSet;
         delete[] openSet;
         delete[] gScore;
         delete[] fScore;
     }

     int heuristic(int start, int end, int m) {
         // This is a simple heuristic that returns the Manhattan distance between the start node and the end node.
         // You may need to adjust this to match the specifics of your graph.
         int startX = start / m;
         int startY = start % m;
         int endX = end / m;
         int endY = end % m;
         return abs(startX - endX) + abs(startY - endY);
     }

     void reconstructPath(int* previous, int current) {
         // This function constructs the shortest path from the start node to the current node using the `previous` array.
         // The path is printed to the console, but you can modify this to suit your needs.
         int pathLength = 0;
         for (int i = current; i != -1; i = previous[i]) {
             pathLength++;
         }
         int* path = new int[pathLength];
         int index = pathLength - 1;
         for (int i = current; i != -1; i = previous[i]) {
             path[index] = i;
             index--;
         }
         for (int i = 0; i < pathLength; i++) {
             std::cout << path[i] << ' ';
         }
         std::cout << '\n';
         delete[] path;
     }*/

    void print(int n)
    {
        system("cls");
        for (int i = 0; i < vertexCount; ++i)
        {
            for (int j = 0; j < vertexCount; ++j)
            {
                int v = i * vertexCount + j;
                // cout << i << j;
                if (i == 0 && j == 0)
                {
                    cout << "\033[35m<\033[32m|S|\033[35m>\033[0m";
                    //cout << "\033[33mCo=o>\033[0m";
                }
                else if (i == n - 1 && j == n - 1)
                {
                    cout << "\033[35m<\033[32m|E|\033[35m>\033[0m";
                }
                else
                {
                    cout << "\033[35m<^-^>\033[0m";
                }
                if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + 1) != adjList[v].edges + adjList[v].edgeCount)
                {
                    cout << "\033[36m----\033[0m";
                }
                else
                {
                    cout << "    ";
                }
            }
            cout << endl;
            if (i < vertexCount - 1)
            {
                for (int j = 0; j < vertexCount; ++j)
                {
                    int v = i * vertexCount + j;
                    if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + vertexCount) != adjList[v].edges + adjList[v].edgeCount)
                    {
                        cout << "\033[36m  |      \033[0m";
                    }
                    else
                    {
                        cout << "         ";
                    }
                }
                cout << endl;
            }
        }
    }

    int printCar(int n, int carPos, int m, chrono::high_resolution_clock::time_point start_time)
    {
        system("cls");

        // Get the console size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int Scorewidth = csbi.srWindow.Right - (csbi.srWindow.Left / 2) + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int newlines = (height - vertexCount * 2) / 2;
        // Print the newlines
        cout << string(newlines, '\n');

        // Calculate the elapsed time
        auto current_time = chrono::high_resolution_clock::now();
        int elapsed_seconds = chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

        // Display the timer
        //cout << string((Scorewidth + 70) / 2, ' ') << "Timer: " << elapsed_seconds << "s" << endl;

        cout << string((Scorewidth) / 2, ' ') << elapsed_seconds << "sec" << string((65) / 2, ' ') << "Nodes: " << score << endl;

        for (int i = 0; i < vertexCount; ++i)
        {
            // Calculate the number of spaces needed to center the grid
            int spaces = (width - vertexCount * 8) / 2;
            // Print the spaces
            cout << string(spaces, ' ');

            for (int j = 0; j < vertexCount; ++j)
            {
                int v = i * vertexCount + j;
                if (v == carPos)
                {
                    if (adjList[v].name == "<<+>>")
                    {
                        adjList[v].name = "\033[32m<<+>>\033[0m";
                        score += 1;
                    }
                    car(m); // Print the car
                }
                else
                {
                    cout << "\033[35m" << adjList[v].name << "\033[0m";
                }
                if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + 1) != adjList[v].edges + adjList[v].edgeCount)
                {
                    cout << "\033[37m----\033[0m";
                }
                else
                {
                    cout << "    ";
                }
            }
            cout << endl;
            if (i < vertexCount - 1)
            {
                // Print the spaces
                cout << string(spaces, ' ');

                for (int j = 0; j < vertexCount; ++j)
                {
                    int v = i * vertexCount + j;
                    if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + vertexCount) != adjList[v].edges + adjList[v].edgeCount)
                    {
                        cout << "\033[37m  |      \033[0m";
                    }
                    else
                    {
                        cout << "         ";
                    }
                }
                cout << endl;
            }
        }

        return elapsed_seconds;
    }

    ~AutoCarGraph()
    {
        for (int i = 0; i < vertexCount * vertexCount; ++i)
        {
            delete[] adjList[i].edges;
            delete[] adjList[i].weights;
        }
        delete[] adjList;
    }
};

#endif
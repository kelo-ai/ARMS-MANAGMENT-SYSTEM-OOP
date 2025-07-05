#include<iostream>
#include<limits>
using namespace std;
const int MAX_NODES = 26;

class traffic {
public:
    // int signal=0; //if value is 1 =(True)=GREEN   if value is 0 =(False)= RED;//
    bool state;
    int greenduration;
    int redduration;
    int currentduration;
    traffic() {
        //   sig = signal;
        state = true;
        greenduration = 5;
        redduration = 5;
        currentduration = 0;
    }
    //    bool signalswitch() {
      //      state = !state;
        //    return state;
        //}
    bool isgreen() {
        return state;
    }
    void displaysignal() {
        if (state) {
            cout << "Signal is Green" << endl;
        }
        else {
            cout << "Signal is Red" << endl;
        }
    }
    void updatesignal() {
        currentduration++;
        if (state && currentduration >= greenduration) {
            state = false;
            currentduration = 0;

        }
        else if (!state && currentduration >= redduration) {

            state = true;
            currentduration = 0;


        }
    }
};
class vehicle {
public:
    int numofcar; //in the queue at trafic signal;//
    int postion;
    int destination;
};

bool isLocationOccupied(int location, int* grid, int gridSize) {
    for (int i = 0; i < gridSize * gridSize; i++) {
        if (location == grid[i]) {
            return true;
        }
    }
    return false;
}


// Queue data structure implementation
class Queue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() {
        return (rear == -1);
    }

    bool isFull() {
        return (rear == capacity - 1);
    }

    void enqueue(int item) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }
        arr[++rear] = item;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        int item = arr[front++];
        if (front > rear) {
            front = 0;
            rear = -1;
        }
        return item;
    }
};

// Dijkstra's algorithm to find shortest paths
void dijkstra(int start, int graph[MAX_NODES][MAX_NODES], int dist[MAX_NODES]) {
    bool visited[MAX_NODES] = { false };
    fill(dist, dist + MAX_NODES, numeric_limits<int>::max());
    dist[start] = 0;

    Queue pq(MAX_NODES); // Priority queue implemented using an array

    pq.enqueue(start);

    while (!pq.isEmpty()) {
        int u = pq.dequeue();

        if (visited[u])
            continue;
        visited[u] = true;

        for (int v = 1; v < MAX_NODES; ++v) {
            if (graph[u][v] != 0) {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    pq.enqueue(v);
                }
            }
        }
    }
}
int main() {
    int gridsize = 0;
    int testcase = 0;
    int index = 0;
    cout << "Enter the Grid size" << endl;
    cin >> gridsize;
    cout << "Enter the Test-cases" << endl;//how many ppls can you it//
    cin >> testcase;

    while (index < testcase) {
        int gridIndex = 0;
        int* grid = new int[gridsize * gridsize];
        for (int i = 0; i < gridsize * gridsize; i++) {
            grid[i] = 0;
        }
        int graph[MAX_NODES][MAX_NODES] = { 0 };//CONSTRUCTING THE ADJCENTCY MATRIX//
        cout << "Enter the number of roads: ";// inputing edges in the graph//
        int roads;
        cin >> roads;
        cout << "Enter the roads in format {start_node end_node weight}: " << endl;
        for (int i = 0; i < roads; i++) {
            int start_node, end_node, weight;
            cin >> start_node >> end_node >> weight;
            graph[start_node][end_node] = weight;
            graph[end_node][start_node] = weight;
        }
        cout << "Enter the source node: ";
        int start;
        cin >> start;

        int dist[MAX_NODES];
        dijkstra(start, graph, dist);

        cout << "Shortest distance from node " << start << " : " << endl;
        for (int i = 0; i < MAX_NODES; i++) {
            if (dist[i] != numeric_limits<int>::max()) {
                cout << "Node " << i << ": " << dist[i] << endl;
            }
        }
        // int signol;
        // cout << "Check weather the signal is Red (0) or Green (1)" << endl;
        // cin >> signol;
        //traffic s(1); //1 for green 0 for red//

        cout << "Enter the intersection of node to manage traffic: " << endl;
        int intersection;
        cin >> intersection;
        //  s.displaysignal();
        cout << "The number of cars can enter are 5 the other will be rerouted" << endl;
        traffic signals;
        Queue carqueue(10);
        for (int i = 1; i <= 10; i++) {
            carqueue.enqueue(i);
        }

        Queue shortestpathqueue(5);
        Queue alternatepathqueue(5);
        for (int i = 0; i < 5; i++) {
            shortestpathqueue.enqueue(carqueue.dequeue());
        }
        for (int i = 0; i < 5; i++) {
            alternatepathqueue.enqueue(carqueue.dequeue());
        }
        cout << "Cars at intersection " << intersection << ":" << endl;
        for (int time = 0; time < 10; time++) {
            cout << "Time unit: " << time + 1 << endl;
            signals.updatesignal();
            signals.displaysignal();


            int count = 0;
            if (signals.isgreen()) {
                cout << "Cars moving to shortest path: ";

                while (!shortestpathqueue.isEmpty() && count < 2) {
                    cout << shortestpathqueue.dequeue() << " ";
                    count++;
                }
                cout << endl;
            }
            else {

                cout << "Cars moving to alternate path: ";
                while (!alternatepathqueue.isEmpty() && count < 2) {
                    cout << alternatepathqueue.dequeue() << " ";
                    count++;
                }
                cout << endl;
            }
            if (shortestpathqueue.isEmpty()&&alternatepathqueue.isEmpty()) {
                cout << "No car is waiting in the shortest path" << endl;
                break;
            }
          //  if (alternatepathqueue.isEmpty()) {
            //    cout << "No car is waiting in the alternate path" << endl;
            //}

        }

        cout << endl;
        index++;
    }

}
#include "GridGraph.h"
#include "Tank.h"

//Constructor
GridGraph::GridGraph(int rows, int cols) : rows(rows), cols(cols) {
    adjMatrix = new int*[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        adjMatrix[i] = new int[rows * cols];
        std::memset(adjMatrix[i], 0, rows * cols * sizeof(int));
    }
    generateConnections();
}

//Desctructor
GridGraph::~GridGraph() {
    for (int i = 0; i < rows * cols; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

//Generar conexiones entre nodos
void GridGraph::generateConnections() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int node = i * cols + j;
            if (i > 0) addEdge(node, (i - 1) * cols + j);
            if (i < rows - 1) addEdge(node, (i + 1) * cols + j);
            if (j > 0) addEdge(node, i * cols + (j - 1));
            if (j < cols - 1) addEdge(node, i * cols + (j + 1));
        }
    }
}

//Agregar aristas al grafo
void GridGraph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}


//Genera nodos del grafo con -1, que se toman como obstaculos
void GridGraph::generateObstacles(float obstacleDensity) {
    QRandomGenerator* generator = QRandomGenerator::global();
    for (int i = 0; i < rows; ++i) {
        for (int j = 2; j < cols - 2; ++j) { // Ignorar las primeras 2 y últimas 2 columnas
            int node = i * cols + j;
            // Generar un número aleatorio para decidir si este nodo es un obstáculo
            if (generator->bounded(1.0) < obstacleDensity) {
                // Marcar el nodo como un obstáculo en la matriz de adyacencia (-1 valor para indicar "bloqueado")
                for (int k = 0; k < rows * cols; ++k) {
                    adjMatrix[node][k] = -1;
                    adjMatrix[k][node] = -1;
                }
            }
        }
    }
}

//Comprueba si el nodo tiene un obstuculo
bool GridGraph::isObstacle(int row, int col) const {
    int node = row * cols + col;
    return adjMatrix[node][node] == -1;
}


//Dibuja el grafo en la ventana
void GridGraph::drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor) {
    int cellWidth = (screenWidth / cols) * scaleFactor;
    int cellHeight = (screenHeight / rows) * scaleFactor;

    QBrush brush(QColor(210, 190, 150)); // Color estándar de las celdas
    QBrush obstacleBrush(QColor(150, 150, 150)); // Color para los obstáculos

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellWidth;
            int y = i * cellHeight;
            int node = i * cols + j;

            // Si el nodo es un obstáculo, usar un color diferente
            if (adjMatrix[node][node] == -1) {
                scene.addRect(x, y, cellWidth, cellHeight, QPen(Qt::black), obstacleBrush);
            } else {
                scene.addRect(x, y, cellWidth, cellHeight, QPen(Qt::black), brush);
            }
        }
    }
}

//Implementacion BFS
int* GridGraph::bfs(int startNode, int targetNode, int& pathLength) {
    bool* visited = new bool[rows * cols];
    int* parent = new int[rows * cols];
    std::memset(visited, false, rows * cols * sizeof(bool));
    std::memset(parent, -1, rows * cols * sizeof(int));

    Queue q(rows * cols);
    visited[startNode] = true;
    q.enqueue(startNode);

    while (!q.isEmpty()) {
        int current = q.dequeue();
        if (current == targetNode) break;

        for (int i = 0; i < rows * cols; ++i) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = current;
                q.enqueue(i);
            }
        }
    }

    pathLength = 0;
    int* path = new int[rows * cols];
    for (int at = targetNode; at != -1; at = parent[at]) {
        path[pathLength++] = at;
    }

    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    delete[] visited;
    delete[] parent;
    return path;
}

//Implementacion Dijikstra
int* GridGraph::dijkstra(int startNode, int targetNode, int& pathLength) {
    const int INF = std::numeric_limits<int>::max();
    bool* visited = new bool[rows * cols];
    int* distance = new int[rows * cols];
    int* parent = new int[rows * cols];

    std::memset(visited, false, rows * cols * sizeof(bool));
    std::fill_n(distance, rows * cols, INF);
    std::memset(parent, -1, rows * cols * sizeof(int));

    distance[startNode] = 0;
    PriorityQueue pq(rows * cols);
    pq.enqueue(startNode, 0);

    while (!pq.isEmpty()) {
        int current = pq.dequeue();
        if (visited[current]) continue;
        visited[current] = true;

        for (int i = 0; i < rows * cols; ++i) {
            if (adjMatrix[current][i] > 0) {
                int newDist = distance[current] + adjMatrix[current][i];
                if (newDist < distance[i]) {
                    distance[i] = newDist;
                    parent[i] = current;
                    pq.enqueue(i, newDist);
                }
            }
        }
    }

    pathLength = 0;
    int* path = new int[rows * cols];
    for (int at = targetNode; at != -1; at = parent[at]) {
        path[pathLength++] = at;
    }

    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    delete[] visited;
    delete[] distance;
    delete[] parent;
    return path;
}

//Linea Vista
int* GridGraph::lineOfSight(int startRow, int startCol, int targetRow, int targetCol, int& pathLength) {
    pathLength = 0;
    int maxSteps = std::max(std::abs(targetRow - startRow), std::abs(targetCol - startCol)) + 1;
    int* path = new int[maxSteps];
    int dx = std::abs(targetCol - startCol);
    int dy = std::abs(targetRow - startRow);
    int sx = (startCol < targetCol) ? 1 : -1;
    int sy = (startRow < targetRow) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Almacenar el nodo actual en la trayectoria
        path[pathLength] = startRow * cols + startCol;
        pathLength++;

        // Verificar si hemos alcanzado los límites del mapa
        if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
            break;
        }

        // Si encontramos un obstáculo, devolver el camino calculado hasta este punto
        if (isObstacle(startRow, startCol)) {
            return path;
        }

        // Si hemos llegado al destino, devolver la trayectoria calculada
        if (startRow == targetRow && startCol == targetCol) {
            return path;
        }

        // Actualizar las coordenadas según el algoritmo de Bresenham
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            startCol += sx;
        }
        if (e2 < dx) {
            err += dx;
            startRow += sy;
        }
    }

    // Si la trayectoria ha terminado sin llegar al destino o encontrar un obstáculo, devolver la trayectoria calculada hasta el límite
    return pathLength > 0 ? path : nullptr;
}





// Metodo para agregar tanques al grid
void GridGraph::addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight) {
    // Verifica que la celda no esté ocupada por un obstáculo
    int node = row * cols + col;
    if (adjMatrix[node][node] == -1) {
        qDebug() << "Error: No se puede colocar un tanque en una celda bloqueada.";
        return;
    }

    // Coloca el tanque en la celda especificada en la escena
    tank.display(scene, row, col, cellWidth, cellHeight);
}

//Revisar que el grafo es navegable
bool GridGraph::isNavigable() const {
    bool* visited = new bool[rows * cols];
    std::memset(visited, false, rows * cols * sizeof(bool));
    dfs(0, visited);
    for (int i = 0; i < rows * cols; ++i) {
        if (!visited[i]) {
            delete[] visited;
            return false;
        }
    }
    delete[] visited;
    return true;
}

//Dfs para revisar si es navegable
void GridGraph::dfs(int node, bool* visited) const {
    visited[node] = true;
    for (int i = 0; i < rows * cols; ++i) {
        if (adjMatrix[node][i] == 1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

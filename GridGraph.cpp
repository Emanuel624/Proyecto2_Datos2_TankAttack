#include "GridGraph.h"
#include "Tank.h"

GridGraph::GridGraph(int rows, int cols) : rows(rows), cols(cols) {
    adjMatrix = new int*[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        adjMatrix[i] = new int[rows * cols];
        std::memset(adjMatrix[i], 0, rows * cols * sizeof(int));
    }
    generateConnections();
}

GridGraph::~GridGraph() {
    for (int i = 0; i < rows * cols; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void GridGraph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

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


void GridGraph::generatePowerUps(QGraphicsScene& scene, float powerUpDensity, int cellWidth, int cellHeight) {
    int totalCells = rows * cols;
    int powerUpCount = totalCells * powerUpDensity;

    QRandomGenerator* generator = QRandomGenerator::global();

    for (int i = 0; i < powerUpCount; ++i) {
        int row, col, node;

        // Busca una celda vacía (sin obstáculo ni tanque)
        do {
            row = generator->bounded(rows);
            col = generator->bounded(2, cols - 2); // Evita primeras y últimas columnas
            node = row * cols + col;
        } while (adjMatrix[node][node] == -1); // Repite si es obstáculo

        // Crea un PowerUp aleatorio y lo coloca en la celda
        PowerUp* powerUp;
        int powerUpType = generator->bounded(4); // 4 tipos de PowerUps

        switch (powerUpType) {
            case 0:
                powerUp = new DobleTurno("/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/PowerUps/DoubleTurn.png", cellWidth, cellHeight);
            break;
            case 1:
                powerUp = new PrecisionMovimiento("/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/PowerUps/Movement.png", cellWidth, cellHeight);
            break;
            case 2:
                powerUp = new PrecisionAtaque("/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/PowerUps/PresitionPowerUp.png", cellWidth, cellHeight);
            break;
            case 3:
                powerUp = new PoderAtaque("/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/PowerUps/Damage+.png", cellWidth, cellHeight);
            break;
        }

        // Ajusta la posición y añade el PowerUp a la escena
        powerUp->setPos(col * cellWidth, row * cellHeight);
        scene.addItem(powerUp);
    }
}

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

void GridGraph::dfs(int node, bool* visited) const {
    visited[node] = true;
    for (int i = 0; i < rows * cols; ++i) {
        if (adjMatrix[node][i] == 1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

#include <iostream>
#include <vector>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>

class GridGraph {
private:
    int size; // Tamaño de la cuadrícula (N)
    std::vector<std::vector<int>> adjMatrix; // Matriz de adyacencia

public:
    // Constructor que inicializa una cuadrícula de NxN
    GridGraph(int n) : size(n), adjMatrix(n * n, std::vector<int>(n * n, 0)) {
        // Conectar cada celda con sus vecinos
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int node = i * size + j; // Nodo en la posición (i, j)
                if (i > 0) addEdge(node, (i - 1) * size + j); // Conectar con el nodo de arriba
                if (i < size - 1) addEdge(node, (i + 1) * size + j); // Conectar con el nodo de abajo
                if (j > 0) addEdge(node, i * size + (j - 1)); // Conectar con el nodo de la izquierda
                if (j < size - 1) addEdge(node, i * size + (j + 1)); // Conectar con el nodo de la derecha
            }
        }
    }

    // Método para agregar una arista entre dos nodos
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Grafo no dirigido
    }

    // Método para verificar si dos nodos están conectados
    bool isConnected(int u, int v) const {
        return adjMatrix[u][v] == 1;
    }

    // Método para dibujar la cuadrícula en una escena de Qt
    void drawGrid(QGraphicsScene& scene, int screenSize) {
        int cellSize = screenSize / size; // Tamaño de cada celda
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int x = j * cellSize; // Posición en X
                int y = i * cellSize; // Posición en Y
                // Dibujar la celda como un rectángulo
                scene.addRect(x, y, cellSize, cellSize, QPen(Qt::black), QBrush(Qt::NoBrush));
            }
        }
    }

    // Método para asegurar que el grafo es navegable
    bool isNavigable() const {
        std::vector<bool> visited(size * size, false);
        dfs(0, visited); // DFS desde el nodo 0 (parte superior izquierda)
        for (bool v : visited) {
            if (!v) return false; // Si algún nodo no fue visitado, el grafo no es navegable
        }
        return true;
    }

private:
    // Búsqueda en profundidad (DFS) para verificar conectividad
    void dfs(int node, std::vector<bool>& visited) const {
        visited[node] = true;
        for (int i = 0; i < size * size; ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Definir el tamaño de la pantalla
    int screenSize = 800; // Tamaño de la ventana (puedes ajustar esto para pantalla completa)
    int gridSize = 20; // Tamaño de la cuadrícula (20x20, por ejemplo)

    // Crear una escena de Qt para dibujar el grafo
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, screenSize, screenSize);

    // Crear el grafo basado en una cuadrícula de tamaño gridSize x gridSize
    GridGraph graph(gridSize);

    // Dibujar la cuadrícula en la escena
    graph.drawGrid(scene, screenSize);

    // Verificar si el grafo es navegable (solo para validación)
    if (graph.isNavigable()) {
        std::cout << "El grafo es completamente navegable." << std::endl;
    } else {
        std::cout << "Error: el grafo no es navegable." << std::endl;
    }

    // Crear una vista para mostrar la escena
    QGraphicsView view(&scene);
    view.setWindowTitle("Mapa del Grafo como Cuadrícula");
    view.resize(screenSize, screenSize);
    view.show();

    return app.exec(); // Ejecutar la aplicación de Qt
}


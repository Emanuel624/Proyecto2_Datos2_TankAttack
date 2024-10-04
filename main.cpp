#include <iostream>

#include <cstring>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include <QtCore/QRandomGenerator>
#include <QtGui/QBrush>
#include <QtGui/QScreen>

class GridGraph {
private:
    int rows; // Número de filas
    int cols; // Número de columnas
    int** adjMatrix; // Matriz de adyacencia

public:
    GridGraph(int rows, int cols) : rows(rows), cols(cols) {
        adjMatrix = new int*[rows * cols];
        for (int i = 0; i < rows * cols; ++i) {
            adjMatrix[i] = new int[rows * cols];
            std::memset(adjMatrix[i], 0, rows * cols * sizeof(int));
        }
        generateConnections();
    }

    // Liberar la memoria de la matriz de adyacencia
    ~GridGraph() {
        for (int i = 0; i < rows * cols; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void generateConnections() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int node = i * cols + j;
                if (i > 0) addEdge(node, (i - 1) * cols + j); // Conectar con el nodo de arriba
                if (i < rows - 1) addEdge(node, (i + 1) * cols + j); // Conectar con el nodo de abajo
                if (j > 0) addEdge(node, i * cols + (j - 1)); // Conectar con el nodo de la izquierda
                if (j < cols - 1) addEdge(node, i * cols + (j + 1)); // Conectar con el nodo de la derecha
            }
        }
    }

    void drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor) {
        // Calcular el tamaño de las celdas ajustado al tamaño de la pantalla
        int cellWidth = (screenWidth / cols) * scaleFactor;
        int cellHeight = (screenHeight / rows) * scaleFactor;
        QBrush brush(QColor(205, 133, 63)); // Color café claro

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int x = j * cellWidth;
                int y = i * cellHeight;
                scene.addRect(x, y, cellWidth, cellHeight, QPen(Qt::black), brush);
            }
        }
    }

    bool isNavigable() const {
        bool* visited = new bool[rows * cols];
        std::memset(visited, false, rows * cols * sizeof(bool)); // Inicializar el arreglo a false
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

private:
    void dfs(int node, bool* visited) const {
        visited[node] = true;
        for (int i = 0; i < rows * cols; ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Obtener el tamaño real de la pantalla
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // Definir el número de filas y columnas
    int rows = 15;
    int cols = 30;

    // Crear una escena de Qt para dibujar el grafo
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, screenWidth, screenHeight);

    // Crear el grafo basado en una cuadrícula
    GridGraph graph(rows, cols);

    // Reducir el tamaño de los nodos mediante escala
    float scaleFactor = 0.8; // Reducir el tamaño de los nodos en un 80%
    graph.drawGrid(scene, screenWidth, screenHeight, scaleFactor);

    // Verificar si el grafo es navegable
    if (graph.isNavigable()) {
        std::cout << "El grafo es completamente navegable." << std::endl;
    } else {
        std::cout << "Error: el grafo no es navegable." << std::endl;
    }

    // Crear una vista para mostrar la escena
    QGraphicsView view(&scene);
    view.setWindowTitle("Mapa del Grafo con Tamaño Ajustado a Pantalla");
    view.resize(screenWidth, screenHeight);
    view.showFullScreen(); // Mostrar en pantalla completa

    return app.exec();
}

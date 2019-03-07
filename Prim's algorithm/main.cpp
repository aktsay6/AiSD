#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
class Vertex
{
public:
    int parent;
    int key;
    int vertex;
};

bool inc_a(Edge edge, int u)
{
    return edge.A == u;
}

bool inc_b(Edge edge, int u)
{
    return edge.B == u;
}

bool contains(vector<Vertex*>& remaining, int v)
{
    for (int i = 0; i < remaining.size(); ++i)
    {
        if(remaining[i]->vertex == v)
            return true;
    }
    return false;
}

Vertex getMinimum(vector<Vertex*>& remaining)
{
    Vertex* min = remaining[0];
    int k = 0;
    for (int i = 0; i < remaining.size(); ++i)
    {
        if(remaining[i]->key < min->key)
        {
            min = remaining[i];
            k = i;
        }
    }
    remaining.erase(remaining.begin() + k);
    return *min;
}
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    //Советую разделить решение на логические блоки
    //Можно использовать любые другие структуры, но затем скопировать ответ в структуру Edge для записи результата в файл.
    //Также можно добавить любые необходимые компараторы для предложенного класса Edge, так как все методы и поля публичные.
    vector<Vertex> vertex(N);
    for (int i = 0; i < N; ++i)
    {
        vertex[i].key = 30001;
        vertex[i].parent = i;
        vertex[i].vertex = i;
    }
    vertex[0].key = 0;
    vector<Vertex*> remaining(N);
    for (int i = 0; i < N; ++i)
    {
        remaining[i] = &vertex[i];
    }
    while(!remaining.empty())
    {
        Vertex u = getMinimum(remaining);
        for (int i = 0; i < edges.size(); ++i)
        {
            if(inc_a(edges[i], u.vertex))
            {
                if(contains(remaining, edges[i].B) && edges[i].W < vertex[edges[i].B].key)
                {
                    vertex[edges[i].B].parent = u.vertex;
                    vertex[edges[i].B].key = edges[i].W;
                }
            }
            if(inc_b(edges[i], u.vertex))
            {
                if(contains(remaining, edges[i].A) && edges[i].W < vertex[edges[i].A].key)
                {
                    vertex[edges[i].A].parent = u.vertex;
                    vertex[edges[i].A].key = edges[i].W;
                }
            }

        }
    }
    for (int i = 1; i < vertex.size(); ++i)
    {
        Edge edge;
        edge.A = vertex[i].parent;
        edge.B = vertex[i].vertex;
        if(edge.A > edge.B)
            swap(edge.A, edge.B);
        edge.W = vertex[i].key;
        if(edge.W != 30001)
            result.push_back(edge);
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}
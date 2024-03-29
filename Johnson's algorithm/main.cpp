﻿#include <queue>
#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

class Vertex
{
public:
    int h;
    int bound;
    vector<Edge> edges;
};
struct Compare
{
    bool operator() (const Vertex *v1, const Vertex *v2) const
    {
        return v1->bound > v2->bound;
    }
};

void dijkstra(int N, vector<Edge>& edges, vector<int>& result, int source)
{
    //Советую разделить решение на логические блоки
    vector<Vertex*> vec_vertex(N);
    priority_queue<Vertex*, vector<Vertex*>, Compare> queue;
    Vertex* vertex;
    for (int i = 0; i < N; ++i)
    {
        vertex = new Vertex;
        if(i != source)
            vertex->bound = 130001;
        else
            vertex->bound = 0;
        for (int j = 0; j < edges.size(); ++j)
        {
            if(edges[j].A == i)
                vertex->edges.push_back(edges[j]);
        }
        queue.push(vertex);
        vec_vertex[i] = vertex;
    }

    while(!queue.empty())
    {
        vertex = queue.top();
        queue.pop();
        for (int i = 0; i < vertex->edges.size(); ++i)
        {
            if(vertex->edges[i].W + vertex->bound < vec_vertex[vertex->edges[i].B]->bound)
                vec_vertex[vertex->edges[i].B]->bound = vertex->edges[i].W + vertex->bound;
        }
        Vertex* tmp = new Vertex;
        tmp->bound = -1000000;
        queue.push(tmp);
        queue.pop();
        delete tmp;
    }

    for (int i = 0; i < N; ++i)
    {
        result.push_back(vec_vertex[i]->bound);
    }
    for (int i = 0; i < vec_vertex.size(); ++i)
    {
        delete vec_vertex[i];
    }
}


void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    //Здесь вывод на печать, например так:
    //Предлагается построчно выводить, как требуется в ответе

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result[i].size(); ++j)
        {
            (result[i][j] == 130001) ? result[i][j] = -1 : result[i][j];
            result[i][j] < 0 ? result[i][j] = -1 : result[i][j];
            if(i != j)
                fout << i << " " << j << " " << result[i][j] << '\n';
        }
    }
    //Можно сделать иначе - в этом же методе, но используя данные параметры метода (vector<vector<int>>)
    //Для этого метод и вынесен в этот файл
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.

bool shortestPath(int N, int M, vector<Edge>& edges, vector<int>& result, int& source)
{
    // made only for edges with positive weight

    //Советую разделить решение на логические блоки
    vector<int> dist(N);
    for (int i = 0; i < N; ++i)
        dist[i] = 130001;

    dist[source] = 0;
    for (int i = 0; i < N - 1; ++i)
    {
        for (int j = 0; j < M; ++j)
            dist[edges[j].B] = min(dist[edges[j].A] + edges[j].W, dist[edges[j].B]);
    }
    for (int i = 0; i < dist.size(); ++i)
    {
        result.push_back(dist[i]);
    }
    return true;
}

void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    //Советую разделить решение на логические блоки
    vector<Vertex> vertex(N);
    vector<Edge> new_edges;
    Vertex s;
    vertex.push_back(s);
    for (int i = 0; i < edges.size(); ++i)
    {
        new_edges.push_back(edges[i]);
    }
    Edge edge;
    for (int i = 0; i < N; ++i)
    {
        edge.A = N;
        edge.B = i;
        edge.W = 0;
        new_edges.push_back(edge);
    }

    vector<int> s_to_vertex;
    if(shortestPath(N + 1, new_edges.size(), new_edges, s_to_vertex, N))
    {
        for (int i = 0; i < vertex.size() - 1; ++i)
            vertex[i].h = s_to_vertex[i];
        vector<Edge> new_weight;
        for (int i = 0; i < edges.size(); ++i)
        {
            edge.A = edges[i].A;
            edge.B = edges[i].B;
            edge.W = edges[i].W + vertex[edges[i].A].h - vertex[edges[i].B].h;
            new_weight.push_back(edge);
        }
        for (int i = 0; i < vertex.size() - 1; ++i)
        {
            vector<int> line;
            dijkstra(N, new_weight, line, i);
            result.push_back(line);
        }
    }
    else
        return;
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
    vector<vector<int>> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeValues(result);

    return 0;
}
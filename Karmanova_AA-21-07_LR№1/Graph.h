#pragma once
#include<iostream>
#include <list>
#include <stack>
using namespace std;

// ����� ��� ������������� �����
class Graph
{
    int V;	// ���������� ������

    //  ��������� �� ������, ���������� ������ ���������
    list<int>* adj;

    // �������, ������������ topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
public:
    Graph(int V);   // �����������

    // ������� ��� ���������� ����� � ����
    void addEdge(int v, int w);

    // ������� �������������� ���������� �����
    void topologicalSort();
};


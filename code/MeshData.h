// By: Huming Liao, 2016.5.13
// At: CASE, Cleveland, OHio, 44120
#pragma once
#include <vector>
using namespace std;

struct Elements
{
	int id;
	int node[4];
};

struct Nodes
{
	int id;
	double coordinate[3];
};

struct NodeSets
{
	char name[255];
	vector<int> node;
};

struct NodeSets_generate
{
	char name[255];
	int start;
	int end;
	int step;
};

struct ElementSets
{
	char name[255];
	vector<int> element;
};

struct ElementSets_generate
{
	char name[255];
	int start;
	int end;
	int step;
};
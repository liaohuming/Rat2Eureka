// By: Huming Liao, 2016.5.13
// At: CASE, Cleveland, OHio, 44120

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MeshData.h"
using namespace std;

static const int NSET_TYPE = 1;
static const int NSET_G_TYPE = 2;
static const int ESET_TYPE = 3;
static const int ESET_G_TYPE = 4;

vector<Elements> elementVector;
vector<Nodes> nodeVector;
vector<int> fluidFixedVector;
vector<NodeSets> nodeSetVector;
vector<NodeSets_generate> nodeSet_G_Vector;
vector<ElementSets> elementSetVector;
vector<ElementSets_generate> elementSet_G_Vector;

void ReadElemets();
void ReadNodes();
void ReadFluidFixed();
void ReadFluidFixedLine(string lineStr);
void ReadSets();
void ReadSets4Rat();
const int& ReturnDataType(int& dataType, string lineStr);
void OutputData();

int main(int argc, char* argv[])
{
	ReadElemets();
	ReadNodes();
	ReadFluidFixed();
	cout << fluidFixedVector.size() << endl;
	ReadSets4Rat();
	OutputData();

	system("pause");
	return 0;
}

void ReadElemets()
{
	Elements tempElem;
	ifstream infile;
	infile.open("elem_rat.txt");
	if (!infile.is_open())
	{
		cout << "Can not open \"elem_rat.txt\"" << endl;
		return;
	}
	while (!infile.eof())
	{
		string lineStr = "";
		getline(infile, lineStr);
		if (lineStr != "")
		{
			//cout << lineStr << endl;
			sscanf(lineStr.c_str(), "%d,%d,%d,%d,%d", 
				&(tempElem.id), &(tempElem.node[0]), &(tempElem.node[1]), &(tempElem.node[2]), &(tempElem.node[3]));
			elementVector.push_back(tempElem);
		}
	}
	return;
}

void ReadNodes()
{
	Nodes tempNode;
	ifstream infile;
	infile.open("nodes_rat.txt");
	if (!infile.is_open())
	{
		cout << "Can not open \"nodes_rat.txt\"" << endl;
		return;
	}
	while (!infile.eof())
	{
		string lineStr = "";
		getline(infile, lineStr);
		if (lineStr != "")
		{
			//cout << lineStr << endl;
			sscanf(lineStr.c_str(), "%d,%lf,%lf,%lf",
				&(tempNode.id), &(tempNode.coordinate[0]), &(tempNode.coordinate[1]), &(tempNode.coordinate[2]));
			nodeVector.push_back(tempNode);
		}
	}
	return;
}

void ReadFluidFixed()
{
	ifstream infile;
	infile.open("fluid_fixed.txt");
	if (!infile.is_open())
	{
		cout << "Can not open \"fluid_fixed.txt\"" << endl;
		return;
	}
	while (!infile.eof())
	{
		string lineStr = "";
		getline(infile, lineStr);
		if (lineStr != "")
		{
			ReadFluidFixedLine(lineStr);
		}
	}
	return;
}

void ReadSets()
{
	//NodeSets tempNodeSet;

	//ifstream infile;
	//infile.open("groups_elem_nodes.txt");
	//if (!infile.is_open())
	//{
	//	cout << "Can not open \"groups_elem_nodes.txt\"" << endl;
	//	return;
	//}
	//while (!infile.eof())
	//{
	//	string lineStr = "";
	//	getline(infile, lineStr);
	//	if (lineStr != "")
	//	{
	//		int dataType = 0;

	//		switch (ReturnDataType(dataType, lineStr))
	//		{
	//		case NSET_TYPE:
	//			{
	//				sscanf(lineStr.c_str(), "%*s=%s,%s",&(tempNodeSet.name));
	//				getline(infile, lineStr);
	//				while (lineStr!="")
	//				{
	//					if (ReturnDataType(dataType, lineStr) != 0)
	//					{
	//						nodeSetVector.push_back(tempNodeSet);
	//						break;
	//					}
	//					else
	//					{
	//						//按空格分隔Set的每个元素
	//						char lineData[255] = { 0 };
	//						strcpy(lineData, lineStr.c_str());
	//						const char *delimter = ",";
	//						char *item;
	//						vector<int> itemCounter;
	//						item = strtok(lineData, delimter);
	//						while (item)
	//						{
	//							//把char类型的转换成int类型存入临时变量
	//							int nodeInt = 0;
	//							string nodeStr(item);
	//							stringstream nodeSs(nodeStr);
	//							nodeSs >> nodeInt;
	//							tempNodeSet.node.push_back(nodeInt);
	//							item = strtok(NULL, delimter);
	//						}
	//						getline(infile, lineStr);
	//					}
	//				}
	//				
	//			}
	//			break;

	//		case NSET_G_TYPE:

	//			break;

	//		case ESET_TYPE:

	//			break;

	//		case ESET_G_TYPE:

	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}
	//return;
}

void ReadFluidFixedLine(string lineStr)
{
	//按空格分隔Set的每个元素
	char lineData[255] = { 0 };
	strcpy(lineData, lineStr.c_str());
	const char *delimter = ",";
	char *item;
	vector<int> itemCounter;
	item = strtok(lineData, delimter);
	while (item)
	{
		//把char类型的转换成int类型存入临时变量
		int nodeInt = 0;
		string nodeStr(item);
		stringstream nodeSs(nodeStr);
		nodeSs >> nodeInt;
		fluidFixedVector.push_back(nodeInt);
		item = strtok(NULL, delimter);
	}
}

const int& ReturnDataType(int& dataType, string lineStr)
{
	string nodeSet = "*Nset,";
	string elementSet = "*Elset,";
	string generateStr = "generate";

	if (lineStr.find(nodeSet) < lineStr.length())
	{
		if (lineStr.find(generateStr) < lineStr.length())
		{
			dataType = NSET_G_TYPE;
			return dataType;
		}
		else
		{
			dataType = NSET_TYPE;
			return dataType;
		}
	}
	if (lineStr.find(elementSet) < lineStr.length())
	{
		if (lineStr.find(generateStr) < lineStr.length())
		{
			dataType = ESET_G_TYPE;
			return dataType;
		}
		else
		{
			dataType = ESET_TYPE;
			return dataType;
		}
	}
	else
	{
		return 0;
	}
}

void ReadSets4Rat()
{
	ifstream infile;
	infile.open("groups_elem_nodes.txt");
	if (!infile.is_open())
	{
		cout << "Can not open \"groups_elem_nodes.txt\"" << endl;
		return;
	}

	ElementSets_generate tempES_G;
	NodeSets_generate tempNS_G;
	NodeSets tempNS;
	int index = 0;
	string lineStr = "";
	getline(infile, lineStr);
	while (lineStr != "")
	{
		if (index == 0)
		{
			sscanf(lineStr.c_str(), "%*[^=]=%[^,],%*s", &(tempES_G.name));
			index++;
			getline(infile, lineStr);
		}
		if (index == 1)
		{
			sscanf(lineStr.c_str(), "%d,%d,%d", &(tempES_G.start), &(tempES_G.end), &(tempES_G.step));
			index++;
			getline(infile, lineStr);
			elementSet_G_Vector.push_back(tempES_G);
		}
		if (index == 2)
		{
			sscanf(lineStr.c_str(), "%*[^=]=%[^,],%*s", &(tempES_G.name));
			index++;
			getline(infile, lineStr);
		}
		if (index == 3)
		{
			sscanf(lineStr.c_str(), "%d,%d,%d", &(tempES_G.start), &(tempES_G.end), &(tempES_G.step));
			index++;
			getline(infile, lineStr);
			elementSet_G_Vector.push_back(tempES_G);
		}
		if (index == 4)
		{
			sscanf(lineStr.c_str(), "%*[^=]=%[^,],%*s", &(tempNS_G.name));
			index++;
			getline(infile, lineStr);
		}
		if (index == 5)
		{
			sscanf(lineStr.c_str(), "%d,%d,%d", &(tempNS_G.start), &(tempNS_G.end), &(tempNS_G.step));
			index++;
			getline(infile, lineStr);
			nodeSet_G_Vector.push_back(tempNS_G);
		}
		if (index == 6)
		{
			sscanf(lineStr.c_str(), "%*[^=]=%[^,],%*s", &(tempNS.name));
			index++;
			getline(infile, lineStr);
		}
		if (index > 6)
		{
			//按","分隔Set的每个元素
			char lineData[255] = { 0 };
			strcpy(lineData, lineStr.c_str());
			const char *delimter = ",";
			char *item;
			item = strtok(lineData, delimter);
			while (item)
			{
				//把char类型的转换成int类型存入临时变量
				int nodeInt = 0;
				string nodeStr(item);
				stringstream nodeSs(nodeStr);
				nodeSs >> nodeInt;
				tempNS.node.push_back(nodeInt);
				item = strtok(NULL, delimter);
			}
		}
		getline(infile, lineStr);
	}
	nodeSetVector.push_back(tempNS);
}

void OutputData()
{
	FILE *outputFile = NULL;
	outputFile = fopen("mesh.dat", "w");
	fprintf(outputFile, "%d\t%d\t%d\t%d\n", 3, 4, nodeVector.size(), elementVector.size());

	for (int i = 0; i < nodeVector.size(); i++)
	{
		fprintf(outputFile, "%d\t%f\t%f\t%f\n",
			nodeVector[i].id,
			nodeVector[i].coordinate[0],
			nodeVector[i].coordinate[1],
			nodeVector[i].coordinate[2]);
	}

	for (int i = 0; i < elementVector.size(); i++)
	{
		fprintf(outputFile, "%d\t%d\t%d\t%d\t%d\n",
			elementVector[i].id,
			elementVector[i].node[0],
			elementVector[i].node[1],
			elementVector[i].node[2],
			elementVector[i].node[3]);
	}

	for (int i = 0; i < elementSet_G_Vector.size(); i++)
	{
		fprintf(outputFile, "8\t%s\t%d\n",
			elementSet_G_Vector[i].name,
			elementSet_G_Vector[i].end - elementSet_G_Vector[i].start);

		for (int j = 0; j < elementSet_G_Vector[i].end - elementSet_G_Vector[i].start + 1; j++)
		{
			int temp = elementSet_G_Vector[i].start + j*elementSet_G_Vector[i].step;
			fprintf(outputFile, "%d\n", temp);
		}
	}

	for (int i = 0; i < nodeSetVector.size(); i++)
	{
		fprintf(outputFile, "7\t%s\t%d\n",
			nodeSetVector[i].name,
			nodeSetVector[i].node.size());

		for (int j = 0; j < nodeSetVector[i].node.size(); j++)
		{
			fprintf(outputFile, "%d\n", nodeSetVector[i].node[j]);
		}
	}

	fprintf(outputFile, "7\t%s\t%d\n",
		nodeSet_G_Vector[0].name,
		nodeSet_G_Vector[0].end - nodeSet_G_Vector[0].start);
	for (int i = 0; i < nodeSet_G_Vector[0].end - nodeSet_G_Vector[0].start + 1; i++)
	{
		int temp = nodeSet_G_Vector[0].start + i*nodeSet_G_Vector[0].step;
		fprintf(outputFile, "%d\n", temp);
	}

	fprintf(outputFile, "7\tfluidFixed\t%d\n", fluidFixedVector.size());
	for (int  i = 0; i < fluidFixedVector.size(); i++)
	{
		fprintf(outputFile, "%d\n", fluidFixedVector[i]);
	}

	fclose(outputFile);
}
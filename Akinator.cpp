#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#define CANARY 1337


typedef int  Data;

class  Node
{
private:
	int canary1 = CANARY;
	Data value;		 //      данные в узле	
	class Node* left;	 //      левая ветвь
	class Node* right;	 //      правая ветвь
public:
	Node();			 //	конструктор
	~Node();		 //	деструктор

	

	void Check();		 //	проверка дерева
	void add(Data);		 //	добавить ветку, уже существующее значение не добавляется
	void print();		 //	инфексный вывод дерева	
	void reset();		 //	обнуление(сброс) дерева
	size_t mass();		 //	колво узлов дерева
	void dump();		 //	печать дерева через Dot
	void dump_in_file(FILE*);//	вывод дерева в файл dota2 на языкке dot
private:
	int canary2 = CANARY;
};


void Node::Check()
{
	assert(canary1 == CANARY);
	assert(canary2 == CANARY);	
	
	assert(&value);
	if(left != NULL)
		(*left).Check();
	if(right != NULL)
		(*right).Check();
}



Node::Node ()
{
	value = 0;
	left = NULL;
	right = NULL;
	
	Node::Check();


}

size_t Node::mass()
{
	size_t mas = 1;
	if(left != NULL)
		mas += (*left).mass();
	if(right != NULL)
		mas += (*right).mass();
	return mas;
}

void Node::reset()
{
	if(left != NULL)
	{
		(*left).~Node();
		free(left);
	}
	if(right != NULL)
	{
		(*right).~Node();
		free(right);
	}
	value = 0;
	left = NULL;
	right = NULL;
	Node::Check();

}

void Node::add(Data input)
{
	Node::Check();

	if(value == 0)
	{
		if((left == NULL) && (right == NULL))
		{
			value = input;	
		
		}
	}
	else
	{

		if (input < value)
		{
			if(left != NULL)
				(*left).add(input);
			else
			{
				left = (Node*)calloc(1, sizeof(class Node));
				left -> canary1 = CANARY;
				left -> canary2 = CANARY;
				left -> value = input;
				(*left).Check();
			

			}
		}
		if(input > value)
		{
			if(right != NULL)
				(*right).add(input);
			else
			{
				right = (Node*)calloc(1, sizeof(class Node));
				right -> canary1 = CANARY;
				right -> canary2 = CANARY;
				right -> value = input;
				(*right).Check();


			}	

		}
	}
}

void Node::print()
{

	if(left != NULL)
		(*left).print();

	printf("%d ", value);


	if(right != NULL)
		(*right).print();


}

void Node::dump()
{
	Node::Check();	

	FILE* dota = fopen("dota2", "w");
	assert(dota);
	
	fprintf(dota, "digraph dota_one_love {\nbgcolor=\"#C6CFD532\";\nresolution=720;\n");

	Node::dump_in_file(dota);


	fprintf(dota, "\n}\n");

	fclose(dota);

	system("dot -Tgif -Odota.gif dota2");

}

void Node::dump_in_file(FILE* dota)
{
	fprintf(dota, "\t%d[color = \"#%6d\"] [fillcolor = \"#%6d\"][fontcolor = red] ;\n", value, rand() % (899998 - 0) + 100000, rand() % (899998 - 0)+ 100000);
	if(left != NULL)
	{
		fprintf(dota, "\t%d -> %d[color = \"#%6d\"] [fillcolor = \"#%6d\"] ;\n", value, left -> value, rand() % (899998 - 0)+ 100000, rand() % (899998 - 0)+ 100000);
		(*left).dump_in_file(dota);
	}
	if(right != 0)
	{
		fprintf(dota, "\t%d -> %d[color = \"#%6d\"] [fillcolor = \"#%6d\"] ;\n", value, right -> value, rand() % (899998 - 0)+ 100000, rand() % (899998 - 0)+ 100000);
		(*right).dump_in_file(dota);
	}


}


Node::~Node()
{
	Node::Check();	

	if(left != NULL)
	{
		(*left).~Node();
		free(left);
	}
	if(right != NULL)
	{
		(*right).~Node();
		free(right);

	}

}


int main()
{


	srand(time(0));
	
	size_t temp;

	Node Tree;

	Tree.add(5);
	Tree.add(777);
	Tree.add(8);
	Tree.add(100);
	Tree.add(666);
	Tree.add(1);
	Tree.add(9);
	Tree.add(14);

	Tree.print();

	printf("\nCANARY = %d\n", CANARY);

	temp = Tree.mass();

	printf("\n%u\n", temp);

	Tree.dump();

	Tree.reset();

	return 0;
}

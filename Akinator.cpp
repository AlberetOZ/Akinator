#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <iostream>
#define MAX_LINE 100

const static int CANARY = rand() % (time(0)) + 1;

typedef char* Data;

class  Node
{
private:
	int canary1 = CANARY;
	Data value;				 //      данные в узле	
	class Node* left;			 //      левая ветвь
	class Node* right;			 //      правая ветвь
	class Node* prev;			 //	 предыдуший узел
public:
	Node();					 //	конструктор
	~Node();				 //	деструктор

	void Begin_Akinator();			 //	ну, собственно, самое важное в данной проге
	void F_Akinator();			 //     ну, собственно, самое важное в данной проге

	void Check();				 //	проверка дерева
	void add(Data);				 //	добавить ветку, уже существующее значение не добавляется

	void print();				 //	печать базы акинатора в файл
	void print_step(FILE*);			 //	шаг печати узла дерева
	void scan(class Node*);			 //	считывание из файла базы акинатора
	void scan_step(FILE*, class Node*);	 //	шаг считывания узла дерева	

	size_t mass();				 //	колво узлов дерева
	void dump();				 //	печать дерева через Dot
	void dump_in_file(FILE*);		 //	вывод дерева в файл dota2 на языкке dot
private:
	int canary2 = CANARY;
};


void Node::Check()
{
	assert(canary1 == CANARY);
	assert(canary2 == CANARY);	
	
	assert(value);

	if(left != NULL)
		(*left).Check();
	if(right != NULL)
		(*right).Check();
}



Node::Node ()
{
	value = (char*)calloc(1, MAX_LINE);
	left = NULL;
	right = NULL;
	prev = NULL;
	
	Node::Check();


}

void Node::Begin_Akinator()
{
	printf("Ну, здравствуй, мой друг))\nДавай сыграем в одну игру, тебе же есть 18?\n");
	
	int i = 0;
	char start[] = {0};
	for(; i == 0; )
	{
		
		printf("Начнем? (Д/Н)\n");

		scanf("%s", start);

		 
		if(start[1] == "Д"[1])
		{
			Node::Check();
			Node::F_Akinator();


		}
		if(start[1] == "Н"[1])
		{
			i++;
			printf("Я уверен, ты все равно вернешься в эту проклятую игру...\n");

		}
		if((start[1] != "Д"[1]) && (start[0] != "Н"[1]))
			 printf("Пасхалок нет, выбирай что дают\n");


	}

	printf("Прощааай\n");

	Node::Check();

	Node::print();

	Node::dump();

	exit(0);

}

void Node::F_Akinator()
{

	if((right == NULL) && (left == NULL))
	{
		char end[] = {0};
		printf("GGWP, ты загадал: %s\nЯ прав? (Д/Н)\n", value);
		int i = 0;
		for(i = 0; i == 0;)
		{

			scanf("%s", end);

		 
			if(end[1] == "Д"[1])
			{
				printf("GG EZ, даже не прочувствовал, давай еще одну\n");	
				i++;
			}
			if(end[1] == "Н"[1])
			{
				char temp[100] = {0};
				i++;
				printf("А ты сильный игрок, скажи что ты загадал\n");

				scanf("%s", temp);

				Node::add(temp);
				Node::Check();
			}
			if((end[1] != "Д"[1]) && (end[1] != "Н"[1]))
				 printf("Пасхалок нет,сколько тебе повторять, тыкай в Да или Нет\n");


		}
	}
	else
	{
		char step[] = {0};
		int i = 0;

		printf("То что ты загадал %s? (Д/Н)\n", value);
		
		for(i = 0; i == 0;)
		{
			scanf("%s", step);

			if(step[1] == "Д"[1])
			{
				(*left).F_Akinator();
				i++;
			}
			if(step[1] == "Н"[1])
			{
				(*right).F_Akinator();
				i++;
			}
			if((step[1] != "Н"[1]) && (step[1] != "Д"[1]))
			{

				printf("Пасхалки скоро будут, для этого нужны лишь ваши донаты, всего то в размере 100 биткоинов))\n");

			}
		}



	}



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


void Node::add(Data input)
{
	Node::Check();

	right = (Node*)calloc(1, sizeof(class Node));
	right -> canary1 = CANARY;
	right -> canary2 = CANARY;
	right -> value = (char*)calloc(1, MAX_LINE);
	stpcpy(right -> value, value);
	(*right).Check();

	printf("Чем загаданное отличается от %s?\n", value);

	scanf("%s", value);

	left = (Node*)calloc(1, sizeof(class Node));
	left -> canary1 = CANARY; 
	left -> canary2 = CANARY; 
	left -> value = (char*)calloc(1, MAX_LINE);
	stpcpy(left -> value, input);
	(*left).Check();

	printf("База обновлена, теперь то я тебя раскатаю\n");

	Node::Check();
}

void Node::print()
{
	FILE* data = fopen("data", "w");

	assert(data);

	Node::Check();

	Node::print_step(data);

	fprintf(data,"$$$$$$$$");

	fclose(data);
}

void Node::print_step(FILE* data)
{

	fprintf(data, "( %s ", value);
	
	

	if(left != NULL)
		(*left).print_step(data);

	if(right != NULL)
		(*right).print_step(data);


	fprintf(data, ") ");
}



void Node::scan(class Node* root)
{

	FILE* data = fopen("data", "r");

	assert(data);

	char temp = '\0';	

	fscanf(data, "%c%s",  &temp,  value); 

	Node::scan_step(data, root);

	Node::Check();


	fclose(data);

}

void Node::scan_step(FILE* data, class Node* root)
{
	char step = '\0';

	fscanf(data, "%c%c", &step, &step);
	
	if(step == '(')
	{
		if(left == NULL)
		{
			
			left = (Node*)calloc(1, sizeof(class Node));
			left -> canary1 = CANARY;
			left -> canary2 = CANARY;
			left -> prev = root; 
			left -> value = (char*)calloc(1, MAX_LINE);
			(*left).Check();



			(*left).scan_step(data, left);
	
		}
		else
		{
			right = (Node*)calloc(1, sizeof(class Node));
			right -> canary1 = CANARY;
			right -> canary2 = CANARY;
			right -> prev = root;
			right -> value = (char*)calloc(1, MAX_LINE);
			(*right).Check();
			(*right).scan_step(data, right);
		}
	}
	else if(step == ')')
		(*prev).scan_step(data, prev);
	else if(step == '$')
		ungetc(step , data);
	else
	{
		ungetc(step, data);
		fscanf(data, "%s", value);
		Node::scan_step(data, root);

	}
	
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
	fprintf(dota, "\t%s[color = \"#%6d\"] [fillcolor = \"#%6d\"][fontcolor = red] ;\n", value, rand() % (899998 - 0) + 100000, rand() % (899998 - 0)+ 100000);
	if(left != NULL)
	{
		fprintf(dota, "\t%s -> %s[color = \"#%6d\"] [fillcolor = \"#%6d\"] ;\n", value, left -> value, rand() % (899998 - 0)+ 100000, rand() % (899998 - 0)+ 100000);
		(*left).dump_in_file(dota);
	}
	if(right != 0)
	{
		fprintf(dota, "\t%s -> %s[color = \"#%6d\"] [fillcolor = \"#%6d\"] ;\n", value, right -> value, rand() % (899998 - 0)+ 100000, rand() % (899998 - 0)+ 100000);
		(*right).dump_in_file(dota);
	}


}


Node::~Node()
{
	Node::Check();	

	free(value);

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

	size_t temp;

	Node Akinator;

	Akinator.scan(&Akinator);

	Akinator.dump();

	Akinator.Begin_Akinator();	

	//Akinator.print();

	//Akinator.dump();

	return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
using namespace std;
int totalline = 0;
class Node
{
public:
	char Data;
	Node *next;
	Node *previous;
	Node *up;
	Node *down;

	Node(char s)
	{
		Data = s;
		this->next = NULL;
		this->previous = NULL;
		this->up = NULL;
		this->down = NULL;
	}
};
class Linkedlist
{
public:
	Node *Head;
	int countletter = 0;
	int countline = 0;
	Linkedlist()
	{
		Head = NULL;
	}
	void insert(char s, int count, string st)
	{
		ofstream write(st + "sample.txt", ios::app);
		Node *newnode = new Node(s);
		write << newnode->Data;
		if (Head == NULL)
		{
			Head = newnode;
			countletter++;
			countline++;
			return;
		}
		if (countline == 1 && countletter == 0)
		{
			Head->down = newnode;
			newnode->up = Head;
			countletter++;
			countline--;
			return;
		}
		countletter++;
		Node *ptr = Head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = newnode;
		newnode->previous = ptr;

		if (countletter == count)
		{
			totalline++;
			/*Node *Temp;*/
			while (Head->previous != NULL)
			{
				Head = Head->previous;
			}
			countletter = 0;
			write << endl;
			countline++;
		}
	}


	void insertat(int pos, char data, string st)
	{
		ofstream write(st + "sample.txt", ios::app);
		if (pos > countletter + 1 || pos < 1)
		{
			cout << "Invalid Position" << endl;
			return;
		}
		if (pos == 1)
		{
			Node *temp = new Node(data);
			temp->next = Head;
			Head->previous = temp;
			Head = temp;
			countletter++;
			totalline++;
			return;
		}
		Node *temp = new Node(data);
		countletter++;
		totalline++;
		Node *ptr = Head;
		for (int i = 1; i < pos - 1; i++)
		{
			ptr = ptr->next;
		}
		temp->next = ptr->next;
		temp->previous = ptr;
		if (ptr->next != NULL)
		{
			ptr->next->previous = temp;
		}
		ptr->next = temp;
	}
};
class File
{
public:
	Linkedlist Data;
	string filename;

	void writingfile(string filename)
	{
		bool flag = true;
		while (flag)
		{
			string savefile;
			getline(cin, savefile);
			if (savefile == "#save")
			{
				flag = false;
				return;
			}
			int counttotalchar = savefile.length();
			char * ch = new char[savefile.length()];
			for (int i = 0; i < savefile.length(); i++)
			{
				ch[i] = savefile[i];
			}
			for (int i = 0; i < savefile.length(); i++)
			{
				Data.insert(ch[i], counttotalchar, filename);
			}
			ofstream linecounter(filename + "linecount.txt");
			linecounter << totalline;
		}
	}

	void setname()
	{
		system("cls");
		cout << "Enter The Name of the File" << endl;
		cin >> filename;
		string checker = "";
		ifstream readfile(filename + "file.txt");
		readfile >> checker;
		if (checker == "")
		{
			ofstream fname(filename + "file.txt");
			fname << filename;
			writingfile(filename);
		}
		else
		{
			system("cls");
			cout << "--------------------------------------" << endl;
			cout << "-----------File Already Exists -------" << endl;
			cout << "--------------------------------------" << endl;
			_getch();
			system("cls");
		}
	}
	void writingold(string filename, int totalcount)
	{
		totalline = totalcount;
		bool flag = true;
		while (flag)
		{
			string savefile;
			getline(cin, savefile);
			if (savefile == "#save")
			{
				flag = false;
				return;
			}
			int counttotalchar = savefile.length();
			char * ch = new char[savefile.length()];
			for (int i = 0; i < savefile.length(); i++)
			{
				ch[i] = savefile[i];
			}
			for (int i = 0; i < savefile.length(); i++)
			{
				Data.insert(ch[i], counttotalchar, filename);
			}
			ofstream linecounter(filename + "linecount.txt");
			linecounter << totalline;

		}
	}
};

class readfile
{
public:
	string savefile;
	readfile()
	{
		savefile = "";
	}

	void reading()
	{
		cout << "Enter The File Name Which you want to open" << endl;
		int countlast = 0;
		cin >> savefile;
		ifstream readfilen(savefile + "file.txt");
		string oldfilecheck = "";
		readfilen >> oldfilecheck;
		if (oldfilecheck != "")
		{
			int readingcount = 0;
			ifstream readcounts(savefile + "linecount.txt");
			readcounts >> readingcount;
			countlast = readingcount;
			ifstream readfileold(savefile + "sample.txt");
			while (readingcount >= 0)
			{
				string typing;
				getline(readfileold, typing);
				cout << typing << endl;
				readingcount--;
			}
			bool flag2 = true;
			while (flag2)
			{
				cout << "------------ Press 1 If you want to Edit or Press 2 for exit -----------------------" << endl;
				int choice;
				cin >> choice;
				if (choice == 1)
				{
					File ob1;
					ob1.writingold(savefile, countlast);
				}
				else if (choice == 2)
				{
					flag2 = false;
				}
			}
		}
		else
		{
			system("cls");
			cout << "--------------------------------------" << endl;
			cout << "-----------No File Exists -------" << endl;
			cout << "--------------------------------------" << endl;
			_getch();
		}
	}
};

void main_menu()
{
	cout << "--------------------------------------" << endl;
	cout << "------------- Notepad C++ ------------" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Press 1- To Make New File" << endl;
	cout << "Press 2- To open Exsisting File" << endl;
	cout << "Press 0-  To Exit The Program" << endl;
}

int main()
{
	char choice = 'n';
	bool flag = true;
	while (flag)
	{
		main_menu();
		cin >> choice;
		if (choice == '1')
		{
			system("cls");
			File start;
			start.setname();
		}
		else if (choice == '2')
		{
			system("cls");


			readfile ob2;
			ob2.reading();
		}
		else if (choice == '0')
		{
			flag = false;
		}
		else
		{
			cout << "Please Enter Write Option" << endl;
			_getch();
			system("cls");

		}
	}
	
	system("pause");
	return 0;
}

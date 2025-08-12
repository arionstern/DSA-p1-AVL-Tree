#include <iostream>
#include "AVLTree.h"
#include <sstream>
#include <iomanip>


using namespace std;

int main(){


	AVLTree tree;
	string numCommands;


	getline(cin, numCommands);
	int commandCount = stoi(numCommands);

	vector<string> commands;


	//read and store commands
	for(int i = 0; i < commandCount; i++)
	{
		string line;
		getline(cin, line);
		commands.push_back(line);
	}

	//process commands
	for(const string& line : commands)
	{
		istringstream iss(line);
		string command;
		iss >> command;

		if(command == "insert")
		{
			string name, ufid;

			char quote;
			if (!(iss >> quote) || quote != '"')
			{
				cout << "unsuccessful" << endl;
				continue;
			}

			std::getline(iss, name, '"');
			iss >> ufid;
			tree.insert(name, ufid);
		}

		else if (command == "search")
		{
			string input;
			getline(iss >> ws, input);
			tree.search(input);
		}
		else if (command == "remove")
		{
			string ufid;
			iss >> ufid;
			tree.remove(ufid);
		}

		else if (command == "printInorder")
			tree.printInorder();
		else if (command == "printPreorder")
			tree.printPreorder();
		else if (command == "printPostorder")
			tree.printPostorder();
		else if (command == "printLevelCount")
			tree.printLevelCount();


		else if(command == "removeInorder")
		{
			int N;
			iss >> N;
			tree.removeInorder(N);
		}

		else cout<<"unsuccessful"<<endl;

	}


	return 0;
}

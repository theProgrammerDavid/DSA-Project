#define  _HAS_EXCEPTIONS 0	//visual studio specific define statement
//#include <algorithm>
//#include <cassert>
#include <iostream>
#include <string>
#include <string.h>
//STL files
#include <vector>
#include <queue>

using namespace std; 

#define MAX_CHILDREN 10
//define max children for an N ary tree. Not used here as
//i am using a std::vector<>


#define XAXIS 50
//number of columns in x axis to print the header


enum action { VIEW_SELECTED_FOLDER, ADD_FILE, ADD_FOLDER, MODIFY_FILE, MODIFY_FOLDER };
//presets to store the user action


inline void printHeader() {
	
	cout << "\n";
	for (int i = 0; i < XAXIS;i++)cout << "-";
	cout << "\n";
}

inline void help() {

	printHeader();
	cout << "\n1. select folder\n2.View selcted folder\n3. Add File\n4.Add Folder\n5.Modify file\n6.Modify Folder\n7.Exit" << endl;
	printHeader();

}


class file {

public:

	file() {
		this->fileData = "";
		this->fileName = "";
	}
	string fileName;
	string fileData;

	~file() {
		delete this;
	}

};


// Represents a node of an n-ary tree . Like a folder in windows explorer
class Node
{
public:
	string folderName;
	vector<Node *>child;
	vector<file*> files;

	Node() {
		folderName = "";
	}
};

//global variable declarations to use in the program
	Node selectFile;
	int selectAction;
	string ModFileName;
	string ModFolderName;

// function to create a new tree node 
file *newfile() {

	printHeader();

	file *f = new file;	//dynamic memory allocation

	cout << "Enter File Name :";
	cin >> f->fileName;

	cout << "Enter file data : ";
	cin.ignore();
	getline(cin, f->fileData, '\n');
	

	return f;
}


Node *newFolder()
{
	//for a new folder, we first ask the user to enter a new file then store  it in the folder
	printHeader();
		
	file *f = newfile();

	Node *temp = new Node;
	temp->files.push_back(f);	
	
	cout << "\nEnter folder name : ";
	cin>>temp->folderName;

	

	return temp;
}

void addChild(Node * root, Node* child) {
	if (root != NULL && child != NULL) {
		root->child.push_back(child);
	}
}







void findFolder(Node* root) {
	//uses the concept of bfs and implements it using an STL queue
	if (root == NULL)
		return;
	queue<Node *> q;
	q.push(root);

	while (!q.empty()) {

		int n = q.size();

		while (n > 0) {
			Node *p = q.front();
			q.pop();

			if (p->folderName == selectFile.folderName) {
				//we have found the folder
				cout << "\nfolder found\n";
				//now we print the names of the files in the folder
				if (selectAction == VIEW_SELECTED_FOLDER)
				{
				for (int i = 0; i < p->files.size(); i++) {
					cout << "\nFiles:\n";
					cout << i + 1 << "] " << p->files[i]->fileName<<"\n";
					cout << "data : " << p->files[i]->fileData;
					cout << "\n";
				}

				for (int i = 0; i < p->child.size(); i++) {
					cout << "\nFolders:\n";
					cout << i + 1 << p->child[i]->folderName;
					cout << "\n";
				}

				return;
				}
				else if (selectAction == ADD_FILE) {
					file *newFile = newfile();
					p->files.push_back(newFile);
					return;
				}
				else if (selectAction == ADD_FOLDER) {
					Node *newNode = newFolder();
					p->child.push_back(newNode);
					return;
				}
				else if (selectAction == MODIFY_FOLDER) {
					cout << "Enter new folder name :";
					cin>>p->folderName;
					return;

				}
				else if (selectAction == MODIFY_FILE) {

					for (int h = 0; h < p->files.size(); h++) {

						if (p->files[h]->fileName == ModFileName) {
							cout << "\nFileFound. Enter new File data :";
							cin >> p->files[h]->fileData;
						}

					}

					return;
				}
			}

			for (int i = 0; i < p->child.size(); i++)
				q.push(p->child[i]);
			n--;
		}
	}
}


int main()
{

	int choice = 0;
	
	Node *root = new Node;
	root->folderName = "root";
	selectFile.folderName = "root";
	
	cout << "\nFirst folder is called root";

	help();
	//menu for easy reading
	// "\n1. select folder\n2.View selcted folder\n3. Add File\n4.Add Folder\n5.Modify file\n6.Modify Folder\n7.Exit";
	while (true) {

		printHeader();
		cout << "Enter Option : ";
		cin >> choice;
		cout << "\n\n";
		switch (choice) {



		case 1:
			//Select Folder
			cout << "\nEnter name of folder to select :";
			cin>>selectFile.folderName;
			break;

		case 2:
			//View Selected Folder
			selectAction = VIEW_SELECTED_FOLDER;
			findFolder(root);
			break;

		case 3:
			//Add File
			selectAction = ADD_FILE;
			findFolder(root);
			break;

		case 4:
			//Add Folder
			cout << "\nPlease add a file in the new folder first\n";
			selectAction = ADD_FOLDER;
			findFolder(root);
			break;

		case 5:
			//modify file
			selectAction = MODIFY_FILE;
			cout << "Enter name of file to modify : ";
			cin >> ModFileName;
			findFolder(root);
			break;

		case 6:
			//modify folder
			selectAction = MODIFY_FOLDER;
			cout << "Enter then name of the folder to change: ";
			cin >> ModFolderName;
			findFolder(root);
			break;

		case 7:
			//exit
			printHeader();
			exit(0);
			break;

		}
		cout << "\n\n";
		help();
	}
	return 0;
}
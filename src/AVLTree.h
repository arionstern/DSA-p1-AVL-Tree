#ifndef AVLTREE_H
#define AVLTREE_H

#include <array>
#include <iostream>
#include <vector>
#include <stdexcept>
using std::string;

struct Node
{
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;

    Node(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    Node* root = nullptr;

    //helper functions:
    Node* insertHelper(Node* node, const string&, const string& ufid);

    void updateHeight(Node* node);
    int getHeight(Node* node);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);

    int getBalance(Node* node);

    bool checkDuplicate(const string& ufid);
    Node* searchByIDHelper(Node* node, string ufid);
    void searchByNameHelper(Node* node, string name, std::vector<string>& ids);

    void printNames(const std::vector<string>& names);

    Node* removeHelper(Node* node, string ufid);
    Node* findMin(Node* node);

    void findNthInorder(Node* node, int& N, string& ufid);

    void destroyTree(Node* node);

    int countNodes(Node* node);




public:
    //main commands
    void insert(const string& name, const string& ufid);
    void search (const string& input);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void remove(const string& ufid);
    void removeInorder(int N);


    //These are public for unit testing purposes but would be private otherwise
    void getInorderNames(Node* node, std::vector<string>& names);
    void getPreorderNames(Node* node, std::vector<string>& names);
    void getPostorderNames(Node* node, std::vector<string>& names);
    Node* getRoot();
    void getInorderIDs(Node* node, std::vector<string>& ufids);


    //destructor
    ~AVLTree();


};


#endif // AVLTREE_H

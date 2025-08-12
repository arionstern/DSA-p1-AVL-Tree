//
// Created by arist on 2/14/2025.
//

#include "AVLTree.h"
#include <regex>



int AVLTree::getHeight(Node* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

void AVLTree::updateHeight(Node* node)
{
    if (node == nullptr) return;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    node->height = 1 + std::max(leftHeight, rightHeight);
}

int AVLTree::getBalance(Node* node)
{
    if (node == nullptr)
        return 0;

    int balance = getHeight(node->left) - getHeight(node->right);

    return balance;
}


//used some code from lecture for rotations
Node* AVLTree::rotateLeft(Node* node)
{
    if (node == nullptr || node->right == nullptr)
        return node;

    Node* newParent = node->right;
    Node* grandchild = newParent->left;

    newParent->left = node;
    node->right = grandchild;

    updateHeight(node);
    updateHeight(newParent);

    return newParent;
}


Node* AVLTree::rotateRight(Node* node)
{
    if (node == nullptr || node->left == nullptr)
        return node;

    Node* newParent = node->left;
    Node* grandchild = newParent->right;

    newParent->right = node;
    node->left = grandchild;

    updateHeight(node);
    updateHeight(newParent);

    return newParent;
}





//calls insert helper function that is private
void AVLTree::insert(const string& name, const string& ufid)
{

//validate ufid
    if(ufid.length() != 8 || !std::regex_match(ufid, std::regex("[0-9]{8}")))
    {
        std::cout <<"unsuccessful" << std::endl;
        return;
    }

//validate name
    if(name.empty() || !std::regex_match(name, std::regex("^[A-Za-z\\s]+$")))
    {
        std::cout <<"unsuccessful" << std::endl;
        return;
    }

    // Check for duplicate
    if (checkDuplicate(ufid))
    {
        std::cout <<"unsuccessful" << std::endl;
        return;
    }

    //Insert
    this->root = insertHelper(this->root, name, ufid);
    std::cout << "successful" << std::endl;

}


//Used code from lecture slides
Node* AVLTree::insertHelper(Node* node, const string& name, const string& ufid)
{
    if(node==nullptr)
        return new Node(name, ufid);
    else if(ufid < node-> ufid)
    node->left=insertHelper(node->left,name, ufid);
    else if (ufid > node->ufid)
        node->right=insertHelper(node->right, name, ufid);


//find and update heights
    updateHeight(node);

//perform rotations
    if (getBalance(node) == -2)
    {
        //Right Left Case
        if (getBalance(node->right) == +1)
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        //Right Right case
        else
            node = rotateLeft(node);
    }
    else if (getBalance(node) == 2)
    {
        //Left Right Case
        if (getBalance(node->left) == -1)
        {
            node-> left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        //Left Left Case
        else
            node = rotateRight(node);
    }


    return node;
}

void AVLTree::search(const string& input)
{
    //IF GIVEN UFID
    if (std::regex_match(input, std::regex("[0-9]{8}"))) {
        Node* foundNode = searchByIDHelper(this->root, input);
        if (foundNode)
            std::cout << foundNode->name << std::endl;  // Print name for ID search
        else
            std::cout << "unsuccessful" << std::endl;
    }

    //IF GIVEN NAME
    else if (input.front() == '"' && input.back() == '"')
    {
        string name = input.substr(1, input.size() - 2);  //Remove quotes
        std::vector<string> ids;
        searchByNameHelper(this->root, name, ids);
        if (ids.empty())
        {
            std::cout << "unsuccessful" << std::endl;
        }
        else
        {
            for (const string& id : ids)
                std::cout << id << std::endl; //print each UFID
        }
    } else std::cout << "unsuccessful" << std::endl;


}

void AVLTree::searchByNameHelper(Node* node, string name, std::vector<string>& ids)
{
    if (node == nullptr)
        return;

    //preorder traversal
    if(node->name == name)
        ids.push_back(node-> ufid);
    searchByNameHelper(node->left, name, ids);
    searchByNameHelper(node->right, name, ids);

}

Node* AVLTree::searchByIDHelper(Node* node, string ufid)
{
    if (node == nullptr)
        return nullptr;

    if(ufid == node->ufid)
        return node;
    else if(ufid < node->ufid)
        return searchByIDHelper(node->left, ufid);
    else return searchByIDHelper(node->right, ufid);

}



bool AVLTree::checkDuplicate(const string& ufid)
{
   return (searchByIDHelper(this->root, ufid) != nullptr);
}




void AVLTree::getInorderNames(Node* node, std::vector<string>& names)
{
    if (node == nullptr)
        return;

    getInorderNames(node->left, names);
    names.push_back(node->name);
    getInorderNames(node->right, names);

}

void AVLTree::getPreorderNames(Node* node, std::vector<string>& names)
{
    if (node == nullptr)
        return;

    names.push_back(node->name);
    getPreorderNames(node->left, names);
    getPreorderNames(node->right, names);
}

void AVLTree::getPostorderNames(Node* node, std::vector<string>& names)
{
    if (node == nullptr)
        return;
    getPostorderNames(node->left, names);
    getPostorderNames(node->right, names);
    names.push_back(node->name);
}

//Helper for traversal print functions
void AVLTree::printNames(const std::vector<string>& names)
{
    if (names.empty())
    {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    for (size_t i = 0; i < names.size(); i++)
    {
        std::cout << names[i];
        if (i < names.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

void AVLTree::printInorder()
{
    std::vector<string> names;
    getInorderNames(this->root, names);
    printNames(names);

}


void AVLTree::printPreorder()
{
    std::vector<string> names;
    getPreorderNames(this->root, names);
    printNames(names);

}

void AVLTree::printPostorder()
{
    std::vector<string> names;
    getPostorderNames(this->root, names);
    printNames(names);

}

void AVLTree::remove(const string& ufid)
{
    if(!checkDuplicate(ufid))
    {
        std::cout<< "unsuccessful" << std::endl;
        return;
    }
    this->root = removeHelper(this->root, ufid);
    std::cout<< "successful" << std::endl;
}

Node* AVLTree::removeHelper(Node* node, string ufid)
{
    if (node == nullptr)
        return nullptr;

    if(ufid < node->ufid)
        node->left = removeHelper(node->left, ufid);
    else if(ufid > node->ufid)
        node->right = removeHelper(node->right, ufid);
    else
    {
        //case 1: no children
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        //case 2: one child (right child exists)
        else if (node->left == nullptr)
        {
            Node* temp = node->right;
            node->right = nullptr;
            delete node;
            return temp;
        }

        //case 3: one child (left child exists)
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            node->left = nullptr;
            delete node;
            return temp;
        }

        //case 4: two children
        else
        {
            Node* successor = findMin(node->right);
            node->ufid = successor->ufid;
            node->name = successor->name;
            node->right = removeHelper(node->right, successor->ufid);
        }

    }

    //update heights and balances

    updateHeight(node);
    int balance = getBalance(node);

    // Left Heavy
    if (balance > 1)
    {
        if (getBalance(node->left) >= 0)
            return rotateRight(node);
        else
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    // Right Heavy
    if (balance < -1)
    {
        if (getBalance(node->right) <= 0)
            return rotateLeft(node);
        else
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}

//used to find inorder successor
Node* AVLTree::findMin(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

//used for removeInorder
int AVLTree::countNodes(Node* node)
{
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void AVLTree::removeInorder(int N)
{
    if (N < 0 || N >= countNodes(this->root))  // Edge case check
    {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    string ufid = "";
    findNthInorder(this->root, N, ufid);
    remove(ufid);
}



void AVLTree::findNthInorder(Node* node, int& N, string& ufid) {
    if (node == nullptr || !ufid.empty()) return;

    findNthInorder(node->left, N, ufid);

    if (ufid.empty()) {
        if (N == 0) {
            ufid = node->ufid;
            return;
        }
        N--;
    }

    findNthInorder(node->right, N, ufid);
}




void AVLTree::printLevelCount()
{
    if (this->root == nullptr)
    {
        std::cout << "0" << std::endl;
        return;
    }

    std::cout << getHeight(this->root) << std::endl;
}

Node* AVLTree::getRoot()
{
    return this->root;
}

void AVLTree::getInorderIDs(Node* node, std::vector<string>& ufids) {
    if (node == nullptr) return;

    getInorderIDs(node->left, ufids);
    ufids.push_back(node->ufid);
    getInorderIDs(node->right, ufids);
}

AVLTree::~AVLTree()
{
    destroyTree(root);
}

void AVLTree::destroyTree(Node* node)
{
    if (node == nullptr) return;

    destroyTree(node->left);
    destroyTree(node->right);

    node->left = nullptr;
    node->right = nullptr;

    delete node;
}



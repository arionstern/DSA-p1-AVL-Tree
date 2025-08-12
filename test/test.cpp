/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <random>
#include <set>
#include <sstream>

#include "AVLTree.h"



using namespace std;



// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[flag]"){
	// instantiate any class members that you need to test here
	int one = 1;

	// anything that evaluates to false in a REQUIRE block will result in a failing test
	REQUIRE(one == 1); // fix me!

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(true); // also fix me!
}

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 1;

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.

TEST_CASE("Example BST Insert", "[flag]"){

		// MyAVLTree tree;   // Create a Tree object
		// tree.insert(3);
		// tree.insert(2);
		// tree.insert(1);
		// std::vector<int> actualOutput = tree.inorder();
		// std::vector<int> expectedOutput = {1, 2, 3};
		// REQUIRE(expectedOutput.size() == actualOutput.size());
		// REQUIRE(actualOutput == expectedOutput);
		//

}


string captureOutput(function<void()> func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    func();
    cout.rdbuf(old);
    return buffer.str();
}

TEST_CASE("Insert with Empty Name", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){ tree.insert("", "12345678"); }) == "unsuccessful\n");
}

TEST_CASE("Insert Name With Only Spaces", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){ tree.insert("    ", "12345678"); }) == "successful\n");
    REQUIRE(captureOutput([&](){ tree.search("\"    \""); }) == "12345678\n");
}

TEST_CASE("Insert and Search Name with Multiple Spaces", "[AVL]") {
    AVLTree tree;
    tree.insert("John  Doe", "87654321");

    REQUIRE(captureOutput([&](){ tree.search("\"John  Doe\""); }) == "87654321\n");
    REQUIRE(captureOutput([&](){ tree.search("\"John Doe\""); }) == "unsuccessful\n");
}

TEST_CASE("Insert Duplicate Name with Different UFIDs", "[AVL]") {
    AVLTree tree;
    tree.insert("Alice", "11111111");
    tree.insert("Alice", "22222222");

    REQUIRE(captureOutput([&](){ tree.search("\"Alice\""); }) == "11111111\n22222222\n");
}


TEST_CASE("Insert with Invalid UFID", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){tree.insert("Alice", "123");}) == "unsuccessful\n");  // Too short
    REQUIRE(captureOutput([&](){tree.insert("Bob", "abcdefgh");}) == "unsuccessful\n"); // Not numeric
}


TEST_CASE("Insert Duplicate UFID", "[AVL]") {
    AVLTree tree;
    tree.insert("Alice", "12345678");
    REQUIRE(captureOutput([&](){ tree.insert("Bob", "12345678"); }) == "unsuccessful\n");  // Same UFID as Alice
}


TEST_CASE("Remove Nonexistent ID", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){ tree.remove("99999999"); }) == "unsuccessful\n");
}

TEST_CASE("Remove Inorder Out of Bounds", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    REQUIRE(captureOutput([&](){ tree.removeInorder(10); }) == "unsuccessful\n");
}


TEST_CASE("Insert and Inorder Traversal", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");

    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Alice, Bob, Charlie\n");
}

TEST_CASE("Insert and Preorder Traversal", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");

    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "Bob, Alice, Charlie\n");
}

TEST_CASE("Insert and Postorder Traversal", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");

    REQUIRE(captureOutput([&](){ tree.printPostorder(); }) == "Alice, Charlie, Bob\n");
}


TEST_CASE("Search by UFID", "[AVL]") {
    AVLTree tree;
    tree.insert("David", "56781234");
    tree.insert("Eve", "87654321");

    REQUIRE(captureOutput([&](){ tree.search("56781234"); }) == "David\n");
    REQUIRE(captureOutput([&](){ tree.search("87654321"); }) == "Eve\n");
    REQUIRE(captureOutput([&](){ tree.search("99999999"); }) == "unsuccessful\n");
}


TEST_CASE("Remove Node and Check Inorder", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");

    // Remove leaf node (Alice)
    tree.remove("12345678");
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Bob, Charlie\n");

    // Remove node with one child (Charlie)
    tree.insert("David", "56781234");
    tree.remove("87654321");
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Bob, David\n");

    // Remove node with two children (Bob)
    tree.insert("Eve", "67891234");
    tree.remove("23456789");
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "David, Eve\n");
}



TEST_CASE("Print Level Count", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){ tree.printLevelCount(); }) == "0\n");

    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");
    std::cout << "Tree structure after insertion of Bob:\n";
    tree.printPreorder();
    tree.printInorder();

    REQUIRE(captureOutput([&](){ tree.printLevelCount(); }) == "2\n");
}


TEST_CASE("Remove Inorder", "[AVL]") {
    AVLTree tree;
    tree.insert("Charlie", "87654321");
    tree.insert("Alice", "12345678");
    tree.insert("Bob", "23456789");




    // Perform removal
    std::string removeOutput = captureOutput([&](){ tree.removeInorder(1); });
    REQUIRE(removeOutput == "successful\n");


    // Validate that Bob was removed
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Alice, Charlie\n");

    // Test out-of-bounds removal
    REQUIRE(captureOutput([&](){ tree.removeInorder(10); }) == "unsuccessful\n");
}

TEST_CASE("Remove Root Repeatedly Until Tree is Empty", "[AVL]") {
    AVLTree tree;
    tree.insert("Root", "50000000");
    tree.insert("Left", "20000000");
    tree.insert("Right", "80000000");

    tree.remove("50000000");  // Remove root
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Left, Right\n");

    tree.remove("20000000");  // Remove new root
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Right\n");

    tree.remove("80000000");  // Remove last node
    REQUIRE(captureOutput([&](){ tree.printLevelCount(); }) == "0\n");  // Tree should be empty
}

TEST_CASE("Remove Inorder on Single-Node Tree", "[AVL]") {
    AVLTree tree;
    tree.insert("Solo", "99999999");

    tree.removeInorder(0);  //Should remove the only node
    REQUIRE(captureOutput([&](){ tree.printLevelCount(); }) == "0\n");  //Tree should be empty
}

TEST_CASE("Print Traversals on Empty Tree", "[AVL]") {
    AVLTree tree;
    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "unsuccessful\n");
    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "unsuccessful\n");
    REQUIRE(captureOutput([&](){ tree.printPostorder(); }) == "unsuccessful\n");
}


TEST_CASE("Insert Alice, Bob, and Charlie, Verify Inorder Traversal", "[AVL]") {
    AVLTree tree;

    tree.insert("Bob", "12345679");
    tree.insert("Alice", "12345678");
    tree.insert("Charlie", "23456789");


    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "Alice, Bob, Charlie\n");
}



TEST_CASE("Test Insert and All Four Rotation Cases", "[AVL]") {
    AVLTree tree;

    // **LL Rotation (Right Rotation)**
    tree.insert("C", "30000000");
    tree.insert("B", "20000000");
    tree.insert("A", "10000000");

    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "A, B, C\n");
    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "B, A, C\n");

    // **RR Rotation (Left Rotation)**
    tree.insert("D", "40000000");
    tree.insert("E", "50000000");

    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "A, B, C, D, E\n");
    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "B, A, D, C, E\n");

    // **LR Rotation (Left-Right Rotation)**
    tree.insert("F", "60000000");
    tree.insert("G", "70000000");
    tree.insert("H", "65000000");

    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "A, B, C, D, E, F, H, G\n");
    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "D, B, A, C, F, E, G, H\n");

    // **RL Rotation (Right-Left Rotation)**
    tree.insert("I", "80000000");
    tree.insert("J", "90000000");
    tree.insert("K", "85000000");

    REQUIRE(captureOutput([&](){ tree.printInorder(); }) == "A, B, C, D, E, F, H, G, I, K, J\n");
    REQUIRE(captureOutput([&](){ tree.printPreorder(); }) == "D, B, A, C, G, F, E, H, K, I, J\n");
}



//Used the link provided and ChatGPT to help with this test case
//Needed help with generating and removing random ids and set functions
TEST_CASE("Insert 100 Nodes, Remove 10 Randomly, and Check Inorder", "[AVL]") {
    AVLTree tree;
    std::set<int> insertedValues;
    std::vector<string> expectedOutput;

    // Generate 100 unique random UFIDs
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve",
                                   "Frank", "Grace", "Hannah", "Ian", "Jack"};

    while (insertedValues.size() < 100) {
        int randomValue = rand() % 90000000 + 10000000;  // Ensures 8-digit UFID
        string ufid = std::to_string(randomValue);

        if (insertedValues.insert(randomValue).second) {
            tree.insert(names[insertedValues.size() % names.size()], ufid);
            expectedOutput.push_back(ufid);
        }
    }

    // Sort the expected UFIDs numerically
    std::sort(expectedOutput.begin(), expectedOutput.end(), [](const string &a, const string &b) {
        return std::stoi(a) < std::stoi(b);
    });

    // Capture actual inorder traversal
    std::vector<string> actualOutput;
    tree.getInorderIDs(tree.getRoot(), actualOutput);
    REQUIRE(actualOutput == expectedOutput);

    // Remove 10 random elements from the tree
    std::vector<string> toRemove;
    auto it = insertedValues.begin();
    for (int i = 0; i < 10 && it != insertedValues.end(); i++, it++) {
        toRemove.push_back(std::to_string(*it));
    }

    for (const string &ufid : toRemove) {
        tree.remove(ufid);
        expectedOutput.erase(std::remove(expectedOutput.begin(), expectedOutput.end(), ufid), expectedOutput.end());
    }

    // Capture updated inorder traversal
    actualOutput.clear();
    tree.getInorderIDs(tree.getRoot(), actualOutput);
    REQUIRE(actualOutput == expectedOutput);  // Ensure AVL order after deletions
}

*/

//Arion Stern
//UFID: 38256771
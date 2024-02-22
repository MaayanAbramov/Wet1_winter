/*
 * A Rank/AVL Tree Tester to test your tree implementation
 *
 * Please Read the instructions in the README file before you start

 * You may add any additional functions you need.
 *
 * I would suggest first beginning with a simple tree and then moving on to a more complex one.
 *
 * G O O D  L U C K !
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
#include <assert.h>
#include "AvlTree.h"

/*
 * is_tree_valid - checks if the tree is valid, meaning that the tree is balanced and the rank is correct
 * @param root - the root of the tree
 * @return true if the tree is valid, false otherwise
 * Should use to make sure your tree is valid after every insertion and deletion
 * If your Node class doesn't use a parent pointer, remove lines 66-84
 * If your tree isn't a Rank Tree, remove lines 56-60
 * if assert happens, put breaking points in "return false" to see where the error is
 */

template<class Key,class Value>
bool AvlTree<Key, Value>::is_tree_valid(Node* root) {
    if (!root) {
        return true;
    }
    // Checks the height of every node is valid
    if (root->heightFromRoot != 1 + std::max(getHeight(root->left), getHeight(root->right))) {
        std::cout << "Height is not valid" << std::endl;
        return false;
    }
    if (!root->left && !root->right && root->heightFromRoot != 0) {
        std::cout << "Leaf Height is not valid" << std::endl;
        return false;
    }
    //checks the Tree is a Binary Search Tree
    if (root->left && root->left->key >= root->key) {
        std::cout << "Left son is not smaller than root" << std::endl;
        return false;
    }
    if (root->right && root->right->key <= root->key) {
        std::cout << "Right son is not bigger than root" << std::endl;
        return false;
    }
    //checks that the rank of every node is valid
    /*if (root->weight != 1 + getWeight(root->left_son) + getWeight(root->right_son)) {
        std::cout << "Rank is not valid" << std::endl;
        return false;
    }*/
    //checks that the Balance Factor of every node is valid
    if (std::abs(BalanceFactor(root)) > 1) {
        std::cout << "Balance Factor is not valid" << std::endl;
        return false;
    }
    //checks that the parent pointer is valid
    if (root->father) {
        if (root->father->left != root && root->father->right != root) {
            std::cout << "Parent pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->left) {
        if (root->left->father != root) {
            std::cout << "Parent's Left Son pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->right) {
        if (root->right->father != root) {
            std::cout << "Parent's Right Son pointer is not valid" << std::endl;
            return false;
        }
    }
    return is_tree_valid(root->left) && is_tree_valid(root->right);
}

template<class Key, class Value>
int AvlTree<Key, Value>::getHeight(Node* root) {
    if (!root) {
        return -1;
    }
    return root->heightFromRoot;
}


template<class Key, class Value>
int AvlTree<Key, Value>::BalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int Rheight = -1;
    int Lheight = -1;
    if (node->right != nullptr) {
        Rheight = node->right->heightFromRoot;
    }
    if (node->left != nullptr) {
        Lheight = node->left->heightFromRoot;
    }
    return Lheight - Rheight;
}
/*
template<class Key, class Value>
int AvlTree<Key, Value>::getWeight(Node* root) {
    if (!root) {
        return 0;
    }
    return root->weight;
}

*/
// A function to print the tree
template<class Key, class Value>
void AvlTree<Key, Value>::print2DHelper(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right_son child first
    print2DHelper(root->right, space);

    // Print current node after space
    std::cout<<std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout<<root->value<<"\n";

    // Process left_son child
    print2DHelper(root->left, space);
}

// Wrapper over print2DHelper()
template<class Key, class Value>
void AvlTree<Key, Value>::print2D(Node* root)
{
    // Pass initial space count as 0
    print2DHelper(root, 0);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
}
int main(){
    AvlTree<int,int> tree;
    std::vector<int> vector;
    int size = 0;
    int count = 0;
    //determines the size of the tree - change i to test different sizes
    for (int i = 1; i < 200; i++) {
        vector.push_back(i);
        size = i;
    }

    //randomizes the vector, and k is the number of trees to randomize - change k to test different numbers of trees
    for (int k = 1; k < 20; ++k) {
        count = k;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        std::cout<<"\n     Creating The Tree \n"<<std::endl;
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            cout << "now inserte ------------------------------ " << *it << endl;
            tree.insertAux(*it,*it);
            assert(tree.is_tree_valid(tree.root));
            if(tree.is_tree_valid(tree.root)){}
            tree.print2D(tree.root);
        }
        tree.printTreeWithInfo(tree.root, 0, '-');
        std::cout<<"    Deleting The Tree \n"<<std::endl;
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            cout << "now remove ------------------------------ " << *it << endl;
            tree.remove(*it);
            assert(tree.is_tree_valid(tree.root));
            tree.print2D(tree.root);

        }
        if(k != 1){
            std::cout<<"A New Tree begins \n"<<std::endl;
        }
        tree.DeleteWholeTree(tree.root);
        tree.root= nullptr;
    }
    std::cout<<" S U C C E S S"<<std::endl;
    std::cout << '\n';
    if(size < 100 && count < 6){
        std::cout << "Great! Now try a Larger Tree and more Trees " << std::endl;
        std::cout << '\n';
    }
    else if(size < 100){
        std::cout << "Great! Now try a Larger Tree " << std::endl;
        std::cout << '\n';
    }
    else if(count < 6){
        std::cout << "Great! Now try more Trees " << std::endl;
        std::cout << '\n';
    }
    else{
        std::cout << "    Great! " << std::endl;
        std::cout << '\n';
    }

    return 0;
}


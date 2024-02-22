#include <iostream>
#include "AvlTree.h"

int main() {
    AvlTree<int, int> tree;

    /*tree.insertAux(5, 2);
    tree.insertAux(2, 2);
    tree.insertAux(6, 2);
    tree.insertAux(1, 2);
    tree.insertAux(3, 2);
    tree.insertAux(7, 2);
    tree.insertAux(4, 2);


    tree.printTreeWithInfo(tree.root, 0, '-');
    tree.remove(5);
    tree.printTreeWithInfo(tree.root, 0, '-');
*/
    AvlTree<int,int>::Node* res = AvlTree<int,int>::createCompleteTree(10);
    tree.root = res;
    tree.numOfNodes = 10;
    tree.printTreeWithInfo(tree.root, 0, '-');
    int index = 0;
    int arrayOfKeys[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrayOfValues[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    tree.inorderFromArrayToTree(tree.root, arrayOfKeys, arrayOfValues, &index);
    tree.printTreeWithInfo(tree.root, 0, '-');


    return 0;
}
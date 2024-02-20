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
    AvlTree<int,int>::Node* res = AvlTree<int,int>::createCompleteTree(11);
    tree.root = res;
    tree.printTreeWithInfo(tree.root, 0, '-');



    return 0;
}
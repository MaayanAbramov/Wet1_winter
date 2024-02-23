//
// Created by Jenya on 29.05.2023.
//

#ifndef OLDTREE_H
#define OLDTREE_H

#define H_OF_LEAF 0
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;


template <class T>
class AvlTree {
public:
    class Node {
    public:
        T m_data;
        int m_height;
        int m_balance_factor;
        Node* m_ptr_left;
        Node* m_ptr_right;
        Node* m_ptr_father;
        explicit Node(const T &data) : m_data(data), m_height(H_OF_LEAF), m_balance_factor(0), m_ptr_left(nullptr),
                                       m_ptr_right(nullptr), m_ptr_father(nullptr) {}
        T getData() { return this->m_data; }
    };
    Node* ptr_main_root;

    AvlTree() : ptr_main_root(nullptr) {}

    // the argument is only for the recursive call15
    void deleteNodesOfTree(Node* curr_node) {
        //if we got to the leaf's child (which does not exist)
        if (curr_node == nullptr) {
            return;
        }

        //recursive calls
        deleteNodesOfTree(curr_node->m_ptr_right);
        deleteNodesOfTree(curr_node->m_ptr_left);
        delete curr_node;
    }

    ~AvlTree() {
        deleteNodesOfTree(ptr_main_root);
    }


    // a function that gets a key
    // returns true if the given key is in the tree
    bool is_key_exists(Node* main_root, const T& key) {
        if (main_root == nullptr) {
            return false;
        }

        if (*(main_root->m_data) == *key) {
            return true;
        }
        else if (*(main_root->m_data) < *key){
            return is_key_exists(main_root->m_ptr_right, key);
        }
        else if ((*main_root->m_data) > *key) {
            return is_key_exists(main_root->m_ptr_left, key);
        }
        return false; // doesn't suppose to get here
    }


    // a function that gets a key
    // returns the pointer to a node with a given key
    // returns nullptr if a key does not exist
    Node* find_pointer(Node* ptr_node, const T& key) {
        bool if_exists = is_key_exists(ptr_main_root, key);
        if (!if_exists) {
            return nullptr;
        }

        if (*(ptr_node->m_data) == *key) {
            return ptr_node;
        }
        else if (*(ptr_node->m_data) < *key) {
            return find_pointer(ptr_node->m_ptr_right, key);
        }
        else {
            return find_pointer(ptr_node->m_ptr_left, key);
        }
    }


private:
    //a function that gets a pointer to a node
    // returns the height of a node in a tree
    int height(Node* node_ptr) {
        int right_height, left_height;

        if (node_ptr == nullptr) {
            return -1;
        }
        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            return 0;
        }

        if (node_ptr->m_ptr_right == nullptr) {
            right_height = 0;
        } else {
            right_height = 1 + node_ptr->m_ptr_right->m_height;
        }

        if (node_ptr->m_ptr_left == nullptr) {
            left_height = 0;
        } else {
            left_height = 1 + node_ptr->m_ptr_left->m_height;
        }

        return std::max(right_height, left_height);
    }


    // a function that gets a node
    // updates a height and a balance factor of a given node
    // does not return anything
    void update(Node* source) {
        if(source == nullptr)
            return;
        source->m_height = height(source);
        source->m_balance_factor = difference(source);
    }


    // a function that gets a pointer to a node
    // returns a value that indicates whether the subtree is balanced
    // NOTICE: this function is not supposed to get nullptr!
    int difference(Node* node_ptr) {
        //a pointer to a subtree with only one node
        if (node_ptr->m_ptr_right == nullptr && node_ptr->m_ptr_left == nullptr) {
            return 0;
        }
            //a pointer to a subtree with only two nodes -> (a root and a left leaf)
        else if (node_ptr->m_ptr_right == nullptr) {
            return node_ptr->m_ptr_left->m_height - (-1);
        }
            //a pointer to a subtree with only two nodes -> (a root and a right leaf)
        else if (node_ptr->m_ptr_left == nullptr) {
            return -1-node_ptr->m_ptr_right->m_height;
        }
            //a pointer to a subtree with two sons or more
        else {
            return node_ptr->m_ptr_left->m_height - node_ptr->m_ptr_right->m_height;
        }
    }


    /****** Helper functions ******/

    // a function that gets a pointer to a node
    // returns the root of the tree to which a given node belongs
    Node* find_main_root(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->m_ptr_father == nullptr) {
            return node;
        }
        return find_main_root(node->m_ptr_father);
    }


    // a function that gets a pointer to a root and a pointer to a node v
    // returns the father inorder (or grandfather, or grand-grand father..)
    Node* distant_grandfather_inorder(Node* ptr_node, Node* ptr_node_v) {
        //the right leaf in the edge has no father
        if (ptr_node_v->m_ptr_father == nullptr) {
            return nullptr;
        }

        if (ptr_node_v->m_ptr_father->m_ptr_left == ptr_node_v) {
            return ptr_node_v->m_ptr_father;
        }
        else {
            return distant_grandfather_inorder(ptr_node, ptr_node_v->m_ptr_father);
        }
        return nullptr; // does not suppose to get here
    }


    // a function that gets a pointer to a root and a pointer to a node v
    // returns a pointer to his consecutive in inorder
    // return nullptr if there is no next inorder value
    Node* find_next_inorder(Node* node_ptr, Node* node_ptr_v) {
        if ((node_ptr_v->m_ptr_right == nullptr) &&
            ((node_ptr_v->m_ptr_father!= nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left != nullptr) &&
             (node_ptr_v->m_ptr_father->m_ptr_left == node_ptr_v))) {
            return node_ptr_v->m_ptr_father;
        }

            // if node_ptr_v->m_ptr_right != nullptr
        else if (node_ptr_v->m_ptr_right != nullptr) {
            return distant_son(node_ptr_v->m_ptr_right);
        }

        else {
            return distant_grandfather_inorder(node_ptr, node_ptr_v);
        }
    }

    // a function that gets a pointer to a node v
    // returns the leftmost leaf of a node v
    Node* distant_son(Node* node_ptr_v) {
        if (node_ptr_v->m_ptr_left == nullptr) {
            return node_ptr_v;
        }

        return distant_son(node_ptr_v->m_ptr_left);
    }



    /****** Rotation functions ******/

    // a function that does Left Left rotation
    // NOTICE: this function is not supposed to get nullptr!
    Node* left_left_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_left;

        if (tempA != nullptr) {
            parent->m_ptr_left = tempA->m_ptr_right;
            tempA->m_ptr_right = parent;
            //cout << "did an action" << endl;

            // changing heights
            update(parent);
            update(tempA);

            // changing pointers to father
            tempA->m_ptr_father = parent->m_ptr_father;
            parent->m_ptr_father = tempA;

            if (parent->m_ptr_left != nullptr) {
                parent->m_ptr_left->m_ptr_father = parent;
            }
        }
        return tempA;
    }

    // a function that does Right Right rotation
    // NOTICE: this function is not supposed to get nullptr!
    Node* right_right_rotation(Node* parent) {
        Node* tempA;
        tempA = parent->m_ptr_right;

        if (tempA != nullptr) {
            parent->m_ptr_right = tempA->m_ptr_left;
            tempA->m_ptr_left = parent;

            // changing heights
            update(parent);
            update(tempA);

            // changing pointers to father
            tempA->m_ptr_father = parent->m_ptr_father;
            parent->m_ptr_father = tempA;

            if (parent->m_ptr_right != nullptr) {
                parent->m_ptr_right->m_ptr_father = parent;
            }
        }
        return tempA;
    }

    // a function that does Left Right rotation
    // NOTICE: this function is not supposed to get nullptr!
    Node* left_right_rotation(Node* parent) {
        if (parent->m_ptr_left == nullptr) {
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_left;
        Node* tempB;
        tempB = tempA->m_ptr_right;

        if (tempB != nullptr) {
            parent->m_ptr_left = tempB->m_ptr_right;
            tempB->m_ptr_right = parent;

            tempA->m_ptr_right = tempB->m_ptr_left;
            tempB->m_ptr_left = tempA;

            // changing heights
            update(parent);
            update(tempA);
            update(tempB);

            // changing pointers to father
            tempB->m_ptr_father = parent->m_ptr_father;
            tempA->m_ptr_father = tempB;
            parent->m_ptr_father = tempB;

            if (tempA->m_ptr_right != nullptr) {
                tempA->m_ptr_right->m_ptr_father = tempA; // Bl
            }
            if (parent->m_ptr_left != nullptr) {
                parent->m_ptr_left->m_ptr_father = parent; // Br
            }
        }
        return tempB;
    }

    // a function that does Right Left rotation
    // NOTICE: this function is not supposed to get nullptr!
    Node* right_left_rotation(Node* parent) {
        if (parent->m_ptr_right == nullptr) {
            return parent;
        }

        Node* tempA;
        tempA = parent->m_ptr_right;
        Node* tempB;
        tempB = tempA->m_ptr_left;

        if (tempB != nullptr) {
            parent->m_ptr_right = tempB->m_ptr_left;
            tempB->m_ptr_left = parent;

            tempA->m_ptr_left = tempB->m_ptr_right;
            tempB->m_ptr_right = tempA;

            // changing heights
            update(parent);
            update(tempA);
            update(tempB);

            // changing pointers to father
            tempB->m_ptr_father = parent->m_ptr_father;
            tempA->m_ptr_father = tempB;
            parent->m_ptr_father = tempB;

            if (parent->m_ptr_right != nullptr) {
                parent->m_ptr_right->m_ptr_father = parent;
            }
            if (tempA->m_ptr_left != nullptr) {
                tempA->m_ptr_left->m_ptr_father = tempA;
            }
        }
        return tempB;
    }


    /****** Balance function ******/

    // a function that gets a pointer to a node
    // balances the tree (if needed)
    // returns a pointer to the same node
    Node* balance(Node* ptr_node) {
        int balance_factor = ptr_node->m_balance_factor;

        if (balance_factor == 2) {
            if (difference(ptr_node->m_ptr_left) >=0) {
                ptr_node = left_left_rotation(ptr_node);
            }
            else if (difference(ptr_node->m_ptr_left) == -1) {
                ptr_node = left_right_rotation(ptr_node);
            }
        }
        else if (balance_factor == -2) {
            if (difference(ptr_node->m_ptr_right) <= 0) {
                ptr_node = right_right_rotation(ptr_node);
            }
            else if (difference(ptr_node->m_ptr_right) == 1) {
                ptr_node = right_left_rotation(ptr_node);
            }
        }
        return ptr_node;
    }




public:
    /****** Print functions ******/

    // a function that gets a pointer to the node
    // prints the subtree of a node
    void printNode(typename AvlTree<T>::Node *node, int level) {
        if (node == nullptr) {
            return;
        }

        printNode(node->m_ptr_right, level + 1);
        std::cout << std::setw(4 * level) << "" << node->m_data << std::endl;
        printNode(node->m_ptr_left, level + 1);
    }

    // a function that gets an AvLTree
    // prints the whole tree (from the root)
    void printAvlTree(const AvlTree<T> &avl) {
        printNode(avl.ptr_main_root, 0);
    }


    /****** Insert function ******/

    // a function that gets a pointer to a root and a key
    // creates a new node and inserts it to the tree
    // keeps the tree avl balanced
    Node* insert(Node* source, const T& key) {
        if (source == nullptr) {
            source = new Node(key);

            if (ptr_main_root == nullptr) {
                ptr_main_root = source;
            }
            return source;
        }

        else if(*(source->m_data) > *key) {
            auto temp = insert(source->m_ptr_left, key);
            source->m_ptr_left = temp;
            temp->m_ptr_father = source;
            update(source);
            source = balance(source); // !!!
        }

        else if (*(source->m_data) < *key) {
            auto temp = insert(source->m_ptr_right, key);
            source->m_ptr_right = temp;
            temp->m_ptr_father = source;
            update(source);
            source = balance(source);
        }
        ptr_main_root = find_main_root(source);
        return source;
    }



    /****** Remove node function ******/

    // a function that gets a pointer to a root and a key
    // finds a pointer to a node with a given key
    // removes it from the tree
    // keeps the tree avl balanced
    void remove_node(Node* main_root, const T& key) {
        Node* ptr_v = find_pointer(main_root, key);
        if (ptr_v == nullptr) {
            return;
        }
        Node* temp = ptr_v->m_ptr_father;

        // if ptr_v is a leaf - delete it
        if (ptr_v->m_ptr_left == nullptr && ptr_v->m_ptr_right == nullptr) {
            // removes an only root of a tree
            if (temp == nullptr) {
                ptr_main_root = nullptr;
            }

                // if ptr_v is a left son
            else if (temp->m_ptr_left == ptr_v) {
                temp->m_ptr_left = nullptr;
            }
                // if ptr_v is a right son
            else {
                temp->m_ptr_right = nullptr;
            }

            ptr_v->m_ptr_father = nullptr;
            delete ptr_v;
        }

            // if ptr_v has only left son
        else if (ptr_v->m_ptr_left != nullptr && ptr_v->m_ptr_right == nullptr) {
            if (temp == nullptr) {
                ptr_main_root = ptr_v->m_ptr_left;
            }

            // checks if ptr_v is a left son or a right son to his father
            if ((ptr_v->m_ptr_father != nullptr) && (ptr_v->m_ptr_father->m_ptr_left == ptr_v)) {
                ptr_v->m_ptr_father->m_ptr_left = ptr_v->m_ptr_left;
            }
            else if (ptr_v->m_ptr_father != nullptr) {
                ptr_v->m_ptr_father->m_ptr_right = ptr_v->m_ptr_left;
            }

            ptr_v->m_ptr_left->m_ptr_father = ptr_v->m_ptr_father;
            ptr_v->m_ptr_father = nullptr;
            delete ptr_v;
        }

            // if ptr_v has only right son
        else if (ptr_v->m_ptr_left == nullptr && ptr_v->m_ptr_right != nullptr) {
            if (temp == nullptr) {
                ptr_main_root = ptr_v->m_ptr_right;
            }

            // checks if ptr_v is a left son or a right son to his father
            if ((ptr_v->m_ptr_father != nullptr) && (ptr_v->m_ptr_father->m_ptr_left == ptr_v)) {
                ptr_v->m_ptr_father->m_ptr_left = ptr_v->m_ptr_right;
            }
            else if (ptr_v->m_ptr_father != nullptr) {
                ptr_v->m_ptr_father->m_ptr_right = ptr_v->m_ptr_right;
            }

            ptr_v->m_ptr_right->m_ptr_father = ptr_v->m_ptr_father;
            ptr_v->m_ptr_father = nullptr;
            delete ptr_v;
        }

            // if ptr_v has both sons
        else {
            Node* ptr_w = find_next_inorder(main_root, ptr_v);

            T temp_data = ptr_v->m_data;
            ptr_v->m_data = ptr_w->m_data;
            ptr_w->m_data = temp_data;

            temp = ptr_w->m_ptr_father;

            // if ptr_w is a leaf - delete it
            if (ptr_w->m_ptr_left == nullptr && ptr_w->m_ptr_right == nullptr) {
                // if ptr_w is a left son
                if (temp->m_ptr_left == ptr_w) {
                    temp->m_ptr_left = nullptr;
                }
                    // if ptr_w is a right son
                else {
                    temp->m_ptr_right = nullptr;
                }

                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }

                // if ptr_w has only left son
            else if (ptr_w->m_ptr_left != nullptr && ptr_w->m_ptr_right == nullptr) {

                // checks if ptr_w is a left son or a right son to his father
                if (ptr_w->m_ptr_father->m_ptr_left == ptr_w) {
                    ptr_w->m_ptr_father->m_ptr_left = ptr_w->m_ptr_left;
                }
                else {
                    ptr_w->m_ptr_father->m_ptr_right = ptr_w->m_ptr_left;
                }

                ptr_w->m_ptr_left->m_ptr_father = ptr_w->m_ptr_father;
                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }

                // if ptr_w has only right son
            else if (ptr_w->m_ptr_left == nullptr && ptr_w->m_ptr_right != nullptr) {

                // checks if ptr_w is a left son or a right son to his father
                if (ptr_w->m_ptr_father->m_ptr_left == ptr_w) {
                    ptr_w->m_ptr_father->m_ptr_left = ptr_w->m_ptr_right;
                }
                else {
                    ptr_w->m_ptr_father->m_ptr_right = ptr_w->m_ptr_right;
                }

                ptr_w->m_ptr_right->m_ptr_father = ptr_w->m_ptr_father;
                ptr_w->m_ptr_father = nullptr;
                delete ptr_w;
            }
        }

        if (temp == nullptr) {
            return;
        }

        Node* temp_backup = temp;
        update(temp);
        temp = balance(temp);
        Node* temps_father = nullptr;


        while (temp != nullptr) {
            update(temp);
            temps_father = temp->m_ptr_father;
            temp = balance(temp);
            temp->m_ptr_father = temps_father;
            if ((temps_father != nullptr) && (temps_father->m_data > temp->m_data)) {
                temps_father->m_ptr_left = temp;
                temps_father->m_ptr_right = temp->m_ptr_father->m_ptr_right;
            }
            else if ((temps_father != nullptr) && (temps_father->m_data < temp->m_data)){
                temps_father->m_ptr_right = temp;
                temps_father->m_ptr_left = temp->m_ptr_father->m_ptr_left;
            }
            temp = temp->m_ptr_father;
            if (temp != nullptr) {
                temp_backup = temp;
            }
        }
        update(temp_backup);
        temp_backup = balance(temp_backup);
        update(temp_backup);
        ptr_main_root = find_main_root(temp_backup);
    }
};

#endif //OLDTREE_H
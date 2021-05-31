#include "TreeTable.h"

/* red-black tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

string* TTreeTable::GetKeys()
{
    string* keys = new string[GetRecNumber()];
    int pos = 0;
    GetKeys(root, keys, pos);
    return keys;
}

int TTreeTable::GetRecNumber()
{
    return GetRecNumber(root);
}

void TTreeTable::GetKeys(Node_ *node, string *keys, int& pos)
{
    keys[pos++] = node->key;
    if(node->left != NIL)
        GetKeys(node->left, keys, pos);
    if(node->right != NIL)
        GetKeys(node->right, keys, pos);
}

int TTreeTable::GetRecNumber(Node_ *node)
{
    int result = 1;
    if (node->left != NIL)
        result += GetRecNumber(node->left);
    if (node->right != NIL)
        result += GetRecNumber(node->right);
    return result;
}

void TTreeTable::rotateLeft(Node* x) {

    /**************************
     *  rotate node x to left *
     **************************/

    Node* y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else {
        root = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL) x->parent = y;
}

void TTreeTable::printAll()
{
    cout << "Tree Nodes:" << endl;
    printNode(root);
}

void TTreeTable::printNode(Node* x)
{
    cout << x->key << ": " << *(x->data) << endl;
    if (x->left != NIL)
        printNode(x->left);
    if (x->right != NIL)
        printNode(x->right);
}

void TTreeTable::rotateRight(Node* x) {

    /****************************
     *  rotate node x to right  *
     ****************************/

    Node* y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else {
        root = y;
    }

    /* link x and y */
    y->right = x;
    if (x != NIL) x->parent = y;
}

void TTreeTable::insertFixup(Node* x) {

    /*************************************
     *  maintain Red-Black tree balance  *
     *  after inserting node x           *
     *************************************/

     /* check Red-Black properties */
    while (x != root && x->parent->color == RED) {
        /* we have a violation */
        if (x->parent == x->parent->parent->left) {
            Node* y = x->parent->parent->right;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {

                /* uncle is BLACK */
                if (x == x->parent->right) {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        }
        else {

            /* mirror image of above code */
            Node* y = x->parent->parent->left;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {

                /* uncle is BLACK */
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node* TTreeTable::insertNode(keyType key, T data) {
    Node* current, * parent, * x;

    /***********************************************
     *  allocate node for data and insert in tree  *
     ***********************************************/

     /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL) {
        if (compEQ(key.c_str(), current->key)) return (current);
        parent = current;
        current = compLT(key.c_str(), current->key) ?
            current->left : current->right;
    }

    /* setup new node */
    if ((x = (Node*)malloc(sizeof(*x))) == 0) {
        printf("insufficient memory (insertNode)\n");
        exit(1);
    }

    x->data = data;
    //x->key = new char[key.length() + 1];
    strcpy_s(x->key, key.c_str());

    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    /* insert node in tree */
    if (parent) {
        if (compLT(key.c_str(), (current->key)))
            parent->left = x;
        else
            parent->right = x;
    }
    else {
        root = x;
        CurrPos = root;
    }

    insertFixup(x);
    return(x);
}

int TTreeTable::Reset(void)
{
    CurrPos = root;
    ResetNodes(root);
    root->Visited = 1;
    return 0;
}

void TTreeTable::ResetNodes(Node* node)
{
    node->Visited = 0;
    if (node->left)
        ResetNodes(node->left);
    if (node->right)
        ResetNodes(node->right);
}

int TTreeTable::IsTabEnded(void) const
{
    return CurrPos == root && root->Visited == 2 ? 1 : 0;
}

int TTreeTable::GoNext(void)
{
    if (CurrPos->left)
    {
        CurrPos = CurrPos->left;
        CurrPos->Visited = 1;
    }
    else
    {
        if (CurrPos->right)
        {
            CurrPos = CurrPos->right;
            CurrPos->Visited = 1;
        }
        else
        {
            CurrPos = CurrPos->parent;
            CurrPos->Visited = 2;
        }
    }
    return 0;
}

string TTreeTable::GetKey(TDataPos mode)
{
    return CurrPos->key;
}
Polinom* TTreeTable::GetValuePtr(TDataPos mode)
{
    return CurrPos->data;
}

void TTreeTable::deleteFixup(Node* x) {

    /*************************************
     *  maintain Red-Black tree balance  *
     *  after deleting node x            *
     *************************************/

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void TTreeTable::deleteNode(Node* z) {
    Node* x, * y;

    /*****************************
     *  delete node z from tree  *
     *****************************/

    if (!z || z == NIL) return;


    if (z->left == NIL || z->right == NIL) {
        /* y has a NIL node as a child */
        y = z;
    }
    else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z)// z->data = y->data;
    {
        strcpy_s(z->key, y->key);
        z->data = y->data;
    }


    if (y->color == BLACK)
        deleteFixup(x);

    free(y);
}

Node* TTreeTable::findNode(keyType key) {

    /*******************************
     *  find node containing data  *
     *******************************/

    Node* current = root;
    Efficiency = 0;
    while (current != NIL)
        if (compEQ(key.c_str(), current->key))
        {
            Efficiency++;
            return (current);
        }
        else
        {
            current = compLT(key.c_str(), current->key) ?
                current->left : current->right;
            Efficiency++;
        }
    return(0);
}

ostream& operator<<(ostream& os, TTreeTable& tab)
{
    os << " Table Print" << endl;
    tab.printAll();
    return os;
}
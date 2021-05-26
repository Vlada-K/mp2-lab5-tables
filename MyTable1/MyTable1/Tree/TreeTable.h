#pragma once
#include"TTable.h"
#include"TTabRecord.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef string   keyType;            /* type of key */
typedef Polinom* T;                  /* type of item to be stored */

#define compLT(a,b) (strcmp(a,b) <  0)
#define compEQ(a,b) (strcmp(a,b) == 0)

/* Red-Black tree description */
typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    struct Node_* left;         /* left child */
    struct Node_* right;        /* right child */
    struct Node_* parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */
    //keyType key;
    char key[16];
    T data;                     /* data stored in node */
    int Visited;
} Node;

#define NIL &sentinel           /* all leafs are sentinels */

/* user data stored in tree */
typedef Polinom* recType;

#define TabMaxSize 25

class TTreeTable:public TTable
{
	protected:
        Node sentinel;// = { NIL, NIL, 0, BLACK, 0 };
        Node* root;               /* root of Red-Black tree */

        Node* CurrPos;//номер текущего записи(нумерация от 0)

	public:
        TTreeTable() 
                  {
                    root = NIL;
                    CurrPos = root;

                    sentinel.left = NIL; // Node{ NIL, NIL, 0, BLACK, "", 0 };
                    sentinel.right = NIL;
                    sentinel.parent = 0;
                    sentinel.color = BLACK;
                    sentinel.key[0] = 0; // "";
                    sentinel.data = 0;
                    sentinel.Visited = 0;
                  }

        Node* insertNode(keyType key, T data);
        void deleteNode(Node* z);
        Node* findNode(keyType key);

        void deleteFixup(Node* x);
        void insertFixup(Node* x);
        void rotateRight(Node* x);
        void rotateLeft(Node* x);

        void printAll();
        void printNode(Node* x);
       
        int IsFull() const// таблица заполнена?
        {
            return 0;
        }

        virtual Polinom* FindRecord(string K)
        {
            Node* node = findNode(K);
            if (node != 0)
                return node->data;
            else
                return nullptr;
        }
        virtual Polinom* InsRecord(string K, Polinom* pVal)//вставить запись
        {
            insertNode(K, pVal);
            return nullptr;
        }
        virtual Polinom* DelRecord(string K) // удалить запись
        {
            Node* node = findNode(K);
            if (node != 0)
                deleteNode(node);
            return nullptr;
        }
        
        virtual int Reset(void);//установить на первую  запись
        void ResetNodes(Node*);
        virtual  int IsTabEnded(void)  const ;//таблица завершена?
        virtual  int GoNext(void) ;//переход к следующей записи

        virtual string GetKey(TDataPos mode) ;
        virtual Polinom* GetValuePtr(TDataPos mode) ;
        
        string* GetKeys();
        void GetKeys(Node_* node, string* keys, int& pos);
        int GetRecNumber();
        int GetRecNumber(Node_*);
        int GetDataCount()
        {
            return GetRecNumber();
        }

        virtual int SetCurrentPos(int pos) { return 0; };
        int GetCurrentPos() const
        {
            return 0; // CurrPos;
        }
        friend ostream& operator<< (ostream& os, TTreeTable& tab);//печать таблицы
};


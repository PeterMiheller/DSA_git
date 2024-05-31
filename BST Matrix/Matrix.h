#pragma once
//2. ADT Matrix – repräsentiert als schwachbesetzte Matrix (sparse) mit Tupeln der Form
//(Zeile, Spalte, Wert) (Wert ≠ 0), wobei die Tupel in lexikographischen Reihenfolge nach
//(Zeile, Spalte) in einem BST mit einer verketteten Repräsentierung auf Arrays
//gespeichert werden.

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    //TODO - Representation
    struct Info {
        int line;
        int column;
        TElem value;
    };
    struct Node{
        Info info;
        int left;
        int right;
        int parent;
    };
    Node* BSTNodes;
    int root;
    int firstEmpty;
    int nrCol;
    int nrLine;
    int capacity;
    int nrElements;

    int findMinimum(int currentNode);
    int allocate();
    void free_pos(int position);
    void resize();
    int recursiveSearch(int position, TElem value) const;
public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    // destructor
    ~Matrix();

};

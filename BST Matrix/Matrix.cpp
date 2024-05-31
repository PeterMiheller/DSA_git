#include "Matrix.h"
#include <exception>
using namespace std;

///Theta(this->capacity)
Matrix::Matrix(int nrLines, int nrCols) {
    //TODO - Implementation
    this->capacity = 10;
    this->nrElements = 0;
    this->nrLine = nrLines;
    this->nrCol = nrCols;
    this->root = -1;
    this->firstEmpty = 0;
    this->BSTNodes = new Node[this->capacity];
    for(int i = 0; i < this->capacity - 1; i++)
    {
        this->BSTNodes[i].left = i + 1;
        this->BSTNodes[i].right = i + 1;
        this->BSTNodes[i].parent = i - 1;
        this->BSTNodes[i].info.value = NULL_TELEM;
    }
    this->BSTNodes[this->capacity - 1].right = -1;
    this->BSTNodes[this->capacity - 1].left = -1;
    this->BSTNodes[this->capacity - 1].parent = this->capacity - 2;
    this->BSTNodes[this->capacity - 1].info.value = NULL_TELEM;
}



///Theta(1)
int Matrix::nrLines() const {
    //TODO - Implementation
    return this->nrLine;
}


///Theta(1)

int Matrix::nrColumns() const {
    //TODO - Implementation
    return this->nrCol;
}

///Best case: Theta(1) -> if the element we search is exactly the root
///Worst case: Theta(this->nrElements) -> if the element we searched is not in the tree
///Average case: Theta(this->nrElements)
///General case: O(this->nrElements)
TElem Matrix::element(int i, int j) const {
    //TODO - Implementation
    if(i < 0 || i >= this->nrLine)
        throw exception();
    if(j < 0 || j >= this->nrCol)
        throw exception();

    int currentNode = this->root;

    while(currentNode != -1)
    {
        if(this->BSTNodes[currentNode].info.line == i and this->BSTNodes[currentNode].info.column == j) {
            return this->BSTNodes[currentNode].info.value;
        }
        if(this->BSTNodes[currentNode].info.line == i and this->BSTNodes[currentNode].info.column < j){
            currentNode = this->BSTNodes[currentNode].right;
        }
        else if(this->BSTNodes[currentNode].info.line < i){
            currentNode = this->BSTNodes[currentNode].right;
        }
        else if(this->BSTNodes[currentNode].info.line == i and this->BSTNodes[currentNode].info.column > j){
            currentNode = this->BSTNodes[currentNode].left;
        }
        else if(this->BSTNodes[currentNode].info.line > i){
            currentNode = this->BSTNodes[currentNode].left;
        }
    }

    return NULL_TELEM;
}


///Best case: Theta(1)
///Worst case: Theta(this->nrElements)
///Average case: Theta(this->nrElements)
///General case: O(this->nrElements)
TElem Matrix::modify(int i, int j, TElem e) {
    //TODO - Implementation
    ///Case 1: currentValue = 0 and newValue = 0 -> do nothing
    ///Case 2: currentValue = 0 and newValue != 0 -> insert in the data structure
    ///Case 3: currentValue != 0 and newValue = 0 -> remove from the data structure
    ///Case 4: currentValue !=0 and newValue != 0 -> just change the value in the data structure

    if (i < 0 || i >= this->nrLine)
        throw exception();
    if (j < 0 || j >= this->nrCol)
        throw exception();

    Node* newNode =new Node[this->capacity];
    newNode->info.line=i;
    newNode->info.column=j;
    newNode->info.value=e;
    if (e != 0) ///We have to modify the value or insert a new one
    {
        int currentNode = this->root;
        int previousNode = 0;
        while (currentNode != -1) {
            ///The first if refers to the following case:
            ///We have to modify the value of the cell
            if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column == j) {
                TElem oldValue = this->BSTNodes[currentNode].info.value;
                this->BSTNodes[currentNode].info = newNode->info;
                return oldValue;
            }
            if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column < j) {
                previousNode = currentNode;
                currentNode = this->BSTNodes[currentNode].right;
            } else if (this->BSTNodes[currentNode].info.line < i) {
                previousNode = currentNode;
                currentNode = this->BSTNodes[currentNode].right;
            } else if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column > j) {
                previousNode = currentNode;
                currentNode = this->BSTNodes[currentNode].left;
            } else if (this->BSTNodes[currentNode].info.line > i) {
                previousNode = currentNode;
                currentNode = this->BSTNodes[currentNode].left;
            }
        }

        ///Here we add a new element
        ///Case 1: The binary search tree is empty so the first added node will become the root
        if (this->root == -1) {
            int position = this->allocate();
            /*if (position == -1 && this->nrElements == this->capacity) {
                this->resize();
                position = this->allocate();
            }*/
            this->BSTNodes[position].info = newNode->info;
            this->root = position;
            this->nrElements++;
            return 0;
        }

        ///Case 2: In this case we found the node for which we add a new "child"
        int position = this->allocate();
        /*if (position == -1 && this->nrElements == this->capacity) {
            this->resize();
            position = this->allocate();
        }*/
        /// It means we have to add the new node as the right child
        if ((this->BSTNodes[previousNode].info.line == i && this->BSTNodes[previousNode].info.column < j) || this->BSTNodes[previousNode].info.line < i) {
            this->BSTNodes[previousNode].right = position;
            this->BSTNodes[position].info = newNode->info;
            this->BSTNodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }
            /// It means we have to add the new node as the left child
        else {
            this->BSTNodes[previousNode].left = position;
            this->BSTNodes[position].info = newNode->info;
            this->BSTNodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }

    } else///We have to remove the value or do nothing
    {
        int currentNodeToBeRemoved = 0;

        int currentNode = this->root;

        bool stop = false;

        while (currentNode != -1 && !stop) {
            if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column == j) {
                currentNodeToBeRemoved = currentNode;
                stop = true;
            } else if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column < j) {
                currentNode = this->BSTNodes[currentNode].right;
            } else if (this->BSTNodes[currentNode].info.line < i) {
                currentNode = this->BSTNodes[currentNode].right;
            } else if (this->BSTNodes[currentNode].info.line == i && this->BSTNodes[currentNode].info.column > j) {
                currentNode = this->BSTNodes[currentNode].left;
            } else if (this->BSTNodes[currentNode].info.line > i) {
                currentNode = this->BSTNodes[currentNode].left;
            }
        }

        ///It means the currentValue from that position is 0 and the new value we want to add is also 0, so we do nothing
        if (currentNode == -1)
            return 0;
        /// Calculating the numbr of descendants
        int numberOfDescendants = 0;

        if (this->BSTNodes[currentNodeToBeRemoved].left != -1)
            numberOfDescendants++;

        if (this->BSTNodes[currentNodeToBeRemoved].right != -1)
            numberOfDescendants++;

        ///In this case, the node we are about to delete doesn't have a descendent.
        if (numberOfDescendants == 0) {
            ///Case 1: we have only one node in the tree which is the root
            if (currentNodeToBeRemoved == this->root) {
                this->root = -1;
                TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                free_pos(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
                ///Case 2: the node we are about to delete is a leaf
            else {
                int parent = this->BSTNodes[currentNodeToBeRemoved].parent;
                ///We check if it was the left child of the parent
                if (this->BSTNodes[parent].left == currentNodeToBeRemoved) {
                    this->BSTNodes[parent].left = -1;
                }
                    ///We check if it was the right child of the parent
                else if (this->BSTNodes[parent].right == currentNodeToBeRemoved) {
                    this->BSTNodes[parent].right = -1;
                }
                TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                free_pos(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
        }
            ///In this case, the node we are about to delete has one descendent
        else if (numberOfDescendants == 1) {
            ///Case 1: the node is the root
            if (currentNodeToBeRemoved == this->root) {
                ///We check if the root had a left child
                if (this->BSTNodes[currentNodeToBeRemoved].left != -1) {
                    TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                    ///We set the new root as being the left child of the root we are about to delete
                    this->root = this->BSTNodes[currentNodeToBeRemoved].left;
                    ///We set the parent of the new root with -1
                    this->BSTNodes[this->root].parent = -1;
                    free_pos(currentNodeToBeRemoved);
                    this->nrElements--;
                    return oldValue;
                }
                    ///We check if the root had a right child
                else if (this->BSTNodes[currentNodeToBeRemoved].right != -1) {
                    TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                    ///We set the new root as being the right child of the root we are about to delete
                    this->root = this->BSTNodes[currentNodeToBeRemoved].right;
                    ///We set the parent of the new root with -1
                    this->BSTNodes[this->root].parent = -1;
                    free_pos(currentNodeToBeRemoved);

                    this->nrElements--;
                    return oldValue;
                }
            }
                ///Case 2: the node is inside the three
            else {
                ///We check if the node had a left child
                if (this->BSTNodes[currentNodeToBeRemoved].left != -1) {

                    ///We keep the parent of the node we want to delete
                    int parent = this->BSTNodes[currentNodeToBeRemoved].parent;

                    ///We check if the node we want to delete was a left child of its parent
                    if (this->BSTNodes[parent].left == currentNodeToBeRemoved) {

                        ///We set the parent for the left child of the node we want to delete with the parent of the node we want to delete
                        this->BSTNodes[this->BSTNodes[currentNodeToBeRemoved].left].parent = parent;

                        ///We set the left child of the parent of the node we want to delete with the left child of the node we want to delete
                        this->BSTNodes[parent].left = this->BSTNodes[currentNodeToBeRemoved].left;

                        TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                        free_pos(currentNodeToBeRemoved);

                        this->nrElements--;
                        return oldValue;
                    }
                        ///We check if the node we want to delete was a right child of its parent
                    else if (this->BSTNodes[parent].right == currentNodeToBeRemoved) {

                        ///We set the parent for the left child of the node we want to delete with the parent of the node we want to delete
                        this->BSTNodes[this->BSTNodes[currentNodeToBeRemoved].left].parent = parent;

                        ///We set the right child of the parent of the node we want to delete with the left child of the node we want to delete
                        this->BSTNodes[parent].right = this->BSTNodes[currentNodeToBeRemoved].left;

                        TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                        free_pos(currentNodeToBeRemoved);

                        this->nrElements--;
                        return oldValue;
                    }
                }
                    ///We check if the node had a right child
                else if (this->BSTNodes[currentNodeToBeRemoved].right != -1) {

                    ///We keep the parent of the node we want to delete
                    int parent = this->BSTNodes[currentNodeToBeRemoved].parent;

                    ///We check if the node we want to delete was a left child of its parent
                    if (this->BSTNodes[parent].left == currentNodeToBeRemoved) {

                        ///We set the parent for the right child of the node we want to delete with the parent of the node we want to delete
                        this->BSTNodes[this->BSTNodes[currentNodeToBeRemoved].right].parent = parent;

                        ///We set the left child of the parent of the node we want to delete with the right child of the node we want to delete
                        this->BSTNodes[parent].left = this->BSTNodes[currentNodeToBeRemoved].right;

                        TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                        free_pos(currentNodeToBeRemoved);

                        this->nrElements--;
                        return oldValue;
                    }
                        ///We check if the node we want to delete was a right child of its parent
                    else if (this->BSTNodes[parent].right == currentNodeToBeRemoved) {

                        ///We set the parent for the right child of the node we want to delete with the parent of the node we want to delete
                        this->BSTNodes[this->BSTNodes[currentNodeToBeRemoved].right].parent = parent;

                        ///We set the right child of the parent of the node we want to delete with the right child of the node we want to delete
                        this->BSTNodes[parent].right = this->BSTNodes[currentNodeToBeRemoved].right;

                        TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
                        free_pos(currentNodeToBeRemoved);

                        this->nrElements--;
                        return oldValue;
                    }

                }
            }

        }
        ///It means the node we want to remove has 2 descendents
        ///We take the right child of the node we want to delete, in order to start the search for the minimum from there
        int rightChild = this->BSTNodes[currentNodeToBeRemoved].right;
        int replacedNode = this->findMinimum(rightChild);

        ///In this part we only detach the minimum from the tree

        ///Case 1: The minimum is a leaf
        ///We check only the right part because, being the minimum, it will always have a child only in the right, if it also had a child in the left, then it wouldn't be the minimum
        if (this->BSTNodes[replacedNode].right == -1) {
            ///We keep the parent of the minimum
            int parent = this->BSTNodes[replacedNode].parent;

            ///We mark the parent of the minimum with -1 for now
            this->BSTNodes[replacedNode].parent = -1;

            ///We check if the minimum was a left child or a right child for its parent
            if (this->BSTNodes[parent].left == replacedNode) {
                this->BSTNodes[parent].left = -1;
            } else if (this->BSTNodes[parent].right == replacedNode) {
                this->BSTNodes[parent].right = -1;
            }

        }

            ///Case 2: The minimum has a right child
            ///We check only the right part because, being the minimum, it will always have a child only in the right, if it also had a child in the left, then it wouldn't be the minimum
        else if (this->BSTNodes[replacedNode].right != -1) {
            ///We keep the parent of the minimum
            int parent = this->BSTNodes[replacedNode].parent;

            ///We check if the minimum was a left child or a right child of its parent and we place there its own right child
            if (this->BSTNodes[parent].left == replacedNode) {
                this->BSTNodes[parent].left = this->BSTNodes[replacedNode].right;
            } else if (this->BSTNodes[parent].right == replacedNode) {
                this->BSTNodes[parent].right = this->BSTNodes[replacedNode].right;
            }
            ///We keep the child of the minimum
            int child = this->BSTNodes[replacedNode].right;

            ///We mark the parent of the child's minimum
            this->BSTNodes[child].parent = parent;

            ///We mark the parent of the minimum with -1 for now
            this->BSTNodes[replacedNode].parent = -1;

        }
        TElem oldValue = this->BSTNodes[currentNodeToBeRemoved].info.value;
        ///We change the value of the node we wanted to delete with the value of the minimum
        this->BSTNodes[currentNodeToBeRemoved].info = this->BSTNodes[replacedNode].info;
        ///We delete the minimum from the tree
        free_pos(replacedNode);
        this->nrElements--;
        return oldValue;

    }
}
///Theta(1)
Matrix::~Matrix() {
    //TODO - Implementation
    delete[] BSTNodes;
}


///General Case: O(n)
int Matrix::findMinimum(int currentNode) {
    if(currentNode==-1)
        throw exception();
    while(this->BSTNodes[currentNode].left != -1){
        currentNode = this->BSTNodes[currentNode].left;
    }
    return currentNode;
}

///Theta(n)
void Matrix::resize() {
    /// Allocate a new array with the new capacity
    this->capacity = 2*this->capacity;
    Node* new_Tree = new Node[this->capacity];
    /// Copy elements from the old array to the new array
    for(int i = 0; i < this->nrElements; i++)
    {
        new_Tree[i] = this->BSTNodes[i];
    }

    this->firstEmpty = this->nrElements;
    /// Reinitialize the elements added at the end of the new array
    for(int i = this->nrElements ; i < this->capacity - 1; i++){
        new_Tree[i].left= i + 1;
        new_Tree[i].right =i + 1;
        new_Tree[i].parent = i - 1;
        new_Tree[i].info.value = NULL_TELEM;
    }
    new_Tree[this->capacity - 1].right = -1;
    new_Tree[this->capacity - 1].left = -1;
    new_Tree[this->capacity - 1].parent = this->capacity - 2;
    new_Tree[this->capacity - 1].info.value = NULL_TELEM;

    delete[] this->BSTNodes;
    this->BSTNodes = new_Tree;
}

///Theta(1)
int Matrix::allocate() {
    if ( this->nrElements == this->capacity)
        resize();
    int newElement = this->firstEmpty;
    if(newElement != -1){
        this->firstEmpty = this->BSTNodes[this->firstEmpty].left;
        this->BSTNodes[newElement].left = -1;
        this->BSTNodes[newElement].right = -1;
        this->BSTNodes[newElement].parent = -1;
    }
    return newElement;
}
///Theta(1)
void Matrix::free_pos(int position) {
    this->BSTNodes[position].left = this->firstEmpty;
    this->BSTNodes[position].info.value = NULL_TELEM;
    this->BSTNodes[position].right = -1;
    this->BSTNodes[position].parent = -1;
    this->firstEmpty = position;
}

///Best case: Theta(1) -> if the element we searched is exactly the root
///Worst case: Theta(this->nrOfElements) ->if the element we searched for is not in the tree
///Average case: Theta(this->nrElements)
///General case: O(this->nrElements)
int Matrix::recursiveSearch(int position, TElem value) const{
    if(position == -1)
        return -1;
    if(this->BSTNodes[position].info.value == value)
        return position;
    else if(this->BSTNodes[position].info.value < value)
        return recursiveSearch(this->BSTNodes[position].right, value);
    else
        return recursiveSearch(this->BSTNodes[position].left, value);
}


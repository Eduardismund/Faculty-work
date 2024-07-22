#include "Matrix.h"
//#include "MatrixIterator.h"
#include <exception>
using namespace std;


// Theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
    this->nr_lines = nrLines;
    this->nr_columns = nrCols;
    this->root = NULL;
    this->nr_elems = 0;
}


// Theta(1)
int Matrix::nrLines() const {
    return this->nr_lines;
}


// Theta(1)
int Matrix::nrColumns() const {
    return this->nr_columns;
}


// Best Case: Theta(1) - The element we're searching is at the root
// Worst Case: Theta(h), where h is the height of the Binary Search Tree - The element is a leaf or is not in the Binary Search Tree
// Total Complexity: O(h), which is O(n)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->nr_lines) {
        throw exception();
    }
    if (j < 0 || j >= this->nr_columns) {
        throw exception();
    }
    TElem found = NULL_TELEM;
    MatrixNode* current_node = this->root;
    while (current_node != NULL) {
        if (current_node->row == i && current_node->column == j) {
            break;
        }
        if (i < current_node->row || (i == current_node->row && j < current_node->column)) {
            current_node = current_node->left;
        }
        else {
            current_node = current_node->right;
        }
    }
    if (current_node != NULL && current_node->row == i && current_node->column == j) {
        found = current_node->value;
    }
    return found;
}

// Best Case: Theta(1) - The node to be removed has no descendants
//					   - The node to be removed has one descendant
// Worst Case: Theta(h) - The node to be removed has two descendants and the we have to traverse the whole height of the tree to find it
// Total Complexity: O(h), which is O(n)
void Matrix::remove_node(MatrixNode* node) {
    if (node == NULL) {
        throw exception();
    }
    if (node->left == NULL && node->right == NULL) {
        // has no descendant
        if (node->parent == NULL) {
            // there is only one node in the Binary Search Tree = the root
            this->root = NULL;
        }
        else {
            //we set to NULL the link from the parent to the children, be it left or right
            if (node->row < node->parent->row || (node->row == node->parent->row && node->column < node->parent->column)) {
                //  the node to delete is a left child
                node->parent->left = NULL;
            }
            else {
                // If the node to delete is a right child
                node->parent->right = NULL;
            }
        }
        delete node;
    }
    else if (node->left != NULL && node->right == NULL) {
        // descent on the left
        if (node->parent == NULL) {
            this->root = node->left;
            node->left = NULL;
        }
        else {
            if (node->row < node->parent->row || (node->row == node->parent->row && node->column < node->parent->column)) {
                // if the node to delete is a left child
                node->parent->left = node->left;
            }
            else {
                // if the node to delete is a right child
                node->parent->right = node->left;
            }
            node->left->parent = node->parent;
        }
        delete node;
    }
    else if (node->left == NULL && node->right != NULL) {
        // If it has one descendant (on the right)
        if (node->parent == NULL) {
            this->root = node->right;
            node->right = NULL;
        }
        else {
            if (node->row < node->parent->row && (node->row == node->parent->row && node->column < node->parent->column)) {
                //  the node to delete is a left child
                node->parent->left = node->right;
            }
            else {
                //  the node to delete is a right child
                node->parent->right = node->right;
            }
            node->right->parent = node->parent;
        }
        delete node;
    }
    else {
        // has 2 descendants
        // we need to find the successor
        MatrixNode* successor_node = node->right;
        while (successor_node->left != NULL) {
            successor_node = successor_node->left;
        }
        // change the information of the node to be deleted, effectivelt deleting it
        node->value = successor_node->value;
        node->row = successor_node->row;
        node->column = successor_node->column;

        if (successor_node->row < successor_node->parent->row || (successor_node->row == successor_node->parent->row && successor_node->column < successor_node->parent->column)) {
            // If the successor node is a left child (i.e., the above while loop ran at least once), then we set
            // a new LEFT child for the successor node
            successor_node->parent->left = successor_node->right;
        }
        else {
            // If the successor node is a right child (i.e., the above while loop didn't run at all, the successor is just the right child
            // of the given node), then we set a new RIGHT child for the successor node
            successor_node->parent->right = successor_node->right;
        }

        successor_node->right = successor_node->left = NULL;
        delete successor_node;
    }
}

// Best Case: Theta(1) - when we change the value of the root
// Worst Case: Theta(h) - when we insert a new entry and have to traverse the whole height of the tree to find the position
//						- when we remove an entry and have to traverse the whole height of the tree to find the successor
// Total Complexity: O(h)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->nr_lines) {
        throw exception();
    }
    if (j < 0 || j >= this->nr_columns) {
        throw exception();
    }

    MatrixNode *current_node = this->root;
    MatrixNode *parent_node = NULL;
    TElem old_value = NULL_TELEM;
    while (current_node != NULL) {
        if (current_node->row == i && current_node->column == j) {
            break;
        }
        parent_node = current_node;
        if (i < current_node->row || (i == current_node->row && j < current_node->column)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    if (current_node != NULL && current_node->row == i && current_node->column == j) {
        // the matrix entry (i, j) is already in the matrix
        // we either modify an existing one or delete an existing one (depending on the value of TElem <e>)
        old_value = current_node->value;
        if (e == NULL_TELEM) {
            // in the case that e = NULL_TELEM we have to remove this matrix entry
            // 3 cases: the node we remove has no descendant, has one descendant, or has 2 descendants
            this->remove_node(current_node);
            this->nr_elems -= 1;
        } else {
            // In the case that e is not NULL_TELEM we simply modify the value of the current node
            current_node->value = e;
        }
    } else {
        // the given position (i, j) is not used in the matrix, the node is not in the Binary Search Tree
        // We either do nothing (if TElem e = NULL_TELEM), or create a new node and insert it in the Binary Search Tree
        if (e == NULL_TELEM) {
            // do nothing
        } else {
            // create a new node with the given information and insert it in the Binary Search Tree
            MatrixNode *new_node = new MatrixNode();
            new_node->row = i;
            new_node->column = j;
            new_node->value = e;
            new_node->left = new_node->right = new_node->parent = NULL;
            if (parent_node == NULL) {
                root = new_node;
            } else {
                new_node->parent = parent_node;
                if (i < parent_node->row || (i == parent_node->row && j < parent_node->column)) {
                    // means that we inserted the node to the left of a node
                    parent_node->left = new_node;
                } else {
                    // means that we inserted the node to the right of a node
                    parent_node->right = new_node;
                }
            }
            this->nr_elems += 1;
        }
    }
    return old_value;


}

/// worst case=best case= theta(nr_lines*h)
void Matrix::setMainDiagonal(TElem elem) {
    if (this->nr_lines != this->nr_columns) {
        throw exception();
    }

    for (int i = 0; i < this->nr_lines; ++i) {
        MatrixNode* current_node = this->root;
        MatrixNode* parent_node = NULL;
        while (current_node != NULL) {
            if (current_node->row == i && current_node->column == i) {
                //main diagonal
                current_node->value = elem;
                break;
            }
            parent_node = current_node;
            if (i < current_node->row || (i == current_node->row && i < current_node->column)) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }
        }

        if (current_node == NULL) {
            // if element doesn't exist, create and insert it
            MatrixNode* new_node = new MatrixNode();
            new_node->row = i;
            new_node->column = i;
            new_node->value = elem;
            new_node->left = new_node->right = NULL;
            new_node->parent = parent_node;
            if (parent_node == NULL) {
                this->root = new_node;
            } else if (i < parent_node->row || (i == parent_node->row && i < parent_node->column)) {
                parent_node->left = new_node;
            } else {
                parent_node->right = new_node;
            }
            ++this->nr_elems;
        }
    }
}

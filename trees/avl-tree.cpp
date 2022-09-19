#include "avl-tree.h"
#include "binary-search-tree.h"
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// check height of the node
int AVLTree::depthBelow(Node *n )
{
    return 1 + BinarySearchTree::depth();
}

Node* AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild = false )
{
    Node* newPar = parentNode->right;
    Node* carry = newPar->left;

    newPar->left = parentNode;
    parentNode->right = carry;
    return newPar;
}

Node* AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild = false )
{
    Node* newPar = parentNode->left;
    Node* carry = newPar->right;

    newPar->right = parentNode;
    parentNode->left = carry;
    return newPar;
}

Node* AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild = false )
{
    Node* newPar = parentNode->left;
    parentNode->left = singleLeftRotation( newPar );
    return singleRightRotation( parentNode );
}

Node* AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild = false )
{
    Node* newPar = parentNode->right;
    parentNode->right = singleRightRotation( newPar );
    return singleLeftRotation( parentNode );
}

// stack of path to inserted/deleted Node
std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    //auto represents std::stack<BinarySearchTree::Node*>
    auto* S = new std::stack<BinarySearchTree::Node*>; // stack of BST node pointers
    BinarySearchTree::Node* cur = BinarySearchTree::getRootNode();

    while( cur ) {
        S->push( cur );
        cur = ( val > cur->val ) ? cur->right : cur->left;
    }
    //below should always be true??
    if( S->top() && S->top()->val == val ) S->pop(); // pops last element if last element is not the parent
    return S; // lol please work???
}

int height( BinarySearchTree::Node* top, bool negative = false ) // don't send a null pointer cuz it wont know what to do with it
{
    bool neg = negative;
    if( !top->left && !top->right ) return 0;
    if( !top->left ) return 1 + abs( height( top->right, true ) );
    if( !top->right ) return 1 + height( top->left, neg );
    int leftHeight = 1 + height( top->left, neg );
    int rightHeight = 1 + height( top->right, neg );
    return ( leftHeight >= abs( rightHeight ) ) ? leftHeight : rightHeight;
}

int difference( BinarySearchTree::Node* top ) // don't send this a NULL pointer
{
    if( !top->left && !top->right ) return 0;
    if( !top->left ) return - 1 - height( top->right );
    if( !top->right ) return 1 + height( top->left );
    return height(top->left) - height( top->right );
}

// generic function to updated tree balance qof insertion/deletion
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    while( pathToNode->size() >= 2 ) {
        // setting parent node
        pathToNode->pop();
        Node *parent = pathToNode->top();
        pathToNode->pop();

        int balanceFactor = difference(parent); // find balanceFactor of parent
        if( abs(balanceFactor) < 2 ) continue;
        if (pathToNode->empty()) { // if we are balancing root case
            Node **root = getRootNodeAddress();
            Node *temp = NULL;
            if (balanceFactor < 0) { // can be replaced with BF < 1 check
                temp = parent->right;
                if (temp->right) *root = singleLeftRotation(parent);
                else *root = rightLeftRotation(parent);
            } else {
                temp = parent->left; // this is case where parent->left exits or BF > 1
                if (temp->left) *root = singleRightRotation(parent);
                else *root = leftRightRotation(parent);
            }
            //*root = temp; // lol this doesnt work
            return true;
        }

        // general case for not resetting root
        Node *grandpa = pathToNode->top(); // points to two places away from parent
        Node *temp = NULL;

        //setting temp depending on the balanceFactor
        if (balanceFactor < -1) {
            temp = parent->right;
            if (temp->right) {
                //if( temp->right->right) grandpa->right = singleLeftRotation( parent );
                //else grandpa->right = rightLeftRotation( parent );
                if (val < grandpa->val) {
                    if (parent->right) grandpa->left = singleLeftRotation(parent);
                    else grandpa->left = rightLeftRotation(parent);
                } else {
                    if (parent->right) grandpa->right = singleLeftRotation(parent);
                    else grandpa->right = leftRightRotation(parent);

                }
            } else {
                if (val < grandpa->val) {
                    if (parent->right) grandpa->left = rightLeftRotation(parent);
                    else grandpa->left = singleRightRotation(parent);
                } else {
                    if (parent->right) grandpa->right = rightLeftRotation(parent);
                    else grandpa->right = singleRightRotation(parent);
                }
            }
        } else {
            temp = parent->left;
            if (temp->left) {
                //if( temp->right->right) grandpa->left = singleLeftRotation( parent );
                //else grandpa->left = rightLeftRotation( parent );
                if (val < grandpa->val) grandpa->left = singleRightRotation(parent);
                else grandpa->right = singleRightRotation(parent);
            }
                //else if( temp->left->left ) grandpa->left = singleRightRotation( parent );
            else if (val < grandpa->val) grandpa->left = leftRightRotation(parent);
            else grandpa->right = leftRightRotation(parent);
        }
        //pathToNode->pop(); // probably not necessary cuz we already popped the top node when setting grandpa
    }

    return true;
}

bool AVLTree::insert(DataType val)
{
    bool returnVal = BinarySearchTree::insert( val );
    if( returnVal ) updateNodeBalance( pathToNodeStack( val ), val );
    return returnVal;
}

bool AVLTree::remove(DataType val)
{

    Node* cur = getRootNode();
    Node* pred = NULL;

    if( !cur ) return false;



    while( cur != NULL ) {
        if( val == cur->val ) break;
        pred = cur;
        if( val > cur->val ) cur = cur->right;
        else if( val < cur->val ) cur = cur->left;
    }

    bool returnVal = BinarySearchTree::remove( val );


    if( returnVal && pred ) updateNodeBalance( pathToNodeStack( pred->val ), pred->val );
    return returnVal;
}

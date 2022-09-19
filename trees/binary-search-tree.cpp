#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;   // Value of the node.
    left = NULL;    // Pointer to the left node.
    right = NULL;   // Pointer to the right node.
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if( !n->left && !n->right ) return 0;

    if( !n->left ) return 1 + getNodeDepth( n->right );
    if( !n->right ) return 1 + getNodeDepth( n->left );

    int leftDepth = 1 + getNodeDepth( n->left );
    int rightDepth = 1 + getNodeDepth( n->right );

    return (leftDepth > rightDepth) ? leftDepth : rightDepth;
}

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{

}

void TreeDeleteFunTimeHeheXD( Node* cur )
{
    if( cur == NULL ) return;
    Node* leftBranch = cur->left;
    Node* rightBranch = cur->right;
    if( leftBranch->left == NULL ) {
        delete leftBranch->left;
        leftBranch->left = NULL;
    }
    if( leftBranch->right == NULL ) {
        delete leftBranch->right;
        leftBranch->left = NULL;
        if( leftBranch->left == NULL ) {
            delete cur->left;
            cur->left = NULL;
        }
    }

    if( leftBranch->left == NULL ) {
        delete leftBranch->left;
        leftBranch->left = NULL;
    }
    if( rightBranch->right == NULL ) {
        delete rightBranch->right;
        rightBranch->left = NULL;
        if( rightBranch->left == NULL ) {
            delete cur->left;
            cur->left = NULL;
        }
    }

    TreeDeleteFunTimeHeheXD( leftBranch );
    TreeDeleteFunTimeHeheXD( rightBranch );
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* cur = root_;
    while( cur->right != NULL ) cur = cur->right;

    std::cout << cur->val << std::endl;
    return cur->val;
}

DataType BinarySearchTree::min() const
{
    Node* cur = root_;
    while( cur->left != NULL ) cur = cur->left;
    std::cout << cur->val << std::endl;
    return cur->val;
}

unsigned int BinarySearchTree::depth() const
{
    // ohh use the other one to implement this
    return getNodeDepth( root_ );
}

void BinarySearchTree::print() const
{
    queue<Node*> q;
    if( root_ != NULL ) q.push( root_ );
    while( !q.empty() ) {
        Node* cur = q.front();
        cout << cur->val << " ";
        q.pop();
        if (cur->left != NULL )
            q.push(cur->left);
        if (cur->right != NULL )
            q.push(cur->right);
    }
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* cur = root_;
    if( cur->val == val ) return true;
    while( cur->left != NULL || cur->right != NULL ) {
        if( val == cur->val ) return true;
        if( val < cur-> val ) {
            if (cur->left == NULL) return false;
            cur = cur->left;
        }
        if( val > cur->val ) {
            if (cur->right == NULL) return false;
            cur = cur->right;
        }
    }
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {

    Node* newNode = new Node( val );
    Node *cur = root_;
    Node *prev = NULL;

    //if empty
    if( cur == NULL ) {
        root_ = newNode;
        size_ ++;
        return true;
    }
    // test if there is only a root node;
    if (root_->right == NULL && root_->left == NULL) {
        if (val < root_->val) {
            root_->left = newNode;
        } else if ( val > root_->val ) {
            root_->right = newNode;
        } else return false;
        size_++;
        return true;
    }
    // iterate thru list
    while (cur != NULL) {
        if (val == cur->val) return false;
        prev = cur;
        if (val < cur->val) cur = cur->left;
        else if (val > cur->val) cur = cur->right;
    }
    //general case
    if (val < prev->val) { // if the value to insert is in the left
        prev->left = newNode;
        size_++;
        return true;
    }
    prev->right = newNode; // if value to insert is in the right
    size_++;
    return true;
}

//ok if this returns pointer, we know this is the smallest -- always check if it returns ptr if we are not testing based case
Node* findPredecessor(Node* ptr, bool firstCheck = true)
{
    if( !ptr ) { // just in case cuz its not working
        std::cout << "ASFJL KJKSLF JLSLKDJF L" << std::endl;
        return NULL;
    }
    //if first time, we want to access the left subtree
    if( firstCheck ) {
        if( !ptr->left ) {
            std::cout << " RETURNING POINTER " << std::endl;
            return ptr; // check if there are any predecessors,
        }
        return findPredecessor( ptr->left, false );
    }

    if( ptr->right ) return findPredecessor( ptr->right, false);
    return ptr; // base case!!!
}


bool BinarySearchTree::remove(DataType val) {
    if (!root_) return false;
    Node *cur = root_;
    if (root_->val == val) { // removing root. in this case we should only return true because we have found the node to remove
        if (!root_->left && !root_->right) { // root is the only node in tree
            delete root_;
            root_ = NULL;
            size_--;
            return true;
        }
        if (!root_->left) { // root has no left subtree
            delete root_;
            root_ = root_->right;
            size_--;
            return true;
        }
        if (!root_->right) {
            delete root_;
            root_ = root_->left;
            size_--;
            return true;
        }
        Node *pred = findPredecessor(cur);
        while( cur != NULL ) {
            if ( pred == cur ) {
                Node *old_pred_left = NULL;
                if (pred->left) old_pred_left = pred->left;
                pred->right = root_->right;
                if (pred != root_->left) {
                    pred->left = root_->left;
                    if (root_->left) {
                        cur = root_->left;
                        while (cur->right != pred) cur = cur->right;
                        // cur->right should point to the predecessor
                        if (old_pred_left) {
                            cur->right = old_pred_left;
                        } else cur->right = NULL;
                    }
                } //else pred->left MUST BE EQUAL TO NULL;
                delete root_;
                root_ = pred;
                size_--;
                return true;
            }
            if (val > cur->val) cur = cur->right;
            else cur = cur->left;
        }
    }


    // we will go to the next element because we already checked if the root holds the val we r looking for
    Node *prev = cur;
    if (val > cur->val) cur = cur->right;
    else cur = cur->left;
    //general case where root is not the value we are looking for...
    while (cur != NULL) { // transversing list to find the value we are looking for
        if (val == cur->val) { // we've hit the root.
            if( !cur->left && !cur->right ) {
                if( val > prev->val ) prev->right = NULL;
                else prev->left = NULL;
                delete cur;
                size_ --;
                return true;
            }
            if( !cur->left ) {
                if( val > prev->val ) prev->right = cur->right;
                else prev->left = cur->right;
                delete cur;
                size_ --;
                return true;
            }
            if( !cur->right ) {
                if( val > prev->val ) prev->right = cur->left;
                else prev->left = cur->left;
                delete cur;
                size_ --;
                return true;
            }
            Node *pred = findPredecessor(cur);
            Node* old_pred_left = pred->left; // Might be NULL
            pred->right = cur->right;
            if( pred->val > prev -> val ) prev->right = pred; // if( prev->left != pred )
            else prev->left = pred;
            if( old_pred_left ) {
                cur = cur->left;
                while( cur->right != old_pred_left ) cur = cur->right;
                cur->right = old_pred_left;
            }

            delete cur;
            size_--;
            return true;
        }

        prev = cur;
        if ( val > cur->val ) cur = cur->right;
        else cur = cur->left;
    }
    return false;
}


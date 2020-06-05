#ifndef BINARYTREE_H
#define BINARYTREE_H

// using template to put factory into the binary tree
template <class T>
class BinaryTree
{

    struct node
    {
        T* value;
        struct node *right;
        struct node *left;
    };

public:
    BinaryTree();
    ~BinaryTree();
    // insert tiles
    void add(T* val);

    // search tiles
    bool lookup(T* val);

    // get specific tiles
    T* get(T* val);

    // find the smallest tile
    struct node* findMin();

    // delete the specific tile
    struct node* remove(T *val);

    // print 
    void printInOrder();

    // get tree size
    int size();
    

private:
    // starting point
    struct node *root;
    
    // tree size
    int treeSize;

    // helper function for above
    T* get(struct node *node, T* val);
    void add(struct node **node, T* val);
    bool lookup(struct node *node, T* val);
    struct node* remove(struct node *node, T *val);
    void printInOrder(struct node *node);
    void deleteTree(struct node *node);
    struct node* findMin(struct node *node);
};

template <class T>
BinaryTree<T>::BinaryTree()
{
    this->root = NULL;
    this->treeSize = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    deleteTree(this->root);
}

template <class T>
int BinaryTree<T>::size()
{
    return this->treeSize;
}

template <class T>
void BinaryTree<T>::add(T* val)
{
    add(&(this->root), val);
}

template <class T>
void BinaryTree<T>::add(struct node **node, T* val)
{

    // if there isn't any nodes, create one
    if (*node == NULL)
    {
        struct node *tmp = new struct node;
        tmp->value = val;
        tmp->left = NULL;
        tmp->right = NULL;
        *node = tmp;    
        
        // make tree size bigger
        this->treeSize++;
    }
    else
    {   
        // if the current colour is bigger than the node colour, find node's right part
        if (val->getColour() > (*node)->value->getColour())
        {
            add(&(*node)->right, val);
        }
        else
        {
            add(&(*node)->left, val);
        }
    }
}

template <class T>
void BinaryTree<T>::printInOrder()
{
    printInOrder(this->root);
    // std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder(struct node *node)
{
    if (node != NULL)
    {
        printInOrder(node->left);
        char colour = node->value->getColourAsChar();
        if (colour == 'R')
            std::cout << "\033[1;31m" << colour << "\033[0m" << ' ';
        if (colour == 'Y')
            std::cout << "\033[1;33m" << colour << "\033[0m" << ' ';
        if (colour == 'U')
            std::cout << "\033[1;30m" << colour << "\033[0m" << ' ';
        if (colour == 'B')
            std::cout << "\033[1;34m" << colour << "\033[0m" << ' ';
        if (colour == 'L')
            std::cout << "\033[1;96m" << colour << "\033[0m" << ' ';
        printInOrder(node->right);
    }
}

// deconstructor helper
template <class T>
void BinaryTree<T>::deleteTree(struct node *node)
{
    if (node != NULL)
    {
        // delete them in order
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <class T>
T* BinaryTree<T>::get(T* val){
    return get(this->root, val);
}

template <class T>
T* BinaryTree<T>::get(struct node *node, T* val)
{
    if (node == NULL)
    {
        return NULL;
    }
    else
    {
        if (val->getColour() == node->value->getColour())
        {
            return node->value;
        }
        if (val->getColour() > node->value->getColour())
        {
            return get(node->right, val);
        }
        else
        {
            return get(node->left, val);
        }
    }
    return NULL;
}

template <class T>
bool BinaryTree<T>::lookup(T* val)
{
    return lookup(this->root, val);
}

template <class T>
bool BinaryTree<T>::lookup(struct node *node, T* val)
{

    if (node != NULL)
    {
        // got the colour
        if (val->getColour() == node->value->getColour()){
            return true;
        }
        // current colour is greater, find right part
        if (val->getColour() > node->value->getColour()){
            return lookup(node->right, val);

        // otherwise look left part
        }else{
            return lookup(node->left, val);
        }
    }

    return false;
}

template <class T>
typename BinaryTree<T>::node *BinaryTree<T>::findMin()
{
    return findMin(this->root);
}

template <class T>
typename BinaryTree<T>::node *BinaryTree<T>::findMin(struct node *node)
{
    // search the smallest colour
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

template <class T>
typename BinaryTree<T>::node *BinaryTree<T>::remove(T *val)
{
    this->root = remove(this->root, val);
    return root;
}

template <class T>
typename BinaryTree<T>::node *BinaryTree<T>::remove(struct node *node, T *val)
{
    // if the node is empty, just return null
    if (node == NULL)
        return node;

    // otherwise several cases by recursion
    // 1. too small, remove left
    if (val->getColour() < node->value->getColour())
        node->left = remove(node->left, val);

    // 2. too big, remove right part
    else if (val->getColour() > node->value->getColour())
        node->right = remove(node->right, val);
    else
    {
        if (node->left == NULL)
        {
            struct node *temp = node->right;
            this->treeSize--;
            delete node;
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = node->left;
            this->treeSize--;
            delete node;
            return temp;
        }
        struct node *temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(node->right, temp->value);
        }
        return node;

}

#endif
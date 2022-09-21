#ifndef BITREE_H
#define BITREE_H
#include <iostream>
#include <cmath>
#include <list>
#include <fstream>

template<typename K, typename V>
class BiTree
{
public:
    BiTree();
    BiTree(const BiTree&);
    ~BiTree();

    void paste(const K&, const V&);
    void remove(const K&);
    void clearAll();
    bool contains(const K&) const;
    int size() const {return size_tree;}

    void read(const std::string &name);
    void write(const std::string &name) const;

    V &operator[](const K&);
    bool operator==(const BiTree&) const;

    std::list<V> values() const;
    std::list<K> keys() const;

private:
    class Node
    {
    public:
        K key;
        V value;
        Node *left, *right;

        Node();
        Node(const K& k, const V& v);
    };

    Node *root;
    int size_tree;

    Node *find(const K&) const;
    V value_in_key(const K&) const;

    void clearAllRecur(Node*);
    void copyRecur(Node*);
    bool compareRecur(Node*, bool) const;
    void valuesRecur(Node*, std::list<V>&) const;
    void keysRecur(Node*, std::list<K>&) const;
    void writeRecur(Node*, std::ofstream &f) const;

};

template<typename K, typename V>
BiTree<K, V>::Node::Node()
{
    key = K();
    value = V();
    left = right = nullptr;
}

template<typename K, typename V>
BiTree<K, V>::Node::Node(const K& k, const V& v)
{
    key = k;
    value = v;
    left = right = nullptr;
}

template<typename K, typename V>
BiTree<K, V>::BiTree()
{
    root = nullptr;
    size_tree = 0;
}

template<typename K, typename V>
BiTree<K, V>::BiTree(const BiTree &tree)
{
    root = nullptr;
    size_tree =0;
    copyRecur(tree.root);
}

template<typename K, typename V>
BiTree<K, V>::~BiTree()
{
    this->clearAll();
}

template<typename K, typename V>
void BiTree<K, V>::paste(const K &k, const V &v)
{
    if(!root)
    {
        root = new Node(k, v);
        size_tree++;
        return;
    }

    Node *curNode = root;

    while(curNode)
    {
        if(curNode->key == k)
        {
            curNode->value = v;
            return;
        }
        if(k < curNode->key)
        {
            if(curNode->left)
                curNode = curNode->left;
            else
            {
                curNode->left = new Node(k, v);
                size_tree++;
                return;
            }
        }
        else
        {
            if(curNode->right)
                curNode = curNode->right;
            else
            {
                curNode->right = new Node(k, v);
                size_tree++;
                return;
            }
        }
    }
}

template<typename K, typename V>
void BiTree<K, V>::remove(const K &k)
{
    if(!this->contains(k))
        return;

    if(k == root->key)
    {
        if(!root->left && !root->right)
        {
            delete(root);
            root = nullptr;
        }
        else if(root->left)
        {
            Node *last = root->left;
            while(last->right)
                last = last->right;
            last->right = root->right;
            Node *temp = root;
            root = root->left;
            delete(temp);
        }
        else
        {
            Node *last = root->right;
            while(last->left)
                last = last->left;
            last->left = root->left;
            Node *temp = root;
            root = root->right;
            delete(temp);
        }
    }
    else
    {
        Node *curNode = root, *target = nullptr;
        while(!target)
        {
            if(k < curNode->key)
            {
                if(curNode->left->key == k)
                    target = curNode->left;
                else
                    curNode = curNode->left;
            }
            else
            {
                if(curNode->right->key == k)
                    target = curNode->right;
                else
                    curNode = curNode->right;
            }
        }

        if(!target->left && !target->right)
        {
            if(curNode->left == target)
                curNode->left = nullptr;
            else
                curNode->right = nullptr;
            delete(target);
        }
        else if(target->left)
        {
            Node *last = target->left;
            while(last->right)
                last = last->right;
            last->right = target->right;

            if(curNode->left == target)
                curNode->left = target->left;
            else
                curNode->right = target->left;
            delete (target);
        }
        else
        {
            Node *last = target->right;
            while(last->left)
                last = last->left;
            last->left = target->left;

            if(curNode->right == target)
                curNode->right = target->right;
            else
                curNode->left = target->right;
            delete (target);
        }
    }

    size_tree--;
}

template<typename K, typename V>
void BiTree<K, V>::clearAll()
{
    clearAllRecur(root);
    root = nullptr;
    size_tree = 0;
}

template<typename K, typename V>
bool BiTree<K, V>::contains(const K &k) const
{
    Node *curNode = root;
    while(curNode)
    {
        if(k == curNode->key)
            return 1;
        if(k < curNode->key)
        {
            curNode = curNode->left;
        }
        else
            curNode = curNode->right;
    }
    return 0;
}

template<typename K, typename V>
void BiTree<K, V>::read(const std::string &name)
{
    this->clearAll();
    std::ifstream f(name);
    K k;
    V v;
    while(f >> k >> v)
    {
        this->paste(k, v);
    }
    f.close();
}

template<typename K, typename V>
void BiTree<K, V>::write(const std::string &name) const
{
    std::ofstream f(name);
    writeRecur(root, f);
    f.close();
}

template<typename K, typename V>
V &BiTree<K, V>::operator[](const K &k)
{
    if(!this->contains(k))
        this->paste(k, V());
    return this->find(k)->value;
}

template<typename K, typename V>
bool BiTree<K, V>::operator==(const BiTree &tree) const
{
    if(this->size_tree != tree.size())
        return 0;
    return compareRecur(tree.root, 1);
}

template<typename K, typename V>
std::list<V> BiTree<K, V>::values() const
{
    std::list<V> ans;
    valuesRecur(root, ans);
    return ans;
}

template<typename K, typename V>
std::list<K> BiTree<K, V>::keys() const
{
    std::list<K> ans;
    keysRecur(root, ans);
    return ans;
}

template<typename K, typename V>
void BiTree<K, V>::clearAllRecur(Node *curNode)
{
    if(!curNode)
        return;
    clearAllRecur(curNode->left);
    clearAllRecur(curNode->right);
    delete(curNode);
}

template<typename K, typename V>
void BiTree<K, V>::copyRecur(Node *curNode)
{
    if(!curNode)
        return;

    this->paste(curNode->key, curNode->value);
    copyRecur(curNode->left);
    copyRecur(curNode->right);
}

template<typename K, typename V>
bool BiTree<K, V>::compareRecur(Node *curNode, bool ok) const
{
    if(!curNode)
        return ok;
    if(!ok)
        return 0;
    ok = (this->contains(curNode->key) && curNode->value == this->value_in_key(curNode->key));
    return (compareRecur(curNode->left, ok) & compareRecur(curNode->right, ok));
}

template<typename K, typename V>
void BiTree<K, V>::valuesRecur(Node *curNode, std::list<V> &list) const
{
    if(!curNode)
        return;
    valuesRecur(curNode->left, list);
    list.push_back(curNode->value);
    valuesRecur(curNode->right, list);
}

template<typename K, typename V>
void BiTree<K, V>::keysRecur(Node *curNode, std::list<K> &list) const
{
    if(!curNode)
        return;
    keysRecur(curNode->left, list);
    list.push_back(curNode->key);
    keysRecur(curNode->right, list);
}

template<typename K, typename V>
void BiTree<K, V>::writeRecur(Node *curNode, std::ofstream &f) const
{
    if(!curNode)
        return;
    writeRecur(curNode->left, f);
    f << curNode->key << " " << curNode->value << std::endl;
    writeRecur(curNode->right, f);
}

template<typename K, typename V>
typename BiTree<K, V>::Node *BiTree<K, V>::find(const K &k) const
{
    if(!this->contains(k))
        return nullptr;

    Node *curNode = root;
    while(curNode->key != k)
    {
        if(k < curNode->key)
            curNode = curNode->left;
        else curNode = curNode->right;
    }
    return curNode;
}

template<typename K, typename V>
V BiTree<K, V>::value_in_key(const K &k) const
{
    Node *curNode = this->find(k);
    if(!curNode)
        return V();
    else
        return curNode->value;
}

#endif // BITREE_H

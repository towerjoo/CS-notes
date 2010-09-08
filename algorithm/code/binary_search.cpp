#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


typedef struct BinarySearchTree
{
    int key;
    string value;
    struct BinarySearchTree *left;
    struct BinarySearchTree *right;
}BinarySearchTree;


void insert(BinarySearchTree* root, pair<int, string> elem)
{
    if(root == NULL)
    {
        root = new BinarySearchTree;
        root->key = elem.first;
        root->value = elem.second;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if(root->left == NULL && root->right == NULL)
    {
        if(root->key > elem.first)
        {
            BinarySearchTree* newelm = new BinarySearchTree;
            newelm->left = NULL;
            newelm->right = NULL;
            newelm->key = elem.first;
            newelm->value = elem.second;
            root->left = newelm;
            return;
        }
        else if (root->key == elem.first)
            return;
        else
        {
            BinarySearchTree* newelm = new BinarySearchTree;
            newelm->left = NULL;
            newelm->right = NULL;
            newelm->key = elem.first;
            newelm->value = elem.second;
            root->right = newelm;
            return;
        }
    }
    else if(root->key > elem.first)
        insert(root->left, elem);
    else if(root->key == elem.first)
        return;
    else
        insert(root->right, elem);

}

void print(BinarySearchTree* root)
{
    if(root == NULL)
        return;
    print(root->left);
    cout<<"key: "<<root->key<<"  value:"<<root->value;
    print(root->right);
}

int main()
{
    map<int, string> dict;
    dict.insert(pair<int, string>(0, "zhutao"));
    dict.insert(pair<int, string>(2, "yaya"));
    dict.insert(pair<int, string>(1, "kexue"));
    BinarySearchTree *root =NULL;
    for(map<int,string>::iterator iter=dict.begin(); iter!=dict.end(); iter++)
        insert(root, *iter);
    print(root);


    return 0;
}

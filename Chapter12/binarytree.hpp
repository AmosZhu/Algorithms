#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>

template<typename elemType>
struct nodeType
{
    elemType info;
    nodeType<elemType>* lLink;
    nodeType<elemType>* rLink;
};

template<typename elemType>
class binaryTreeType
{
public:
    binaryTreeType(void);
    binaryTreeType(const binaryTreeType<elemType>& otherTree);
    virtual ~binaryTreeType(void);

    const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>& otherTree);
    bool isEmpty(void);

    void preorderTraversal(void);
    void inorderTraversal(void);
    void postorderTraversal(void);
    int treeHeight(void);
    int treeNodeCount(void);
    int treeleavesCount(void);
    void destroyTree(void);


protected:
    nodeType<elemType>* root;

private:
    void copyTree(nodeType<elemType>* &copiedTreeNode,nodeType<elemType>* otherTreeNode);
    void destroy(nodeType<elemType>* &p);
    void inorder(nodeType<elemType>* p);
    void preorder(nodeType<elemType>* p);
    void postorder(nodeType<elemType>* p);
    int height(nodeType<elemType>* p);
    int max(int x,int y);
    int nodeCount(nodeType<elemType>* p);
    int leavesCount(nodeType<elemType>* p);
};


template<typename elemType>
binaryTreeType<elemType>::binaryTreeType(void)
{
    root=NULL;
}

template<typename elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
    if(otherTree.root==NULL)
    {
        root=NULL;
        return;
    }

    copyTree(root,otherTree);
}

template<typename elemType>
binaryTreeType<elemType>::~binaryTreeType(void)
{
    destroy(root);
}

template<typename elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
    if(this==otherTree)
        return this;

    if(root!=NULL)
        destroy(root);

    if(otherTree.root==NULL)
    {
        root=NULL;
        return;
    }

    copyTree(root,otherTree);
}


template<typename elemType>
bool binaryTreeType<elemType>::isEmpty(void)
{
    return(root==NULL);
}

template<typename elemType>
void binaryTreeType<elemType>::preorderTraversal(void)
{
    std::cout<<"Preorder: ";
    preorder(root);
	std::cout<<std::endl;
}

template<typename elemType>
void binaryTreeType<elemType>::inorderTraversal(void)
{
    std::cout<<"Inorder: ";
    inorder(root);
	std::cout<<std::endl;
}

template<typename elemType>
void binaryTreeType<elemType>::postorderTraversal(void)
{
    std::cout<<"Postorder: ";
    postorder(root);
	std::cout<<std::endl;
}

template<typename elemType>
int binaryTreeType<elemType>::treeHeight(void)
{
    return height(root);
}

template<typename elemType>
int binaryTreeType<elemType>::treeNodeCount(void)
{
    return nodeCount(root);
}

template<typename elemType>
int binaryTreeType<elemType>::treeleavesCount(void)
{
    return leavesCount(root);
}

template<typename elemType>
void binaryTreeType<elemType>::destroyTree(void)
{
    destroy(root);
}

template<typename elemType>
void binaryTreeType<elemType>::copyTree(nodeType<elemType>* &copiedTreeNode,nodeType<elemType>* otherTreeNode)
{
    if(otherTreeNode==NULL)
    {
        copiedTreeNode=NULL;
        return;
    }


    copiedTreeNode=new nodeType<elemType>;
    copiedTreeNode->info=otherTreeNode->info;
    copyTree(copiedTreeNode->lLink,otherTreeNode->lLink);
    copyTree(copiedTreeNode->rLink,otherTreeNode->rLink);

    return;
}

template<typename elemType>
void binaryTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
    if(p==NULL)
        return;

    destroy(p->lLink);
    destroy(p->rLink);
    delete p;
    p=NULL;
    return;
}

template<typename elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType>* p)
{
    if(p==NULL)
        return;

    inorder(p->lLink);
    std::cout<<p->info<<" ";
    inorder(p->rLink);
    return;
}

template<typename elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType>* p)
{
    if(p==NULL)
        return;

    std::cout<<p->info<<" ";
    preorder(p->lLink);
    preorder(p->rLink);
    return;
}

template<typename elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType>* p)
{
    if(p==NULL)
        return;

    postorder(p->lLink);
    postorder(p->rLink);
    std::cout<<p->info<<" ";

    return;
}

template<typename elemType>
int binaryTreeType<elemType>::height(nodeType<elemType>* p)
{
    if(p==NULL)
        return 0;

    return 1+max(height(p->lLink),height(p->rLink));
}

template<typename elemType>
int binaryTreeType<elemType>::max(int x,int y)
{
    return x?y:x>=y;
}

template<typename elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType>* p)
{
    if(p==NULL)
        return 0;
    return 1+nodeCount(p->lLink)+nodeCount(p->rLink);
}

template<typename elemType>
int binaryTreeType<elemType>::leavesCount(nodeType<elemType>* p)
{
    if(p==NULL)
        return 0;

    if(p->rLink==NULL&&p->lLink==NULL)
        return 1;

    return leavesCount(p->rLink)+leavesCount(p->lLink);
}

#endif

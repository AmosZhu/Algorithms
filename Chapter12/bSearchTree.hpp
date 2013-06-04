#ifndef _BSEARCHTREE_HPP
#define _BSEARCHTREE_HPP

#include "binaryTree.hpp"
#include <iostream>

template<typename elemType>
class bSearchTreeType:public binaryTreeType<elemType>
{
public:
    bool search(const elemType& item);
    void insert(const elemType& item);
    void deleteNode(const elemType& item);

private:
    void deleteFromTree(nodeType<elemType>* &p);
};


template<typename elemType>
bool bSearchTreeType<elemType>::search(const elemType& item)
{
    bool found=false;
    nodeType<elemType>* current;

    if(root!=NULL)
    {
        current=root;
        while(current!=NULL&&found==false)
        {
            if(current->info==item)
            {
                found=true;
                continue;
            }
            if(current->info>item)
                current=current->lLink;
            else
                current=current->rLink;
        }
    }

    return found;
}

template<typename elemType>
void bSearchTreeType<elemType>::insert(const elemType& item)
{
    nodeType<elemType>* current;
    nodeType<elemType>* newNode;
    nodeType<elemType>* tailNode;

    newNode=new nodeType<elemType>;
    newNode->info=item;
    newNode->lLink=NULL;
    newNode->rLink=NULL;

    if(root==NULL)
        root=newNode;
    else
    {
        current=root;
        while(current!=NULL)
        {
            tailNode=current;
            if(newNode->info==current->info)
            {
                std::cout<<"Not allowed to insert same node!"<<std::endl;
                delete newNode;
                return;
            }
            if(newNode->info>current->info)
                current=current->rLink;
            else
                current=current->lLink;
        }

        if(newNode->info>tailNode->info)
            tailNode->rLink=newNode;
        else
            tailNode->lLink=newNode;

    }
}

template<typename elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& item)
{
    bool found=false;
    nodeType<elemType>* current;
    nodeType<elemType>* tailNode;

    if(root!=NULL)
    {
        current=root;
        tailNode=NULL;
        while(current!=NULL&&found==false)
        {
            if(current->info==item)
            {
                found=true;
                continue;
            }
            tailNode=current;
            if(current->info>item)
                current=current->lLink;
            else
                current=current->rLink;
        }
        if(current==NULL)
        {
            std::cout<<"item not in the binary tree!"<<std::endl;
            return;
        }
        else
        {
            if(tailNode!=NULL)
            {
                if(found)
                {
                    std::cout<<tailNode->info<<std::endl;
                    if(tailNode->info>item)
                        deleteFromTree(tailNode->lLink);
                    else
                        deleteFromTree(tailNode->rLink);
                }
            }
            else
                deleteFromTree(root);
        }
    }

}

template<typename elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType>* &p)
{
    nodeType<elemType>* temp;
    nodeType<elemType>* tailNode;
    nodeType<elemType>* current;

    if(p==NULL)
        return;

    if(p->rLink==NULL&&p->lLink==NULL)
    {
        temp=p;
        delete temp;
        p=NULL;
    }
    else if(p->rLink==NULL)
    {
        temp=p;
        p=p->lLink;
        delete temp;
    }
    else if(p->lLink==NULL)
    {
        temp=p;
        p=p->rLink;
        delete temp;
    }
    else
    {
        current=p->lLink;
        tailNode=NULL;
        while(current->rLink!=NULL)
        {
            tailNode=current;
            current=current->rLink;
        }
        p->info=current->info;
        if(tailNode==NULL)
            p->lLink=current->lLink;
        else
            tailNode->rLink=current->lLink;

        delete current;
    }
}

#endif

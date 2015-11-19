/*
File       : title.cpp
Program    : Program 4 - Binary Search Tree Indexes
Due Date   : December 4, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"

using namespace std;

//Add a title (Sort alphabetically)
bool TitleIndex::addTitle(std::string Y, int P)
{
    if (root == NULL)
    {
        root = new Node(Y, P);
        return true;
    } // end if
    else
    {
        return addTitle(root, Y, P);
    } // end else
    return false;
} // end addTitle

bool TitleIndex::addTitle(Node *& r, std::string my_Title, int my_key)
{
    if (my_Title == r->title)
        return false;
    else if (my_Title < r->title)
    {
        if (r->left == NULL)
        {
            r->left = new Node(my_Title, my_key);
            return true;
        }
        else
            return addTitle(r->left, my_Title, my_key);
    }
    else if (my_Title > r->title)
    {
        if (r->right == NULL)
        {
            r->right = new Node(my_Title, my_key);
            return true;
        }
        else
            return addTitle(r->right, my_Title, my_key);
    }
    return false;
} // end addTitle using Node

//Display all titles
void TitleIndex::getAllTitles()
{
    postOrder(root, 0);
} // end getAllTitles

void TitleIndex::postOrder(Node* r, int indent)
{
    if(r != NULL) {
        if(r->left) postOrder(r->left, indent+4);
        if(r->right) postOrder(r->right, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout<< r->title << "\n ";
    }
}

//Write out titles
void TitleIndex::writeFile()
{
    Node * wp = root->left;
    ofstream fout("title_index.txt");
    fout << size << endl;
    while(wp != NULL)
    {
        fout << wp->title << " " << wp->pos << endl;
        wp = wp->left;
    } //end while
    fout.close();
} // end writeFile

//Read in titles
void TitleIndex::readFile()
{
    string newTitle;
    int newPos;
    int numOfTitles = 0;

    ifstream fin("title_index.txt");
    fin >> numOfTitles;
    for(int i = 0; i < numOfTitles+2; ++i)
    {
        fin >> newTitle >> newPos;
        addTitle(newTitle, newPos);
    } // end for
    fin.close();
} // end readFile

//Delete a title by title
void TitleIndex::deleteTitleByTitle(string T)
{
    Node * wp = root->left;
    while(wp != NULL)
    {
        if(wp->title == T)
        {
            wp->right->left = wp->left;
            wp->left->right = wp->right;
            delete wp;
            size--;
            return;
        } // end if
        else
        {
            wp = wp->left;
        } // end else
    } //end while

    return;
} // end deleteTitleByTitle

//Return a array of the positions of all titles (already sorted)
std::vector<int> TitleIndex::printAllAlphabetically()
{
    try
    {
        std::vector<int> myVector;
        Node * wp = root->left;

        while(wp != NULL)
        {
            myVector.push_back(wp->pos);
            wp =  wp->left;
        } // end while

        return myVector;
    } // try
    catch(std::bad_alloc& ba)
    {
        cout << " Primary Index file not found" << endl;
    }
    std::vector<int> newVector;
    return newVector;


} // end printAllAlphabetically

//Delete a title by position
void TitleIndex::deleteTitleByPosition(int P)
{
    Node * wp = root->left;
    while(wp != NULL)
    {
        if(wp->pos == P)
        {
            wp->right->left = wp->left;
            wp->left->right = wp->right;
            delete wp;
            size--;
            return;
        } // end if
        else
        {
            wp = wp->left;
        } // end else
    } //end while

} // end deleteTitleByPosition

//Delete a title by title or position
void TitleIndex::deleteTitle(string T, int P)
{
    if(P>0)
        deleteTitleByPosition(P);
    if(T.length() > 1)
        deleteTitleByTitle(T);
    return;
} // end deleteTitle

//Find a title and return its pos
bool TitleIndex::findTitle(string T, int& P)
{
    Node * wp = root;

    while(wp != NULL)
    {
        if(wp->title == T)
        {
            P = wp->pos;
            return true;
        }
         wp = wp->left;
    } // end while
      P = 0;
      return false;
} //end findTitle

//Update a title
void TitleIndex::updateTitle(string oldtitle, string newTitle)
{
    Node * wp = root->left;

    while(wp != NULL)
    {
        if(wp->title == oldtitle)
        {
            int position = wp->pos;
            //Delete old title and add new title
            //This retains sorting
            deleteTitle(oldtitle, 0);
            addTitle(newTitle, position);
            return;
        }
        wp = wp->left;
    } // end while
} // end updateTitle

int TitleIndex::getSize()
{
    return size;
} // end getSize

void TitleIndex::killTree()
{
    RealKillTree(root);
};
void TitleIndex::RealKillTree(Node *&r)
{
    if(r == NULL) return;
    RealKillTree(r->left);
    RealKillTree(r->right);
    delete r;
    return;
}
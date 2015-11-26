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
bool TitleIndex::addTitle(std::string T, int P, int Pr)
{
    if (root == NULL)
    {
        root = new Node(T, P, Pr);
        ++size;
        return true;
    } // end if
    else
    {
        return addTitle(root, T, P, Pr);
    } // end else
    return false;
} // end addTitle

//Add Title recursively
bool TitleIndex::addTitle(Node *& r, std::string my_Title, int my_key, int my_price)
{
    if (my_Title == r->title)
        return false;
    else if (my_Title < r->title)
    {
        if (r->left == NULL)
        {
            r->left = new Node(my_Title, my_key, my_price);
            ++size;
            return true;
        }
        else
            return addTitle(r->left, my_Title, my_key, my_price);
    }
    else if (my_Title > r->title)
    {
        if (r->right == NULL)
        {
            r->right = new Node(my_Title, my_key, my_price);
            ++size;
            return true;
        }
        else
            return addTitle(r->right, my_Title, my_key, my_price);
    }
    return false;
} // end addTitle using Node

//Display all titles
void TitleIndex::getAllTitles()
{
    pushNodes();
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        cout << nodes[i]->title << " " << nodes[i]->price << " " << nodes[i]->pos << endl;
    }
} // end getAllTitles

//Push nodes into the vector array
void TitleIndex::pushNodes()
{
    nodes.clear();
    pushNode(root);
} // end pushNodes

//Push a node into the vector array
void TitleIndex::pushNode(Node* r)
{
    if(r != NULL)
    {
        if(r->left != NULL)
            pushNode(r->left);
        nodes.push_back(r);
        if(r->right != NULL)
            pushNode(r->right);
    }
} // end pushNode

//Write out titles
void TitleIndex::writeFile()
{
    //Push nodes in the vector array
    pushNodes();
    ofstream fout("title_index.txt");
    fout << size << endl;
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        fout << nodes[i]->title << " " << nodes[i]->price << " " << nodes[i]->pos << endl;
    }
    fout.close();
} // end writeFile

//Read in titles
void TitleIndex::readFile()
{
    string newTitle;
    int newPos = 0;
    int newPrice = 0;
    int numOfTitles = 0;

    ifstream fin("title_index.txt");
    fin >> numOfTitles;
    for(int i = 0; i < numOfTitles; ++i)
    {
        fin >> newTitle >> newPrice >> newPos;
        addTitle(newTitle, newPos, newPrice);
    } // end for
    fin.close();
} // end readFile

//Delete a title by title
void TitleIndex::deleteTitleByTitle(string T)
{
    deleteTitleByTitle(root, T);
} // end deleteTitleByTitle

//Delete Title by Title recursively
TitleIndex::Node* TitleIndex::deleteTitleByTitle(Node*& r, string T)
{
    if(r == NULL)
        return r;
    else if(T < r->title)
        r->left = deleteTitleByTitle(r->left, T);
    else if(T > r->title)
        r->right = deleteTitleByTitle(r->right, T);
    else
    {
        //if no children
        if(r->left == NULL && r->right == NULL)
        {
            delete r;
            r = NULL;
            --size;
        }
        //if no left child
        else if(r->left == NULL)
        {
            Node *temp = r;
            r = r->right;
            delete temp;
            --size;
        }
        //if no right child
        else if(r->right == NULL)
        {
            Node *temp = r;
            r = r->left;
            delete temp;
            --size;
        }
        //if left child and right child
        else
        {
            Node *temp = findMinNode(r->right);
            r->title = temp->title;
            r->pos = temp->pos;
            r->price = temp->price;
            r->right = deleteTitleByTitle(r->right, temp->title);
        }
    } // end else
    return r;
} // end deleteTitleByTitle

//Get lowest node
TitleIndex::Node* TitleIndex::findMinNode(Node*& r)
{
    while(r->left != NULL)
        r = r->left;
    return r;
} // end findMinNode

//Return a array of the positions of all titles (already sorted)
std::vector<int> TitleIndex::printAllAlphabetically()
{
    try
    {
        std::vector<int> myVector;
        pushNodes();

        for (int i = 0; i < (int)nodes.size(); ++i)
        {
            myVector.push_back(nodes[i]->pos);
        }

        return myVector;
    } // try
    catch(std::bad_alloc& ba)
    {
        cout << " Primary Index file not found" << endl;
    }
    std::vector<int> newVector;
    return newVector;
} // end printAllAlphabetically

//Return a array of the positions of all titles (already sorted)
std::vector<int> TitleIndex::printAllReverseAlphabetically(int userPrice)
{
    try
    {
        std::vector<int> myVector;
        pushNodes();

        for (int i = 0; i < (int)nodes.size(); ++i)
        {
            if(nodes[i]->price < userPrice)
                myVector.push_back(nodes[i]->pos);
        }

        return myVector;
    } // try
    catch(std::bad_alloc& ba)
    {
        cout << " Primary Index file not found" << endl;
    }
    std::vector<int> newVector;
    return newVector;
} // end printAllReverseAlphabetically

//Delete a title by title or position
void TitleIndex::deleteTitle(string T, int P)
{
    if(T.length() > 1)
        deleteTitleByTitle(T);
    return;
} // end deleteTitle

//Find a title and return its pos
bool TitleIndex::findTitle(string T, int& P)
{
    return findTitleNode(root, T, P);
} //end findTitle

//Find a title and return its pos using Node
bool TitleIndex::findTitleNode(Node *& r, string T, int& P)
{
    if(r!=NULL)
    {
        if(T == r->title)
        {
            P = r->pos;
            return true;
        }
        if(T < r->title)
            return findTitleNode(r->left, T, P);
        else
            return findTitleNode(r->right, T, P);
    }
    else
        return false;
} //end findTitle


//Update a title
void TitleIndex::updateTitle(string oldtitle, string newTitle, int newPrice)
{
    int position = 0;
    if(findTitle(oldtitle, position))
    {
        //Delete old title and add new title
        //This retains sorting
        deleteTitle(oldtitle, 0);
        addTitle(newTitle, position, newPrice);

    }
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

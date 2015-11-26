/*
File       : year.cpp
Program    : Program 4 - Binary Search Tree Indexes
Due Date   : December 4, 2015
Author     : Justin Kirk
Description: Year - secondary index
*/

#include "year.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

//Add a year (Sort alphabetically) (1,2,3)
void YearIndex::addYear(int Y, int P)
{
    if (root == NULL)
    {
        root = new Node(Y, P);
        root->up = new Node(-1, 1);
        root->up->up = new Node(-1, P);
        root->up->up->down = root->up;
        ++size;
        return;
    } // end if
    else
    {
        addYear(root, Y, P);
    } // end else
} // end addYear

void YearIndex::addYear(Node *& r, int my_Year, int my_key)
{
    if (my_Year == r->year)
    {
        r->up->pos = r->up->pos + 1;
        Node * holdUp = r->up;
        while(holdUp->up != NULL)
        {
            holdUp = holdUp->up;
        } // end while
        Node * p = new Node(-1,my_key);
        p->down = holdUp->down;
        p->up = holdUp;
        holdUp->down->up=p;
        holdUp->down=p;
    }
    else if (my_Year < r->year)
    {
        if (r->left == NULL)
        {
            r->left = new Node(my_Year, my_key);
            r->left->up = new Node(-1, 1);
            r->left->up->up = new Node(-1, my_key);
            r->left->up->up->down = r->left->up;
            ++size;
            return;
        }
        else
            return addYear(r->left, my_Year, my_key);
    }
    else if (my_Year > r->year)
    {
        if (r->right == NULL)
        {
            r->right = new Node(my_Year, my_key);
            r->right->up = new Node(-1, 1);
            r->right->up->up = new Node(-1, my_key);
            r->right->up->up->down = r->right->up;
            ++size;
            return;
        }
        else
            return addYear(r->right, my_Year, my_key);
    }
} // end addYear using Node

//Update a year
void YearIndex::updateYear(int old_year, int new_year, int old_pos)
{
    int holdLocation = 0;

    //If new year does not currently exist...
    if(!matchYear(new_year, holdLocation))
    {
        addYear(new_year, old_pos);
    } // end if
    else
    {
        //Copy positions to new location

         Node * newNode = findYearNode(root, new_year, holdLocation);

        //Update count
        newNode->up->pos = newNode->up->pos + 1;

        //Find empty up in newNode
        Node * newUp = newNode->up;
        while(newUp->up != NULL)
        {
            newUp = newUp->up;
        } // end while

        //Add New Up
        Node * p = new Node(-1,old_pos);
        p->down = newUp->down;
        p->up = newUp;
        newUp->down->up=p;
        newUp->down=p;

    } // end else
    //Delete Old Up
    deleteYear(old_year, old_pos);
} // end updateYear

//Display all years
void YearIndex::getAllYears()
{
    pushNodes();
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        std::cout << nodes[i]->year << " " << nodes[i]->up->pos << std::endl;
    }
} // end getAllArtists

//Push nodes into the vector array
void YearIndex::pushNodes()
{
    nodes.clear();
    pushNode(root);
} // end pushNodes

//Push a node into the vector array
void YearIndex::pushNode(Node* r)
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

//Write out years
void YearIndex::writeFile()
{
    std::ofstream fout("year_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    //For each item in Linked List
     for (int i = 0; i < (int)nodes.size(); ++i)
    {
        Node * wp = nodes[i];
        //Default
        buildLine = " ";
        //Number of Keys
        std::stringstream strs;
        if(wp->up != NULL)
        {
            strs << wp->up->pos;
            std::string temp_str = strs.str();
            //Add number of keys to numOfKeys
            numOfKeys = temp_str + " ";

            Node * holdUp = wp->up->up;
            //for each item in pos
            while(holdUp != NULL)
            {
                if(holdUp->pos != 0)
                {
                    //Convert the key to a string
                    std::stringstream strs;
                    strs << holdUp->pos;
                    std::string temp_str = strs.str();
                    //Add key to buildLine
                    buildLine += temp_str + " ";
                } //end if
                holdUp = holdUp->up;
            } // end while

            //If there is at least 1 key then write to file
            if(wp->up->pos != 0)
            {
                //Write to file
                fout << numOfKeys
                     << wp->year
                     << buildLine
                     << std::endl;
            } // end if
        } // end if
    } //end for

    //Close file
    fout.close();
} // end writeSecondary

//Read in years
void YearIndex::readFile()
{
    std::ifstream input("year_index.txt");
    std::string line;
    getline (input,line);
    size = atoi(line.c_str());

    if (input.is_open())
    {
        //Set position to 1
        long position = 1;
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        size_t pos = 0;
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;
        //Number of keys in line
        int numOfKeys = 0;
        //Year Input
        int year_input = -1;
        while(!input.eof() && position != (int)(size+1))
        {
            //Read in a line from the sequential file
            getline (input,line);

            //Defaults
            pos = 0;
            part = "";
            numOfKeys = 0;

            //Get Number of keys
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                numOfKeys = atoi(part.c_str());
            } // end if

            //Get year
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                year_input = atoi(part.c_str());
                line.erase(0, pos + delimiter.length());
                --size;
            } // end if

            //Set pos to keys in line
            for(int i = 0; i < numOfKeys; ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    addYear(year_input, atoi(part.c_str()));
                    line.erase(0, pos + delimiter.length());
                } // end if
            } // end for

            position++;
        } // End eof while
        input.close();
    } // end if
} // end readSecondary

//Find a year and return an array of positions
std::vector<int> YearIndex::findYear(int inYear)
{
    std::vector<int> myVector;

    //Push nodes in the vector array
    pushNodes();

    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        Node * wp = nodes[i];
        if(wp->year == inYear)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                Node * holdUp = wp->up;
                int j = 0;

                while(holdUp != NULL)
                {
                    myVector.insert(myVector.begin() + j, holdUp->pos);
                    holdUp = holdUp->up;
                    ++j;
                } // end while
                break;
            } // end if
            else
                break;
        } // end if
    } // end for

    return myVector;
} // end findYear

//Match a year
bool YearIndex::matchYear(int inYear, int &pos)
{
    Node * wp = root->left;

    while(wp != NULL)
    {
        if(wp->year == inYear)
        {
            pos = wp->up->pos;
            return true;
        } // end if
        wp = wp->left;
    } // end while
    pos = 0;
    return false;
} // end matchYear

//Find a year and return its pos using Node
YearIndex::Node * YearIndex::findYearNode(Node *& r, int Y, int& P)
{
    if(r!=NULL)
    {
        if(Y == r->year)
        {
            P = r->pos;
            return r;
        }
        if(Y < r->year)
            return findYearNode(r->left, Y, P);
        else
            return findYearNode(r->right, Y, P);
    }
    else
        return NULL;
} //end findYearNode

//Delete a year
bool YearIndex::deleteYear(int inYear, int pos)
{
    deleteYearByYear(root, inYear, pos);
} // end deleteYear

//Delete year by year recursively
YearIndex::Node* YearIndex::deleteYearByYear(Node*& r, int A, int pos)
{
    if(r == NULL)
        return r;
    else if(A < r->year)
        r->left = deleteYearByYear(r->left, A, pos);
    else if(A > r->year)
        r->right = deleteYearByYear(r->right, A, pos);
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
            r->year = temp->year;
            r->pos = temp->pos;
            r->right = deleteYearByYear(r->right, temp->year, temp->pos);
        }
    } // end else
    return r;
} // end deleteYearByYear

//Get lowest node
YearIndex::Node* YearIndex::findMinNode(Node*& r)
{
    while(r->left != NULL)
        r = r->left;
    return r;
} // end findMinNode

void YearIndex::killTree()
{
    RealKillTree(root);
};
void YearIndex::RealKillTree(Node *&r)
{
    if(r == NULL) return;
    RealKillTree(r->left);
    RealKillTree(r->right);
    RealKillTreeMiddle(r->up);
    delete r;
    return;
}
void YearIndex::RealKillTreeMiddle(Node *&m)
{
    if(m == NULL) return;
    if(m->up != NULL)
        RealKillTreeMiddle(m->up);
    delete m;
    m = NULL;
    return;
}


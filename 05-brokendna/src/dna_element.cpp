////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <vector>
#include "dna_element.h"

using namespace std;
// TODO: implement
DNAElement::DNAElement()
{
    id = "";
    number = 0;
    base = "";
}

DNAElement::DNAElement(const std::string &description)
{
    readFromString(description);
}

void DNAElement::readFromString(const std::string &description)
{
    vector<string> _vec;
    int i = 0;
    string _str = "";
    while(i != description.length())
    {
        if(description[i] != ' ')
            _str += description[i];
        else
        {
            _vec.push_back(_str);
            _str = "";
        }
        i++;
        if(i == description.length())
            _vec.push_back(_str);
    }
    for (int i = 0; i < _vec.size(); ++i)
    {
        _str = _vec[i];
        if(_str[0] >= 'a' && _str[0] <= 'z')
            id = _str[0];
        else
            throw invalid_argument("Invalid Argument!");
        int m = 1;
        string numb = "";
        while(_str[m] != ':')
        {
            if(m > _str.length())
                throw invalid_argument("Invalid argument");
            numb += _str[m];
            m++;
        }
        number = stoi(numb);
        if(number <= 0)
            throw invalid_argument("Invalid argument");
        ++m;
        if(_str[m] == 'A' || _str[m] == 'C' || _str[m] == 'T' || _str[m] == 'G')
            base = _str[m];
        else
            throw invalid_argument("Invalid argument");
    }
}
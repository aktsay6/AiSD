////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!
using namespace xi;
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован linked_list.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



// Creating chains and checking each elements id. If there is no id we create a chain and add it to the map.
// If there is such id in the map, then we just put element in chain.
// We have vector of strings as well, which contains ids, so that we could sort it in the future.
// We can get a chain from the map by key, so there is vector of ids.

void DNARepairer::repairDNA()
{
    // Начало примера
    // ВАЖНО! Все содержимое этого метода всего лишь пример.
    // Удалите его и перепишите функцию repairDNA заново.
    //// Конец примера
    
    //Write your code here...
    NodeDNAChain* nodeDNAChain = _dnaStorage.getPreHead();
    NodeDNA* nodeDNA;
    vector<string> vecOfIds;
    ListOfDNAChains _newList;
    Id2DnaMap map;
    while(nodeDNAChain->next != nullptr)
    {
        nodeDNAChain = nodeDNAChain->next;
        nodeDNA = nodeDNAChain->value.getPreHead();
        nodeDNA = nodeDNA->next;
        DNAChain* chain;
        while(nodeDNA != nullptr)
        {
            if(map.find(nodeDNA->value.id) == map.end())
            {
                chain = new DNAChain();
                DNAElement element = nodeDNA->value;
                chain->addElementToEnd(element);
                map.insert(pair<string, DNAChain*>(nodeDNA->value.id, chain));
                vecOfIds.push_back(nodeDNA->value.id);
            } else
            {
                chain = map.find(nodeDNA->value.id)->second;
                chain->addElementToEnd(nodeDNA->value);
            }
            nodeDNA = nodeDNA->next;
        }
    }
    //sort chains by numbers
    for (int k = 0; k < vecOfIds.size(); ++k)
    {
        DNAChain* chain = map.find(vecOfIds[k])->second;
        for (int i = 0; i < chain->size(); ++i)
        {
            int _cur = 0;
            while(_cur < chain->size())
            {
                if(chain->operator[](i).number < chain->operator[](_cur).number)
                {
                    DNAElement tmp = chain->operator[](i);
                    chain->operator[](i) = chain->operator[](_cur);
                    chain->operator[](_cur) = tmp;
                }
                _cur++;
            }
        }
    }
    // chain alphabetical sort
    for (int j = 0; j < vecOfIds.size(); ++j)
    {
        int _cur = 0;
        while(_cur < vecOfIds.size())
        {
            if (vecOfIds[j] < vecOfIds[_cur])
            {
                string tmp = vecOfIds[j];
                vecOfIds[j] = vecOfIds[_cur];
                vecOfIds[_cur] = tmp;
            }
            _cur++;
        }
    }

    for (int i = 0; i < vecOfIds.size(); ++i)
    {
        _newList.addElementToEnd(*map.find(vecOfIds[i])->second);
    }
    _dnaStorage = _newList;
}

void DNARepairer::printDNAStorage()
{
    printToStream(cout);
}

string DNARepairer::dnaChainToString(NodeDNAChain* dnaChain)
{
    stringstream ss;
    
    NodeDNA* it2 = dnaChain->value.getPreHead();
    while (it2->next != nullptr)
    {
        it2 = it2->next;
        //итерация по списку ДНК

        ss << it2->value.id << "" << it2->value.number << ":";
        ss << it2->value.base << "  ";
    }
    return ss.str();
}


void DNARepairer::printToStream(std::ostream& outStream)
{
    xi::Node<DNARepairer::DNAChain>* it1 = _dnaStorage.getPreHead();
    while (it1->next != nullptr)
    {
        it1 = it1->next;
        outStream << dnaChainToString(it1) << endl;
    }
}


void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        throw std::runtime_error("Could not open file");
    
    readFromStream(fin);
}

void DNARepairer::readFromStream(std::istream& inStream)
{
    // начинаем с головы
    NodeDNAChain* it = _dnaStorage.getPreHead();

    string line;
    while (getline(inStream, line))
    {
        // Создаем узел ДНК на куче
        NodeDNAChain* pNewNode = new NodeDNAChain;                

        //Создаем строковый поток для разбора
        istringstream istr(line);
        
        string strTmp;
        while (istr >> strTmp)                                  // разбиваем поток на слова
        {
            DNAElement tmpDNAElement(strTmp);                   // каждое слово читаем в DNAElement
            pNewNode->value.addElementToEnd(tmpDNAElement);     // добавляем полученный DNAElement в ДНК            
        }
        it->next = pNewNode;
        it = it->next;
        
    }
}

DNARepairer::ListOfDNAChains& DNARepairer::getDNAStorage()
{
    return _dnaStorage;
}

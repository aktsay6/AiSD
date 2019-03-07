////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

namespace xi {

template <class T>
LinkedList<T>::LinkedList()
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;

    // TODO: Write your code here
    // ...
}

template <class T>
LinkedList<T>::~LinkedList()
{
    // TODO: Write your code here
    Node<T>* current = _preHead;
    while (current != nullptr)
    {
        Node<T>* tmp = current->next;
        delete current;
        current = tmp;
    }
    // на забудьте удалить искусственный элемент
}

    // TODO: Write your code here

    template <class T>
    LinkedList<T>::LinkedList(const xi::LinkedList<T> &other)
    {
        if (other._preHead == nullptr)
            return;

        Node<T>* current = new Node<T>(*other._preHead);

        _preHead = current;

        Node<T>* anotherIter = other._preHead->next;

        while (anotherIter != nullptr)
        {
            current->next = new Node<T>(*anotherIter);
            current = current->next;
            anotherIter = anotherIter->next;
        }
    }

    template <class T>
    LinkedList<T>& LinkedList<T>::operator=(const xi::LinkedList<T> &other)
    {
        LinkedList<T>* cur = new LinkedList<T>(other);

        _preHead = cur->_preHead;

        return *this;
    }

    template <class T>
    Node<T>* LinkedList<T>::getPreHead()
    {
        return _preHead;
    }

    template <class T>
    void LinkedList<T>::addElementToEnd(T &value)
    {
        Node<T>* nd = _preHead;
        while(nd->next != nullptr)
        {
            nd = nd->next;
        }
        Node<T>* _elem = new Node<T>();
        _elem->value = value;
        _elem->next = nullptr;
        nd->next = _elem;
    }
    template <class T>
    void LinkedList<T>::deleteNodes(xi::Node<T>* pNodeBefore, xi::Node<T>* pNodeLast)
    {
        if(!pNodeBefore || !pNodeLast || !pNodeBefore->next)
            return;
        Node<T>* _cur = pNodeBefore->next;

        while (_cur != pNodeLast)
        {
            Node<T>* toDel = _cur;
            _cur = _cur->next;
            delete toDel;
        }
        pNodeBefore->next = _cur->next;
        delete _cur;
    }

    template <class T>
    void LinkedList<T>::deleteNextNode(xi::Node<T> *pNodeBefore)
    {
        if(!pNodeBefore || !pNodeBefore->next)
            return;
        Node<T>* del = pNodeBefore->next;
        pNodeBefore->next = del->next;
        delete del;
    }

    template <class T>
    int LinkedList<T>::size()
    {
        int size = 0;
        Node<T>* nd = _preHead;
        while(nd->next != nullptr)
        {
            size++;
            nd = nd->next;
        }
        return size;
    }

    template <class T>
    void LinkedList<T>::moveNodesToEnd(xi::Node<T> *pNodeBefore, xi::Node<T> *pNodeLast)
    {
        if(!pNodeBefore || !pNodeLast || !pNodeBefore->next)
            return;
        Node<T>* _cur = pNodeBefore;
        while(_cur != pNodeLast->next)
        {
            _cur = _cur->next;
            moveNodeToEnd(_cur);
        }
    }

    template <class T>
    void LinkedList<T>::moveNodeToEnd(xi::Node<T> *pNodeBefore)
    {
        if(!pNodeBefore || !pNodeBefore->next)
            return;
        addElementToEnd(pNodeBefore->next->value);
        deleteNextNode(pNodeBefore);
    }

    template <class T>
    void LinkedList<T>::moveNodesAfter(xi::Node<T> *pNode, xi::Node<T> *pNodeBefore, xi::Node<T> *pNodeLast)
    {
        //checking
        if(!pNode || !pNodeBefore || !pNodeLast)
            throw std::logic_error("LIL");
        Node<T>* _last = pNodeLast->next;
        Node<T>* _curPNode = pNode;
        Node<T>* _cur = pNodeBefore;
        while(_cur->next != pNodeLast)
        {
           moveNodeAfter(_curPNode, _cur);
           _curPNode = _curPNode->next;
        }
        moveNodeAfter(_curPNode, _cur);
        pNodeBefore->next = _last;
    }

    template <class T>
    void LinkedList<T>::moveNodeAfter(xi::Node<T> *pNode, xi::Node<T> *pNodeBefore)
    {
        if(!pNode || !pNodeBefore || !pNodeBefore->next)
            return;
        Node<T>* next = pNode->next;
        Node<T>* copy = pNodeBefore->next;
        Node<T>* _newNode = new Node<T>(*copy);
        pNode->next = _newNode;
        _newNode->next = next;
        deleteNextNode(pNodeBefore);
    }

    template <class T>
    T& LinkedList<T>::operator[](int i)
    {
        if(i >= size() || i < 0)
            throw std::out_of_range("Out of range");
        Node<T>* nd = _preHead;
        int curNode = 0;
        while(curNode <= i)
        {
            nd = nd->next;
            curNode++;
        }

        return nd->value;
    }

    template <class T>
    Node<T>& Node<T>::operator=(const xi::Node<T> &other)
    {
        Node<T>* cur = new Node<T>(other);

        value = cur->value;
        next = cur->next;

        return *this;
    }

    template<class T>
    Node<T>::Node(const Node <T> &other)
    {
        T* cur = new T(other.value);
        value = *cur;
        next = nullptr;
    }
} // namespace xi
#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapify(int* ages, int n, int arrSize)
{
    int leftChild = 2*n + 1;
    int rightChild = 2*n + 2;
    int largest;

    if(leftChild < arrSize && ages[leftChild] > ages[n])
        largest = leftChild;
    else
        largest = n;
    if(rightChild < arrSize && ages[rightChild] > ages[largest])
        largest = rightChild;

    if(largest != n)
    {
        int cur = ages[n];
        ages[n] = ages[largest];
        ages[largest] = cur;
        heapify(ages, largest, arrSize);
    }
}

void heapBuild(int *ages, int n)
{
    for (int i = n/2; i >= 0; --i)
    {
        heapify(ages, i - 1, n);
    }
}
void heapSort(int *numbers, int array_size)
{
    heapBuild(numbers, array_size);
    for(int i = array_size - 1; i >= 0; i--)
    {
        int cur = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = cur;
        heapify(numbers, 0, i);
    }
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main() 
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
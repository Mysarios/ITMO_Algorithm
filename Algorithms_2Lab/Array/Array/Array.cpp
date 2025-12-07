#include <iostream>

#include "Library/TArray.h"

int main(int argc, char* argv[])
{
    TArray<int> array(2);
    for (int i = 0; i < 16; ++i)
    {
        array.insert(i + 1);
    }
    
    for (TArray<int>::TIterator it = array.iterator(); it.has_next(); it.next())
    {
        std::cout << it.get() << '\n';
    }
    
    for (auto& element : array)
    {
        element *= 2;
    }
    
    for (int i = 0; i < 16; ++i)
    {
        std::cout << array[i] << '\n';
    }


    return 0;
}

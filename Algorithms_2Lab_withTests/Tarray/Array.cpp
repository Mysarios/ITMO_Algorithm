#include <iostream>
#include <gtest/gtest.h>

#include "Library/TArray.h"
#include "Library/TArray_tests.h"

int main(int argc, char* argv[])
{
    if (0)
    {
        TArray<int> array(2);
        for (int i = 0; i < 16; ++i)
        {
            array.insert(i + 1);
        }

        for (TArray<int>::TIterator it = array.iterator(); it.has_next(); it.next())
        {
            std::cout << it.get() << ' ';
        }
        std::cout << std::endl;
        for (auto& element : array)
        {
            element *= 2;
        }

        for (int i = 0; i < 16; ++i)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }
    
    if (1)
    {
        ::testing::InitGoogleTest(&argc, argv);
        RUN_ALL_TESTS();
    }

    return 1;
}

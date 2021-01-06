#include <iostream>

int main()
{
    unsigned int size{10};
    auto a = new int[size];
    //do some stuff untill we realize that we should have declered more space

    {
        const unsigned int new_size{size * 2};
        auto tmp = new int[new_size];

        for (unsigned int i = 0; i < size; ++i)
            tmp[i] = a[i];

        delete[] a; // a became a dangling pointer
                    // a pointer without meaning
                    // if we don't delete a we would have a memory leak: memory portion 
                    // without access because we don't remember the adress

        a = tmp; //if we would not use a we should a = nullptr;
    }

    //note the scope so new_size and tmp would not be accesible anymore
}
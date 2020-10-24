#include "Hashtable.hpp"
#include <iostream>


int Hashtable::hash(std::string key)
{
    std::cout << "Hashing value = " << key << std::endl;

    int sum = 0;
    for (char ch : key)
        sum += ch;
    
    std::cout << "REsult = " << sum % size << std::endl;

    return sum % size;


}

void Hashtable::insert(std::string key, Token *value)
{
    int h = hash(key);
    int pos = h;

    do
    {
        if (!arr[pos] || arr[pos]->is_del)
        {
            // insert
            arr[pos] = new Pair(key, value);
            return;
        }
        else
        {
            // found same element
            if (arr[pos]->key == key)
                return; 
            pos = (pos + 1) % size;
        }
    } while (pos != h); // if pos == h again, the array is full

    throw("hashtable is full");
}

Token* Hashtable::find(std::string key)
{
    int h = hash(key);
    int pos = h;

    do {
        if (!arr[pos])
            return nullptr;
        else if (!arr[pos]->is_del)
            if (key == arr[pos]->key)
                return arr[pos]->value;
        pos = (pos + 1) % size;
    } while(pos != h); // if pos == h again, the array is full

    return nullptr;
}

Hashtable::Hashtable(int s)
{
    size = s;
    arr = new Pair* [size](); // parentheses to initialise 0's
}

Hashtable::Hashtable()
{
    size = 1024;
    arr = new Pair* [size]();
}

void Hashtable::print()
{
    int index = 1;
    const int len = 20;
    std::string buf;
    buf = "\n---------------------";
    for (int j = 0; j < len; j++)
        buf += "-";
    buf += "\n";

    for (int i = 0; i < size; i++)
    {
        if (!arr[i] || arr[i]->is_del)
            continue;

        buf += "| " + std::to_string(i) + "\t| " + arr[i]->key;
        index++;
        for (int j = len - arr[i]->key.length(); j > 0; j--) 
            buf += " ";
        buf += "| " + std::to_string((int)arr[i]->value->tag) + "\t|\n";
    }
    buf += "---------------------";
    for (int j = 0; j < len; j++)
        buf += "-";
    buf += "\n";
    std::cout << buf;
}

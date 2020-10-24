#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <map>
using namespace std;


enum LiteralT { Float, Int, Var };


bool isOperator(char ch)
{
    char operators[] = "+-*/%=^";

    for (int i = 0; i < 7; ++i)
        if (ch == operators[i])
            return true;
    return false;
}

string literalName (LiteralT literal)
{
    switch (literal)
    {
    case Int:
        return "Int";
        break;
    case Float:
        return "Float";
        break;
    case Var:
        return "Var";
        break;
    default:
        break;
    }
}

void print_table(map<string, LiteralT> &table)
{
    int i = 1;
    const int len = 20;

    cout << "---------------------";
    for (int j = 0; j < len; j++)
        cout << "-";
    cout << "\n";

    for (auto pair : table)
    {
        cout << "| " << i << "\t| " << pair.first;
        i++;
        for (int j = len - pair.first.length(); j > 0; j--) cout << " ";
        cout << "| " << literalName(pair.second) << "\t|\n";
    }

    cout << "---------------------";
    for (int j = 0; j < len; j++)
        cout << "-";
    cout << "\n";
}


// returns id of literal in table
void insert(map<string, LiteralT> &table, char *buffer, LiteralT type)
{
    auto _pair = table.insert(pair<string, LiteralT>(buffer, type));
}

int get_id(map<string, LiteralT> &table, char *buffer)
{
    return distance(table.begin(), table.find(buffer));
}

void print_output(map<string, LiteralT> &table)
{
    char ch, buffer[256];
    int j = 0;
    string output = "";
    ifstream fin("data.txt");

    bool isVar = false,
         isConst = false;
    int id;

    while (!fin.eof())
    {
        ch = fin.get();

        if (isspace(ch))
            continue;
        else if (isalpha(ch))
        {
            if (isConst)
                throw;
            isVar = true;
            buffer[j++] = ch;
        }
        else if (isdigit(ch) || ch == '.')
        {
            if (isVar) // it's ok
                { /* do nothing */ }
            else {
                isConst = true;
            }
            buffer[j++] = ch;
        }
        else if (isOperator(ch) || ch == ';')
        {
            if (isVar || isConst) 
            {
                // found
                buffer[j] = '\0';
                id = get_id(table, buffer);
                output += "<id" + to_string(id+1) + ">";
                isVar = isConst = false;
                j = 0;
            }
            output += ch;
        }
    }

    cout << output << endl;
}

int main()
{
    char ch, buffer[256];
    map<string, LiteralT> table;
    int j = 0;
    string output = "";
    ifstream fin("data.txt");

    if (!fin.is_open())
    {
        cout << "Error while opening the file\n";
        return 1;
    }

    bool isVar = false,
         isConst = false;
    int dots = 0;

    while (!fin.eof())
    {
        ch = fin.get();

        if (isspace(ch))
            continue;
        else if (isalpha(ch))
        {
            if (isConst)
                throw;
            isVar = true;
            buffer[j++] = ch;
        }
        else if (isdigit(ch) || ch == '.')
        {
            if (isVar) // it's ok
                { /* do nothing */ }
            else {
                isConst = true;
                if (ch == '.') dots++;
            }
            buffer[j++] = ch;
        }
        else if (isOperator(ch) || ch == ';')
        {
            if (isVar) 
            {
                // found
                buffer[j] = '\0';
                isVar = false;
                j = 0;
                insert(table, buffer, Var);
            } else if (isConst) 
            {
                // found 
                buffer[j] = '\0';
                insert(table, buffer, (dots == 0) ? Int : Float);
                // clear
                isConst = false;
                dots = 0;
                j = 0;
            }
            output += ch;
        }
    }

    print_table(table);
    print_output(table);

    fin.close();

    return 0;
}
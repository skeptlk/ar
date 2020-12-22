#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <iterator>
#include "Lexer.hpp"


class Optimizer {
public:
    std::vector <std::string> *lines;
    Lexer *lex;
    std::string result;
    
    Optimizer(std::vector <std::string> *l) {
        lines = l;
        lex = new Lexer();
    }

    void removeUnused() {
        std::set<Word*> unused;
        std::map<std::string, Token*>::iterator it;
        Word *w;
        Token *tok;

        for (std::string line: *lines) {
            lex->nextline(line);
            while (!lex->iseof) {
                tok = lex->scan();
            }
        }

        for (it = lex->words.begin(); it != lex->words.end(); it++) {
            if (it->second && it->second->tag == Tag::ID) {
                w = (Word*) it->second;
                if (w->use_count <= 1 && !isLabel(w))
                    unused.insert(w);
            }
        }

        std::cout << "Unused vars removed:";
        for (auto w: unused) std::cout << w->toString() << " ";
        std::cout << "\n";

        std::vector<std::string>::iterator list_i;
        std::set<Word*>::iterator set_i;
        for (list_i = lines->begin(); list_i != lines->end(); list_i++) {
            lex->nextline(*list_i);
            while (!lex->iseof) {
                tok = lex->scan();
                // check this token among unused variables
                // and delete line if found
                Word *tmp = (Word*)tok;
                set_i = unused.find(tmp);
                if (set_i != unused.end()) {
                    lines->erase(list_i);
                    break;
                }
            }
        }


        // join list of strings
		std::ostringstream os;
		std::copy(lines->begin(), lines->end() - 1,
			std::ostream_iterator<std::string>(os, "\n"));
		os << *lines->rbegin();
        result = os.str();
    }

    bool isLabel(Word *w) {
        std::string s = w->toString();
        if (s.length() > 0) return (s[0] == 'L');
        return false;
    }

    void removeTemps() {

    }

    void run () {
        removeUnused();
        removeTemps();
    }

};

void readFile (std::string filename, std::vector<std::string>* lines)
{
    lines->clear();
    std::ifstream file(filename);
    std::string s;

    while (std::getline(file, s)) {
        lines->push_back(s);
    }
}


int main() {
    try {
        auto lines = new std::vector<std::string>();
        readFile("raw.txt", lines);
        Optimizer* optmzr = new Optimizer(lines);
        optmzr->run();
        
        std::cout << optmzr->result << '\n';
    }
    catch(std::string e)
    {
        std::cout << e << '\n';
    }
}

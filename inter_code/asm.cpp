#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>

class Generator {
public:
    std::ifstream *file;
    Generator(std::ifstream *f) {
        file = f;
    }

    void go() {
        std::string line;
        bool endofline;
        while (std::getline(*file, line)) {
            endofline = false;
            std::istringstream iss(line);
            std::string token; 
            iss >> token;

            while (islabel(token)) {
                std::cout << token << "\n";
                if(!(iss >> token)) {
                    endofline = true;
                    break;
                }
            }

            if (!endofline) {
                if (token == "if") {
                    _if(iss);
                } else if (token == "iffalse") {
                    _iffalse(iss);
                } else {
                    threeAddress(token, iss);
                }
            }
        }
    }

    void _if (std::istringstream &iss) {
        try {
            std::string left, op, right, _goto, label, jmp;
            
            if (left != "true")
                iss >> op >> right;
            iss >> _goto >> label;

            if (left == "true") jmp = "JMP"; // unconditional
            else if (op == ">=") jmp = "JGE";
            else if (op == "==") jmp = "JE";
            else if (op == "<=") jmp = "JLE";
            else if (op == "!=") jmp = "JNE";
            else if (op == ">")  jmp = "JG";
            else if (op == "<")  jmp = "JL";

            std::cout << "CMP " << left << ", " << right << "\n";
            std::cout << jmp << " " << label << "\n";
        
        } catch (std::exception e) {};
    }

    void _iffalse (std::istringstream &iss) {
        try {
            std::string left, op, right, _goto, label, jmp;
            iss >> left;

            if (left != "false")
                iss >> op >> right;
            iss >> _goto >> label;

            if (left == "false") jmp = "JMP"; // unconditional
            else if (op == ">=") jmp = "JLE";
            else if (op == "==") jmp = "JNE";
            else if (op == "<=") jmp = "JGE";
            else if (op == "!=") jmp = "JE";
            else if (op == ">")  jmp = "JL";
            else if (op == "<")  jmp = "JG";

            std::cout << "CMP " << left << ", " << right << "\n";
            std::cout << jmp << " " << label << "\n";
        
        } catch (std::exception e) {};
    }

    void threeAddress(std::string left, std::istringstream &iss) 
    {
        std::string asgn, first, op, second;
        iss >> asgn >> first >> op >> second;

        std::cout << "LOAD " << first << "\n";
        if (op != "") {
            if      (op == "*") std::cout << "MPY " << second << "\n";
            else if (op == "/") std::cout << "DIV " << second << "\n";
            else if (op == "+") std::cout << "ADD " << second << "\n";
            else if (op == "-") std::cout << "SUB " << second << "\n";
        } 
        std::cout << "STORE " << left << "\n";
    }

    bool islabel(std::string s) {
        return s[s.length() - 1] == ':';
    }

};


int main() {
    try {
        std::ifstream threecode("out.txt");
        Generator * gen = new Generator(&threecode);
        gen->go();
    }
    catch(std::string e)
    {
        std::cout << e << '\n';
    }
}

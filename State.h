#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>

// classfor terminala nd non-terminal states
class State{
private:
    std::string symbol;
    std::string SymbolType; //terminal or non-terminal
    bool isTerminal; // Terminal is always a terminal
    bool isNonTerminal; // Terminal is never a non-terminal
    bool isEpsilon; // Terminal is never an epsilon
    bool isStartState; // Terminal is never a start state


public:



    State(std::string val , std::string type) : symbol(removeSpaces(val)), SymbolType(type) {
        SymbolType = type;
        if (type == "terminal") {
            isTerminal = true;
            isNonTerminal = false;
            isEpsilon = false;
            isStartState = false;
        }
        else if (type == "non-terminal") {
            isTerminal = false;
            isNonTerminal = true;
            isEpsilon = false;
            isStartState = false;
        }
        else if (type == "epsilon") {
            isTerminal = false;
            isNonTerminal = false;
            isEpsilon = true;
            isStartState = false;
        }
        else if (type == "start-state") {
            isTerminal = false;
            isNonTerminal = false;
            isEpsilon = false;
            isStartState = true;
        }

    }

    std::string getSymbol() const { return symbol; }
    std::string getType() const { return SymbolType; }
    void showSymbol() const { std::cout << symbol; }
    void showType() const { std::cout << SymbolType; }
    //bool isTerminal() { return isTerminal; }

    void setSymbol(std::string val) { symbol = removeSpaces(val); }
    void setType(std::string type) { SymbolType = type; }
    
    bool operator==(const State& other) const {
        // Compare relevant members of the State class
        // Replace 'member' with the actual member(s) to compare
        return this->symbol == other.symbol;
    }

    std::string removeSpaces(const std::string& str) {
        std::string result;
        for (char ch : str) {
            if (ch != ' ') {
                result += ch;
            }
        }
        return result;
    }
    
};

#endif // TERMINAL_H

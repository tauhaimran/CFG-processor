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



    State(std::string val , std::string type) : symbol(val) {
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

    std::string getSymbol() { return symbol; }
    void showSymbol() const { std::cout << symbol; }
};

#endif // TERMINAL_H

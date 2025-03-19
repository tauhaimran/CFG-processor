#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <iostream>
#include "State.h"
#include "ProductionRule.h"

class CFG {
private:
    std::vector<State> nonTerminals;
    std::vector<State> terminals;
    std::vector<ProductionRule> productionRules;
    State startSymbol;

public:
    CFG(const State& startSymbol) : startSymbol(startSymbol) {}

    void addNonTerminal(const State& nonTerminal) { 
        if( isInNonTerminals(nonTerminal) == false) {
            nonTerminals.push_back(nonTerminal); 
        }
     }

    void addTerminal(const State& terminal) { 
        if (isInTerminals(terminal) == false) {
            terminals.push_back(terminal); 
        }
     }

    void addProductionRule(const ProductionRule& rule) { productionRules.push_back(rule); }

    void display() const {
        std::cout << "Start Symbol: ";
        startSymbol.showSymbol();
        std::cout << std::endl << "Production Rules:" << std::endl;

        for (const auto& rule : productionRules) {
            rule.display();
        }
    }

    void showNonTerminals() const {
        std::cout << "Non-terminals: \n";
        for (const auto& nonTerminal : nonTerminals) {
            nonTerminal.showSymbol();
            std::cout << "\t(" ;
            nonTerminal.showType();
            std::cout << ") , ";
            std::cout << " \n";
        }
        std::cout << std::endl;
    }

    void showTerminals() const {
        std::cout << "Terminals: \n";
        for (const auto& terminal : terminals) {
            terminal.showSymbol();
            std::cout << "\t(" ;
            terminal.showType();
            std::cout << ") , ";
            std::cout << " \n";
        }
        std::cout << std::endl;
    }

    bool isInTerminals(const State& state) const {
        for (const auto& terminal : terminals) {
            if (terminal == state) return true;
        }
        return false;
    }

    bool isInNonTerminals(const State& state) const {
        for (const auto& nonTerminal : nonTerminals) {
            if (nonTerminal == state) return true;
        }
        return false;
    }
};

#endif // CFG_H

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

    void addNonTerminal(const State& nonTerminal) { nonTerminals.push_back(nonTerminal); }

    void addTerminal(const State& terminal) { terminals.push_back(terminal); }

    void addProductionRule(const ProductionRule& rule) { productionRules.push_back(rule); }

    void display() const {
        std::cout << "Start Symbol: ";
        startSymbol.showSymbol();
        std::cout << std::endl << "Production Rules:" << std::endl;

        for (const auto& rule : productionRules) {
            rule.display();
        }
    }
};

#endif // CFG_H

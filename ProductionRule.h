// ProductionRule.h
#ifndef PRODUCTION_RULE_H
#define PRODUCTION_RULE_H

#include <vector>
#include <string>
#include <iostream>
#include "State.h"

class ProductionRule {
private:
    State lhs; // Left-hand side (LHS): A single State
    std::vector<State> rhs; // Right-hand side (RHS): A list of States

public:
    // Constructor
    ProductionRule(const State& lhsState, const std::vector<State>& rhsStates)
        : lhs(lhsState), rhs(rhsStates) {}

    // Get LHS
    const State& getLHS() const { return lhs; }

    // Get RHS
    const std::vector<State>& getRHS() const { return rhs; }

    // Display the Production Rule
    void display() const {
        lhs.showSymbol();
        std::cout << " -> ";
        for (const auto& state : rhs) {
            state.showSymbol();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
};

#endif // PRODUCTION_RULE_H

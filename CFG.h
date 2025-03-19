#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <iostream>
#include "State.h"
#include "ProductionRule.h"

class CFG {
private:
    std::vector<State> nonTerminals;   // Stores all non-terminal states
    std::vector<State> terminals;      // Stores all terminal states
    std::vector<ProductionRule> productionRules; // Stores all production rules
    State startSymbol;                 // Stores the starting symbol of the grammar

public:
    // Constructor to initialize the CFG with a starting symbol
    CFG(const State& startSymbol) : startSymbol(startSymbol) {}

    // Adds a non-terminal state to the grammar if it doesn't already exist
    void addNonTerminal(const State& nonTerminal) { 
        if( isInNonTerminals(nonTerminal) == false) {
            nonTerminals.push_back(nonTerminal); 
        }
     }

    // Adds a terminal state to the grammar if it doesn't already exist
    void addTerminal(const State& terminal) { 
        if (isInTerminals(terminal) == false) {
            terminals.push_back(terminal); 
        }
     }

    // Adds a production rule to the grammar
    void addProductionRule(const ProductionRule& rule) { productionRules.push_back(rule); }

    // Displays the start symbol and all production rules in the grammar
    void display() const {
        std::cout << "Start Symbol: ";
        startSymbol.showSymbol();
        std::cout << std::endl << "Production Rules:" << std::endl;

        for (const auto& rule : productionRules) {
            rule.display();
        }
    }

    // Displays all non-terminal states in the grammar
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

    // Displays all terminal states in the grammar
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

    // Checks if a given state exists in the terminals list
    bool isInTerminals(const State& state) const {
        for (const auto& terminal : terminals) {
            if (terminal == state) return true;
        }
        return false;
    }

    // Checks if a given state exists in the non-terminals list
    bool isInNonTerminals(const State& state) const {
        for (const auto& nonTerminal : nonTerminals) {
            if (nonTerminal == state) return true;
        }
        return false;
    }

    // Step # 1
    //FUNCTION  for left Factoring
    void leftFacortring(){

    //FOR each NonTerminal in nonTerminals
    for (const auto& nonTerminal : nonTerminals) {
        std::vector<ProductionRule> RULES_FOR_NONTERMINAL;

        //Collect all ProductionRules associated with NonTerminal
        for (const auto& rule : productionRules) {
            if (rule.getLHS() == nonTerminal) {
                RULES_FOR_NONTERMINAL.push_back(rule);
            }
        }

        // Compare each pair of production rules for common prefixes
        //FOR each rule_j in RULES_FOR_NONTERMINAL
        for (int j = 0; j < RULES_FOR_NONTERMINAL.size(); j++) {
            ProductionRule rule_j = RULES_FOR_NONTERMINAL[j];
            //FOR each rule_k after rule_j in RULES_FOR_NONTERMINAL
            for (int k = j + 1; k < RULES_FOR_NONTERMINAL.size(); k++) {
                ProductionRule rule_k = RULES_FOR_NONTERMINAL[k];
                std::vector<State> prefix, remainingJ, remainingK;//PREFIX = []
                int INDEX = 0;//INDEX = 0

                // Compare symbols until mismatch
                //WHILE INDEX < min(size of rule_j, size of rule_k) AND 
                while(INDEX < std::min(rule_j.getRHS().size(), rule_k.getRHS().size()) &&
                      
                rule_j.getRHS()[INDEX] == rule_k.getRHS()[INDEX]) {
                      
                        if(rule_j.getRHS()[INDEX] == rule_k.getRHS()[INDEX]) //if prefixes match..
                      { //ADD rule_j[INDEX] to PREFIX
                          prefix.push_back(rule_j.getRHS()[INDEX]);
                      }
                      INDEX++; //INCREMENT INDEX
                    
                    
                    prefix.push_back(rule_j.getRHS()[INDEX]);
                }

                //IF PREFIX is NOT empty
                if(!prefix.empty()) {
                    // Create a new NonTerminal for the factored part
                    State newNonTerminal = nonTerminal;
                    //NEW_NONTERMINAL = NonTerminal + "'"
                    newNonTerminal.setSymbol(newNonTerminal.getSymbol() + "'");
                    //ADD NEW_NONTERMINAL to nonTerminals
                    addNonTerminal(newNonTerminal);

                    // Prepare remaining parts of rule_j and rule_k
                     // Prepare remaining parts for both rules
                     remainingJ.assign(rule_j.getRHS().begin() + INDEX, rule_j.getRHS().end()); //REMAINING_J = remaining symbols of rule_j after INDEX
                     remainingK.assign(rule_k.getRHS().begin() + INDEX, rule_k.getRHS().end()); //REMAINING_K = remaining symbols of rule_k after INDEX

                    //IF REMAINING_J is empty, ADD ε (epsilon) to REMAINING_J
                    if(remainingJ.empty()) {
                        State epsilon( "epsilon" , "terminal");
                        remainingJ.push_back(epsilon);
                    }
                    //IF REMAINING_K is empty, ADD ε (epsilon) to REMAINING_K
                    if(remainingK.empty()) {
                        State epsilon( "epsilon" , "terminal");
                        remainingK.push_back(epsilon);
                    }

                    // Add the new production rules to grammar
                    productionRules.push_back(ProductionRule(nonTerminal, prefix)); //ADD ProductionRule(NonTerminal -> PREFIX + NEW_NONTERMINAL) to productionRules
                    productionRules.push_back(ProductionRule(newNonTerminal, remainingJ)); //ADD ProductionRule(NEW_NONTERMINAL -> REMAINING_J) to productionRules
                    productionRules.push_back(ProductionRule(newNonTerminal, remainingK)); //ADD ProductionRule(NEW_NONTERMINAL -> REMAINING_K) to productionRules

                    // Remove the original conflicting rules from grammar
                    //REMOVE rule_j and rule_k from productionRules
                    productionRules.erase(productionRules.begin() + j); //REMOVE rule_j from productionRules
                    productionRules.erase(productionRules.begin() + k); //REMOVE rule_k from productionRules
                    //REMOVE rule_j and rule_k from RULES_FOR_NONTERMINAL
                    RULES_FOR_NONTERMINAL.erase(RULES_FOR_NONTERMINAL.begin() + j); //REMOVE rule_j from RULES_FOR_NONTERMINAL
                    RULES_FOR_NONTERMINAL.erase(RULES_FOR_NONTERMINAL.begin() + k); //REMOVE rule_k from RULES_FOR_NONTERMINAL

                    // Restart comparison for updated list
                    k = j; //k = j .. still tryna ficure out how this part works...
                }//ENDIF
            }//ENDFOR
         } //ENDFOR
    } //ENDFOR
}//END FUNCTION

};

#endif // CFG_H

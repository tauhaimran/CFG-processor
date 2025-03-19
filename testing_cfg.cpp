#include <iostream>
#include "CFG.h"
#include "CFGReader.h"

int main() {
    // Define some states
    State S("S", "start-state");
    State A("A", "non-terminal");
    State B("B", "non-terminal");
    State a("a", "terminal");
    State b("b", "terminal");

    // Create production rules
    ProductionRule rule1(S, { A, B });
    ProductionRule rule2(A, { a });
    ProductionRule rule3(B, { b });

    // Create the CFG
    CFG cfg(S);

    // Add terminals, non-terminals, and rules
    cfg.addNonTerminal(A);
    cfg.addNonTerminal(B);
    cfg.addTerminal(a);
    cfg.addTerminal(b);

    cfg.addProductionRule(rule1);
    cfg.addProductionRule(rule2);
    cfg.addProductionRule(rule3);

    // Display the CFG
    //cfg.display();

    std::cout << "---now--reading--file---" << std::endl;

    State startSymbol("S", "non-terminal");
    CFG cfg2(startSymbol);
    

    if (CFGReader::readFromFile("input.txt", cfg2)) {
        std::cout << "CFG successfully loaded!" << std::endl;
        cfg2.display();
        std::cout << "-------------------------" << std::endl;
        
        std::cout << "Step#1 -- left factoring.." << std::endl;
        cfg2.leftFactoring();
        //cfg2.showNonTerminals();
        // cfg2.showTerminals();
        cfg2.display();
        //std::cout << "Step#2 -- left recursion.." << std::endl;

    } else {
        std::cerr << "Failed to load CFG from file." << std::endl;
    }


    return 0;
}

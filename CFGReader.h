#ifndef CFG_READER_H
#define CFG_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include "CFG.h"
#include "ProductionRule.h"
#include "State.h"

class CFGReader {
public:
    static bool readFromFile(const std::string& filename, CFG& cfg) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            if (line.empty()) continue;

            size_t arrowPos = line.find("->");
            if (arrowPos == std::string::npos) continue;

            std::string lhsSymbol = line.substr(0, arrowPos);
            std::string rhsSymbols = line.substr(arrowPos + 2);

            State lhs(lhsSymbol, "non-terminal");
            if (lhsSymbol == "S") cfg.addNonTerminal(lhs); // Add start symbol as non-terminal

            std::stringstream ss(rhsSymbols);
            std::string production;
            while (std::getline(ss, production, '|')) {
                std::stringstream rhsStream(production);
                std::string symbol;
                std::vector<State> rhsStates;

                while (rhsStream >> symbol) {
                    if (isNonTerminal(symbol)) { // If it matches NonTerminal pattern
                        State nonTerminal(symbol, "non-terminal");
                        rhsStates.push_back(nonTerminal);
                        cfg.addNonTerminal(nonTerminal);
                    }
                    else { // Anything else is a Terminal
                        State terminal(symbol, "terminal");
                        rhsStates.push_back(terminal);
                        cfg.addTerminal(terminal);
                    }
                }
                cfg.addProductionRule(ProductionRule(lhs, rhsStates));
            }
        }
        file.close();
        return true;
    }

private:
    static bool isNonTerminal(const std::string& symbol) {
        if (symbol == "S") return true; // Special case for Start Symbol
        if (symbol.size() == 1 && std::isupper(symbol[0])) return true; // A to Z

        // Check for A1, A2, ... Zn pattern
        if (std::isupper(symbol[0])) {
            for (size_t i = 1; i < symbol.size(); ++i) {
                if (!std::isdigit(symbol[i])) return false;
            }
            return true;
        }
        return false;
    }
};

#endif // CFG_READER_H

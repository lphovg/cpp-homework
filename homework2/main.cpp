#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>
#include "Errors.hpp"
#include "ServiceCenter.hpp"
#include "Fleet.hpp"
#include "Inventory.hpp"
#include "Transport.hpp"
#include "Things.hpp"
#include "Commands.hpp"

int main() {
    Fleet fleet;
    ServiceCenter service;
    std::string input;
    while (std::getline(std::cin, input)) {
        try {
            std::istringstream args(input);
            std::string cmd;
            if (args.peek() == EOF) {
                continue;
            }
            if (!(args >> cmd)) {
                throw ParseError();
            }
            if (CmdCompiler(cmd, args, fleet, service)) {
                continue;
            }
            if (cmd == "quit") {
                break;
            }
            throw ParseError();
        } catch (const FleetError& error) {
            std::cout << "Error: " << error.what() << "\n";
        }
    }
    return 0;
}
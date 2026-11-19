#pragma once
#include "Journal.hpp"
#include "Transport.hpp"
#include "Things.hpp"
#include "Inventory.hpp"
#include "Errors.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <memory>

class ServiceCenter {
private:
    RegJournal<const Transport*, 100> Vehicles;
    RegJournal<const Thing*, 100> Items;
    RegJournal<std::string, 100> Notes;
public:
    void check(const InventoryItem& item) {
        std::string name = item.getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.find("broken") != std::string::npos) {
            Notes.add("broken " + name);
            throw InspectionError();
        }
        if (dynamic_cast<const Transport*>(&item)) {
            Vehicles.add(dynamic_cast<const Transport*>(&item), true);
        } else {
            Items.add(dynamic_cast<const Thing*>(&item), true);
        }
    }
    void cleanTransport() {
        Vehicles.clean();
    }
    void cleanThings() {
        Items.clean();
    }
    void cleanBroken() {
        Notes.clean();
    }
};
#pragma once
#include <iostream>
#include <string>

class InventoryItem {
public:
    virtual std::string InventoryId() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string describe() const = 0;
    virtual std::string type() const = 0;
    virtual ~InventoryItem() = default;
    inline friend std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
        out << item.describe();
        return out;
    }
    inline friend bool operator<(const InventoryItem& item1, const InventoryItem& item2) {
        return item1.InventoryId() < item2.InventoryId();
    }
};

class EnergyConsumer {
public:
    virtual double dailyEnergy() const = 0;
    virtual ~EnergyConsumer() = default;
};
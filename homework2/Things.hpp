#pragma once
#include "Inventory.hpp"
#include "Errors.hpp"
#include <string>

class Thing : public InventoryItem {
protected:
    std::string id;
    std::string name;
public:
    Thing(const std::string& id_, const std::string& name_) {
        if (id_ == "" || name_ == "") {
            throw ItemCreatingError();
        }
        id = id_;
        name = name_;
    }
    std::string type() const override {
        return "Thing";
    }
};

class Helmet : public Thing {
public:
    Helmet(const std::string& id_, const std::string& name_) : Thing(id_, name_) {}
    std::string InventoryId() const override {
        return id;
    }
    std::string getName() const override {
        return name;
    }
    std::string describe() const override {
        return id + " " + name;
    }
};

class DockStation : public Thing, public EnergyConsumer {
private:
    double energyForDay;
public:
    DockStation(const std::string& id_, const std::string& name_, const double& energizer) : Thing(id_, name_) {
        if (energizer < 0) {
            throw EnergyError();
        }
        energyForDay = energizer;
    }
    std::string InventoryId() const override {
        return id;
    }
    std::string getName() const override {
        return name;
    }
    std::string describe() const override {
        return id + " " + name;
    }
    double dailyEnergy() const override {
        return energyForDay;
    }
};
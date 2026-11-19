#pragma once
#include "Inventory.hpp"
#include "Errors.hpp"
#include <algorithm>
#include <string>

class Transport : public InventoryItem {
protected:
    std::string id;
    std::string name;
    int beginnerScore;
public:
    Transport(const std::string& id_, const std::string& name_, int score) {
        if (score < 1 || score > 10) {
            throw BeginnerScoreError();
        }
        if (id_ == "" || name_ == "") {
            throw ItemCreatingError();
        }
        id = id_;
        name = name_;
        beginnerScore = score;
    }
    std::string type() const override {
        return "Transport";
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
    virtual int getBegScore() const = 0;
};

class Bike : public Transport { 
public:
    Bike(const std::string& id_, const std::string& name_, int score) : Transport(id_, name_, score) {}
    int getBegScore() const override {
        return beginnerScore;
    }
};

class ElectricScooter : public Transport, public EnergyConsumer {
private:
    double energyForDay;
public:
    ElectricScooter(const std::string& id_, const std::string& name_, int score, double energizer) : Transport(id_, name_, score) {
        if (energizer < 0) {
            throw EnergyError();
        }
        energyForDay = energizer;
    }
    int getBegScore() const override {
        return beginnerScore;
    }
    double dailyEnergy() const override {
        return energyForDay;
    }
};

class EBike : public Transport, public EnergyConsumer {
private:
    double energyForDay;
public:
    EBike(const std::string& id_, const std::string& name_, int score, double energizer) : Transport(id_, name_, score) {
        if (energizer < 0) {
            throw EnergyError();
        }
        energyForDay = energizer;
    }
    int getBegScore() const override {
        return beginnerScore;
    }
    double dailyEnergy() const override {
        return energyForDay;
    }
};

class Deltaplan : public Transport {
private:
    double howhighcanfly;
    int quality;
public:
    Deltaplan(const std::string& id_, const std::string& name_, int score, double longitue, int qual) : Transport(id_, name_, std::max(score - 3, 1)) {
        if (longitue < 0) {
            throw DistanceError();
        }
        if (qual < 1 || qual > 10) {
            throw QualityError();
        }
        howhighcanfly = longitue;
        quality = qual;
    }
    int getBegScore() const override {
        return beginnerScore;
    }
    double getHeight() const {
        return howhighcanfly;
    }
    int getQuality() const {
        return quality;
    }
};
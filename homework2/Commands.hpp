#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Transport.hpp"
#include "Things.hpp"
#include "Fleet.hpp"
#include "Errors.hpp"
#include "ServiceCenter.hpp"

struct Table {
    const std::string name;
    void (*func)(std::istringstream& input, Fleet& fleet, ServiceCenter& service);
};

void AddBike(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    int score;
    if (!(input >> id >> name >> score) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<Bike>(id, name, score);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void AddDeltaplan(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    int score;
    double howhighcanfly;
    int quality;
    if (!(input >> id >> name >> score >> howhighcanfly >> quality) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<Deltaplan>(id, name, score, howhighcanfly, quality);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void AddScooter(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    int score;
    double energy;
    if (!(input >> id >> name >> score >> energy) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<ElectricScooter>(id, name, score, energy);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void AddEBike(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    int score;
    double energy;
    if (!(input >> id >> name >> score >> energy) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<EBike>(id, name, score, energy);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void AddHelmet(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    if (!(input >> id >> name) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<Helmet>(id, name);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void AddDock(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    std::string name;
    double energy;
    if (!(input >> id >> name >> energy) || input.peek() != EOF) {
        throw InputError();
    }
    std::unique_ptr<InventoryItem> tr = std::make_unique<DockStation>(id, name, energy);
    service.check(*tr);
    fleet.add(std::move(tr));
}

void HMEnergy(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    std::cout << std::fixed << std::setprecision(1) << fleet.energy() << "\n";
}

void Novice(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    for (auto& i : fleet.novice()) {
        std::cout << i << "\n";
    }
}

void List(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    for (auto& i : fleet.list()) {
        std::cout << *i << "\n";
    }
}

void Focus(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    if (!(input >> id) || input.peek() != EOF) {
        throw InputError();
    }
    fleet.focus(id);
}

void ShowFocus(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    std::cout << fleet.show_focus() << "\n";
}

void Remove(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    std::string id;
    if (!(input >> id) || input.peek() != EOF) {
        throw InputError();
    }
    fleet.remove(id);
}

void cleanVech(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    service.cleanTransport();
}

void cleanTh(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    service.cleanThings();
}

void cleanBrok(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    service.cleanBroken();
}

void mediumNovice(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    std::cout << std::fixed << std::setprecision(1) << fleet.mediumNoviceScore() << "\n";
}

void maxheight(std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (input.peek() != EOF) {
        throw InputError();
    }
    std::cout << std::fixed << std::setprecision(1) << fleet.maxhigh() << "\n";
}

Table Commands[] = {
    {"add bike", AddBike},
    {"add scooter", AddScooter},
    {"add helmet", AddHelmet},
    {"add dock", AddDock},
    {"energy", HMEnergy},
    {"novice", Novice},
    {"list", List},
    {"remove", Remove},
    {"focus", Focus},
    {"show_focus", ShowFocus},
    {"add deltaplan", AddDeltaplan},
    {"clean vehicles", cleanVech},
    {"clean things", cleanTh},
    {"clean notes", cleanBrok},
    {"medium_novice_score", mediumNovice},
    {"max_height", maxheight},
    {"add ebike", AddEBike}
};

bool CmdCompiler(std::string& cmd, std::istringstream& input, Fleet& fleet, ServiceCenter& service) {
    if (cmd == "add" || cmd == "clean") {
        std::string w;
        if (!(input >> w)) {
            throw ParseError();
        }
        cmd += " " + w;
    }
    for (auto& cmds : Commands) {
        if (cmds.name == cmd) {
            cmds.func(input, fleet, service);
            return true;
        }
    }
    return false;
}
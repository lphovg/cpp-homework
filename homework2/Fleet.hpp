#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include "Inventory.hpp"
#include "Transport.hpp"
#include "Errors.hpp"

class Fleet {
private:
    std::vector<std::shared_ptr<InventoryItem>> items;
    std::weak_ptr<InventoryItem> focus_ptr;
public:
    void add(std::unique_ptr<InventoryItem> item) {
        items.push_back(std::move(item));
    }
    void focus(const std::string& id) {
        for (const auto& item : items) {
            if (item->InventoryId() == id) {
                focus_ptr = item;
                return;
            }
        }
        throw UnexpectedIdError();
    }
    std::string show_focus() {
        if (focus_ptr.expired()) {
            return "expired";
        }
        return focus_ptr.lock()->describe();
    }
    void remove(const std::string& id) {
        for (const auto& item : items) {
            if (item->InventoryId() == id) {
                std::erase(items, item);
                return;
            }
        }
        throw UnexpectedIdError();
    }
    double energy() const {
        double ans = 0;
        for (const auto& item : items) {
            if (dynamic_cast<EnergyConsumer*>(item.get())) {
                ans += dynamic_cast<EnergyConsumer*>(item.get())->dailyEnergy(); 
            }
        }
        return ans;
    }
    std::vector<std::string> novice() const {
        std::vector<std::string> ans;
        for (const auto& item : items) {
            if (dynamic_cast<Transport*>(item.get())) {
                if (dynamic_cast<Transport*>(item.get())->getBegScore() >= 6) {
                    ans.push_back(item->describe());
                }
            }
        }
        if (ans.size() == 0) {
            throw NoError();
        }
        return ans;
    }
    std::vector<std::shared_ptr<InventoryItem>> list() const {
        std::vector<std::shared_ptr<InventoryItem>> ans = items;
        std::sort(ans.begin(), ans.end(), [](const auto& a, const auto&b){return *a < *b;});
        if (ans.size() == 0) {
            throw NoError();
        }
        return ans;
    }
    double mediumNoviceScore() const {
        double ans = 0;
        int cnt = 0;
        for (const auto& item : items) {
            if (dynamic_cast<Transport*>(item.get())) {
                ans += dynamic_cast<Transport*>(item.get())->getBegScore();
                cnt += 1;
            }
        }
        if (cnt == 0) {
            throw NoError();
        }
        return ans / cnt;
    }
    double maxhigh() const {
        double ans = 0;
        for (const auto& item : items) {
            if(dynamic_cast<Deltaplan*>(item.get())) {
                ans = std::max(ans, dynamic_cast<Deltaplan*>(item.get())->getHeight());
            }
        }
        return ans;
    }
};
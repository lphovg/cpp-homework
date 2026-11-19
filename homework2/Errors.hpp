#pragma once
#include <exception>

class FleetError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Fleet Error";
    }
};

class UnexpectedIdError : public FleetError {
public:
    const char* what() const noexcept override {
        return "Item not found in the fleet";
    }
};

class InspectionError : public FleetError {
public:
    const char* what() const noexcept override {
        return "Item is broken";
    }    
};

class ItemCreatingError : public FleetError {
public:
    const char* what() const noexcept override {
        return "Incorrect Id or name";
    }
};

class TransportCreatingError : public ItemCreatingError {
public:
    const char* what() const noexcept override {
        return "Incorrect transport's parameters";
    }
};

class BeginnerScoreError : public TransportCreatingError {
public:
    const char* what() const noexcept override {
        return "Beginner score is not in the interval [1;10]";
    }
};

class EnergyError : public ItemCreatingError {
public:
    const char* what() const noexcept override {
        return "Energy can be only positive";
    }
};

class DistanceError : public ItemCreatingError {
public:
    const char* what() const noexcept override {
        return "The distance should be positive";
    }
};

class QualityError : public ItemCreatingError {
public:
    const char* what() const noexcept override {
        return "The quality in [1; 10] and integer";
    }
};

class ParseError : public FleetError {
public:
    const char* what() const noexcept override {
        return "Incorrect command";
    }
};

class NoError : public FleetError {
public:
    const char* what() const noexcept override {
        return "there are no such items yet";
    }
};

class InputError : public ParseError {
public:
    const char* what() const noexcept override {
        return "Incorrect values";
    }
};

class JournalOverflowError : public FleetError {
public:
    const char* what() const noexcept override {
        return "Two many notes, clean your journal";
    }
};
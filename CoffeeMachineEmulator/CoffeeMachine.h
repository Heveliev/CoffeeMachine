#pragma once
#include <vector>
#include <iostream>

#include "CoffeeMachineState.h"
#include "Reservoir.h"
#include "DrinkProgram.h"

class CoffeeMachine
{
public:
    CoffeeMachine() : m_currentState(new Sleep), m_waterReservoir(new WaterReservoir),
        m_milkReservoir(new MilkReservoir), m_coffeeContainer(new CoffeeGrainsContainer) {}

    ~CoffeeMachine() 
    {
        delete m_SelectedDrink;
        delete m_waterReservoir;
        delete m_milkReservoir;
        delete m_coffeeContainer;
        delete m_currentState;

        for (auto recipe : m_recipes)
        {
            delete recipe;
        }
        m_recipes.clear();
    }

    bool IsBooted() const { return !m_powerOffRequest; }

    void initDefaultDrinks();
    void addDrinkReceipt(DrinkProgram* program) { m_recipes.push_back(program); }

    void showMenu()
    {
        if (m_currentState != nullptr) { m_currentState->showMenu(*this); }
    };
    void receiveInput() 
    {
        if (m_currentState != nullptr) { m_currentState->receiveInput(*this); }
    };
    void update()
    {
        if (m_currentState != nullptr) { m_currentState->update(*this); }
    };

    void setState(CoffeeMachineState* state) {
        delete m_currentState;
        m_currentState = state;
    }



    WaterReservoir* getWaterReservoir() const { return m_waterReservoir; }
    MilkReservoir* getMilkReservoir() const { return m_milkReservoir; }
    CoffeeGrainsContainer* getCoffeeContainer() const { return m_coffeeContainer; }

    int getCurrentChoice() const { return m_currentChoice; }
    void setCurrentChoice(const int& input) { m_currentChoice = input; }
    bool getPowerOffRequest() const { return m_powerOffRequest; }
    void setPowerOffRequest(const bool& powerOff) { m_powerOffRequest = powerOff; }

    DrinkProgram* getSelectedDrink() const { return m_SelectedDrink; }

    void showListOfDrinks();
    void selectDrink();


private:
    CoffeeMachineState* m_currentState = nullptr;

    std::vector<DrinkProgram*> m_recipes;
    DrinkProgram* m_SelectedDrink = nullptr;

    WaterReservoir* m_waterReservoir = nullptr;
    MilkReservoir* m_milkReservoir = nullptr;
    CoffeeGrainsContainer* m_coffeeContainer = nullptr;
    
    int m_currentChoice = -1;
    bool m_powerOffRequest = false;
};

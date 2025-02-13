#pragma once
#include <vector>
#include <iostream>

#include "WaterReservoir.h"
#include "MilkReservoir.h"
#include "DrinkProgram.h"

class CoffeeGrainsContainer
{
    //not used yet
};


enum class CoffeeMachineState
{
    Sleep,
    PowerOffRequest,
    
    MainMenu,
    
    WaterReservoir,
    MilkReservoir,
    CoffeeGrain,    //Not implemented yet

    DrinkSelection,
    DrinkPreparation,

    LowWaterError,
    LowMilkError,

    SpoiledMilkError,
};


class CoffeeMachine
{
public:
    ~CoffeeMachine() 
    {
        m_recipes.clear();
        //TODO HW: clear recipes memory from vector}
    }

    bool IsBooted() const { return !m_powerOffRequest; }

    void initDefaultDrinks();
    void addDrinkReceipt(DrinkProgram* program) { m_recipes.push_back(program); }

    void showMenu();
    void receiveInput();
    void update();

private:
    void powerOn();
    void powerOff();

    void selectNewMenuFromMain();
    
    void showListOfDrinks();
    void prepareDrink();
    void selectDrink();

    void showLowWaterError();
    void showLowMilkError();
    void showSpoiledMilkError();

private:
    std::vector<DrinkProgram*> m_recipes;
    DrinkProgram* m_SelectedDrink = nullptr;

    WaterReservoir m_waterReservoir;
    MilkReservoir m_milkReservoir;
    
    int m_currentChoice = -1;
    CoffeeMachineState m_currentState = CoffeeMachineState::Sleep;

    bool m_powerOffRequest = false;

private:
    friend class DrinkProgram;
};

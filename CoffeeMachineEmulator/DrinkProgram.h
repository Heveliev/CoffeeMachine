#pragma once
#include <string>

enum class DrinkType
{
    Espresso,
    Cappuccino
};

enum class DrinkProgramStatus
{
    Success = 0,
    LowWater,
    CleanNeeded,  //Not implemented
    LowMilk,
    SpoiledMilk,
    //TODO HW, add new status if needed

    Count
};


class DrinkProgram
{
public:
    DrinkProgram(DrinkType type, class CoffeeMachine& context); //forward declaration of CoffeeMachine class, to not include header here, only in .cpp

    void showInfo();
    void printPreparation(std::string drinkName);
    DrinkProgramStatus prepare();

private:
    DrinkType m_drinkType;

    const float EsspressoVolume = 0.05f;
    const float CappuccinoMilkVolume = 0.2f;

    class CoffeeMachine& m_context; //Aggregation, Drink program doesn't own CoffeeMachine
};

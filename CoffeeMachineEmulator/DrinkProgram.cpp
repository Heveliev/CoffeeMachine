#include "DrinkProgram.h"
#include "CoffeeMachine.h"
#include <chrono>
#include <thread>
#include <string>

DrinkProgram::DrinkProgram(DrinkType type, CoffeeMachine& context) : 
    m_drinkType(type), 
    m_context(context) {}

void DrinkProgram::showInfo()
{
    switch (m_drinkType)
    {
    case DrinkType::Espresso:
        std::cout << "Espresso!";
        break;
    case DrinkType::Cappuccino:
        std::cout << "Cappuccino!";
        break;
    default:
        break;
    }
}

void DrinkProgram::printPreparation(std::string drinkName)
{
    std::cout << "\n\nGrrr ";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "\nPreparing... " << drinkName << "... ";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = 5; i > 3; i--)
    {
        std::cout << i << ".";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "..Hanging... ";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}


DrinkProgramStatus DrinkProgram::prepare()
{
    switch (m_drinkType)
    {
    case DrinkType::Espresso:
    {
        if (m_context.m_waterReservoir.getVolume() < EsspressoVolume)
        {
            return DrinkProgramStatus::LowWater;
        }

        m_context.m_waterReservoir.useWater(EsspressoVolume);

        printPreparation("Esspresso");

        std::cout << "DONE!\n\n";

        return DrinkProgramStatus::Success;
    }
    case DrinkType::Cappuccino:

        if (m_context.m_waterReservoir.getVolume() < EsspressoVolume)
        {
            return DrinkProgramStatus::LowWater;
        }

        if (m_context.m_milkReservoir.getMilkState() != MilkState::Fresh)
        {
            return DrinkProgramStatus::SpoiledMilk;
        }

        if (m_context.m_milkReservoir.getVolume() < CappuccinoMilkVolume)
        {
            return DrinkProgramStatus::LowMilk;
        }


        m_context.m_waterReservoir.useWater(EsspressoVolume);
        m_context.m_milkReservoir.getMilk(CappuccinoMilkVolume);

        printPreparation("Milk");
        printPreparation("Esspresso");
        printPreparation("Cappuccino");

        std::cout << "DONE!\n\n";

        return DrinkProgramStatus::Success;

        //TODO HW: Implement Cappuccino logic
        //Check Water, Milk... Return appropriate error if smth goes wrong

        //Note: Some coffeeMachineі don't check milk strictly, that is they try
        //to prepare the drink even if there's not enough milk present, up to you to decide exact logic 

        //print "Preparing msgs with proper steps ideally"

        break;
    default:
        break;
    };

    return DrinkProgramStatus::Success;
}

#include "DrinkProgram.h"
#include "CoffeeMachine.h"
#include "./utils/utils.h"

#include <chrono>
#include <thread>


// DrinkProgram class
unsigned short DrinkProgram::m_useAmount = 0;
DrinkProgram::DrinkProgram(std::string drinkName, CoffeeMachine& context) :
    m_name(drinkName),
    m_context(context) {}


DrinkProgram::DrinkProgram(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
    m_name(drinkName),
    m_temperature(temperature),
    m_context(context) {}

void DrinkProgram::finishPreparation()
{
    std::cout << "DONE!\n\n";
    status = DrinkProgramStatus::Success;
    m_useAmount++;
}

void DrinkProgram::checkUses()
{
    if (m_useAmount > m_useAmountMax) { status = DrinkProgramStatus::CleanNeeded; }
}

void DrinkProgram::showInfo()
{
    std::cout << m_name;
}

// Coffe class
unsigned short Coffee::m_strength = 3;

void Coffee::checkReservoirs()
{
    if (m_context.getWaterReservoir()->getVolume() < EsspressoWaterVolume)
    {
        status = DrinkProgramStatus::LowWater;
        return;
    }
    else if (m_context.getCoffeeContainer()->getVolume() < m_strength * m_coffeeDose)
    {
        status = DrinkProgramStatus::LowCoffeeGrains;
    }
    else 
    {
        status = DrinkProgramStatus::Success;
    }

    
}

void Coffee::setStrength(unsigned short strength)
{
    m_strength = strength;
}

void Coffee::grindGrains()
{
    std::cout << "\n\nGr";
    for (int i = 0; i < 7; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "r";
    }
}


// Espresso class
DrinkProgramStatus Espresso::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;

    m_context.getCoffeeContainer()->useVolume(static_cast<float>(m_strength * m_coffeeDose));
    m_context.getWaterReservoir()->useVolume(EsspressoWaterVolume);

    grindGrains();
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}

//Cappuccino class
void Cappuccino::checkReservoirs()
{
    Coffee::checkReservoirs();
    if (status != DrinkProgramStatus::Success) return;

    if (m_context.getMilkReservoir()->getMilkState() != MilkState::Fresh)
    {
        status = DrinkProgramStatus::SpoiledMilk;
    }
    else if (m_context.getMilkReservoir()->getVolume() < MilkVolume)
    {
        status = DrinkProgramStatus::LowMilk;
    }
    else 
    {
        status = DrinkProgramStatus::Success;
    }
}

DrinkProgramStatus Cappuccino::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;

    m_context.getCoffeeContainer()->useVolume(static_cast<float>(m_strength * m_coffeeDose));
    m_context.getWaterReservoir()->useVolume(EsspressoWaterVolume);
    m_context.getMilkReservoir()->useVolume(MilkVolume);

    grindGrains();

    printPreparation("Milk");
    printPreparation("Esspresso");
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}

//Latte class
void Latte::checkReservoirs()
{
    Coffee::checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return;

    if (m_context.getMilkReservoir()->getMilkState() != MilkState::Fresh)
    {
        status = DrinkProgramStatus::SpoiledMilk;
    }
    else if (m_context.getMilkReservoir()->getVolume() < MilkVolume)
    {
        status = DrinkProgramStatus::LowMilk;
    }
    else
    {
        status = DrinkProgramStatus::Success;
    }
}

DrinkProgramStatus Latte::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;

    m_context.getCoffeeContainer()->useVolume(static_cast<float>(m_strength * m_coffeeDose));
    m_context.getWaterReservoir()->useVolume(EsspressoWaterVolume);
    m_context.getMilkReservoir()->useVolume(MilkVolume);

    grindGrains();

    printPreparation("Milk");
    printPreparation("Esspresso");
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}

// Tea class
void Tea::checkReservoirs()
{
    if (m_context.getWaterReservoir()->getVolume() < m_waterAmount)
    {
        status = DrinkProgramStatus::LowWater;
        return;
    }
    else
    {
        status = DrinkProgramStatus::Success;
    }
}

void Tea::prepareWater()
{
    std::cout << "\n\nHeating water to a temperature of " << m_temperature << " degrees.\n" << std::endl;
}

// BlackTea class
DrinkProgramStatus BlackTea::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;
    m_context.getWaterReservoir()->useVolume(m_waterAmount);

    prepareWater();
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}

//GreenTea class
DrinkProgramStatus GreenTea::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;
    m_context.getWaterReservoir()->useVolume(m_waterAmount);

    prepareWater();
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}

//MatchaTea class
void MatchaTea::checkReservoirs()
{
    Tea::checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return;

    if (m_context.getMilkReservoir()->getMilkState() != MilkState::Fresh)
    {
        status = DrinkProgramStatus::SpoiledMilk;
    }
    else if (m_context.getMilkReservoir()->getVolume() < MilkVolume)
    {
        status = DrinkProgramStatus::LowMilk;
    }
    else
    {
        status = DrinkProgramStatus::Success;
    }
}


DrinkProgramStatus MatchaTea::prepare()
{
    checkReservoirs();
    DrinkProgram::checkUses();
    if (status != DrinkProgramStatus::Success) return status;

    m_context.getWaterReservoir()->useVolume(m_waterAmount);
    m_context.getMilkReservoir()->useVolume(MilkVolume);
    prepareWater();

    printPreparation("Milk");
    printPreparation(m_name);

    DrinkProgram::finishPreparation();
    return status;
}
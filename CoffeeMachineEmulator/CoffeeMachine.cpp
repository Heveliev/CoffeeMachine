#include "CoffeeMachine.h"

void CoffeeMachine::initDefaultDrinks()
{
    m_recipes.push_back(new DrinkProgram(DrinkType::Espresso, *this));
    m_recipes.push_back(new DrinkProgram(DrinkType::Cappuccino, *this));
}

void CoffeeMachine::showMenu()
{
    switch (m_currentState)
    {
    case CoffeeMachineState::Sleep:
        std::cout << "1. POWER ON\n";
        break;
    case CoffeeMachineState::MainMenu:
    {
        std::cout << "\n1. Prepare Drink\n";
        std::cout << "2. Access Water Reservoir\n";
        std::cout << "3. Access Milk Reservoir\n";
        std::cout << "4. Access Coffe Grain Container\n";
        std::cout << "5. Power off\n";
        break;
    }
    case CoffeeMachineState::DrinkSelection:
    {
        showListOfDrinks();
        break;
    }
    case CoffeeMachineState::WaterReservoir:
        m_waterReservoir.showOperations();
        break;
    case CoffeeMachineState::MilkReservoir:
        m_milkReservoir.showOperations();
        break;
    default:
        break;
    }

}

void CoffeeMachine::receiveInput()
{
    switch (m_currentState)
    {
    case CoffeeMachineState::Sleep:
    case CoffeeMachineState::MainMenu:
    case CoffeeMachineState::DrinkSelection:
    {
        std::cout << "Choice: ";
        std::cin >> m_currentChoice;    //Used in update method
        break;
    }
    case CoffeeMachineState::WaterReservoir:
        m_waterReservoir.receiveInput();    //switching to reservoir input handler
        break;
    case CoffeeMachineState::MilkReservoir:
        m_milkReservoir.receiveInput();
        break;
    default:
        break;
    }
}

void CoffeeMachine::update()
{
    switch (m_currentState)
    {
    case CoffeeMachineState::Sleep:
    {
        powerOn();
        break;
    }
    case CoffeeMachineState::MainMenu:
        //Moving to sub-menu animation
        selectNewMenuFromMain();
        break;
    case CoffeeMachineState::DrinkSelection:
        //Moving to drinks sub-menu cool animation
        selectDrink();
        break;
    case CoffeeMachineState::DrinkPreparation:
        prepareDrink();
        break;
    case CoffeeMachineState::WaterReservoir:
        m_waterReservoir.update();
        m_currentState = CoffeeMachineState::MainMenu;
        break;
    case CoffeeMachineState::MilkReservoir:
        m_milkReservoir.update();
        m_currentState = CoffeeMachineState::MainMenu;
        break;
    case CoffeeMachineState::PowerOffRequest:
    {
        powerOff();
        break;
    }
    case CoffeeMachineState::LowWaterError:
    {
        showLowWaterError();
        break;
    }
    case CoffeeMachineState::LowMilkError:
    {
        showLowMilkError();
        break;
    }
    case CoffeeMachineState::SpoiledMilkError:
    {
        showSpoiledMilkError();
        break;
    }
    case CoffeeMachineState::CoffeeGrain:
        break;
    default:
        break;
    }
}

void CoffeeMachine::powerOn()
{
    if (m_currentChoice == 1)
    {
        std::cout << "\nGrrrr... Self diagnostics... Checking water and milk level...\n";

        if (m_waterReservoir.getVolume() <= 0.0f)
        {
            m_currentState = CoffeeMachineState::LowWaterError;
        }
        if (m_milkReservoir.getVolume() <= 0.0f)
        {
            m_currentState = CoffeeMachineState::LowMilkError;
        }
        else
        {
            m_currentState = CoffeeMachineState::MainMenu;
        }
    }
}

void CoffeeMachine::powerOff()
{
    std::cout << "Grrrrrr.... Bye-bye... (Cool animation's playing)\n\n\n";
    m_powerOffRequest = true;
}

void CoffeeMachine::selectNewMenuFromMain()
{
    switch (m_currentChoice)
    {
    case 1:
        m_currentState = CoffeeMachineState::DrinkSelection;
        break;
    case 2:
        m_currentState = CoffeeMachineState::WaterReservoir;
        break;
    case 3:
        m_currentState = CoffeeMachineState::MilkReservoir;
        break;
    case 5: 
        m_currentState = CoffeeMachineState::PowerOffRequest;
        break;
    default:
        m_currentState = CoffeeMachineState::MainMenu;
        break;
    }
}

void CoffeeMachine::showListOfDrinks()
{
    std::cout << std::endl;
    for (int i = 0; i < m_recipes.size(); i++)
    {
        std::cout << i + 1 << ". ";
        m_recipes[i]->showInfo();
        std::cout << std::endl;
    }
}

void CoffeeMachine::selectDrink()
{
    const int receipeIdx = m_currentChoice - 1;
    if (receipeIdx >= 0 && receipeIdx < m_recipes.size())
    {
        m_SelectedDrink = m_recipes[receipeIdx];
    }

    if (m_SelectedDrink != nullptr)
    {
        m_currentState = CoffeeMachineState::DrinkPreparation;
    }
    else
    {
        m_currentState = CoffeeMachineState::DrinkSelection;
    }
}

void CoffeeMachine::showLowWaterError()
{
    std::cout << "LOW WATER, please refill the water container!\n";
    m_currentState = CoffeeMachineState::MainMenu;
}
void CoffeeMachine::showLowMilkError()
{
    std::cout << "LOW MILK, please refill the milk container!\n";
    m_currentState = CoffeeMachineState::MainMenu;
}
void CoffeeMachine::showSpoiledMilkError()
{
    std::cout << "MILK SPOILED, please replace the milk!\n";
    m_currentState = CoffeeMachineState::MainMenu;
}

void CoffeeMachine::prepareDrink()
{
    //Sanity check. Ideally we shouldn't get this far is a drink wasn't selected correctly
    if (m_SelectedDrink == nullptr)
    {
        m_currentState = CoffeeMachineState::DrinkSelection;
        return;
    }

    const DrinkProgramStatus status = m_SelectedDrink->prepare();

    if (status == DrinkProgramStatus::Success)
    {
        m_currentState = CoffeeMachineState::MainMenu;
    }
    else if (status == DrinkProgramStatus::LowWater)
    {
        m_currentState = CoffeeMachineState::LowWaterError;
    }
    else if (status == DrinkProgramStatus::LowMilk)
    {
        m_currentState = CoffeeMachineState::LowMilkError;
    }
    else if (status == DrinkProgramStatus::SpoiledMilk)
    {
        m_currentState = CoffeeMachineState::SpoiledMilkError;
    }
}

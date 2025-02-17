#include "CoffeeMachineState.h"
#include "CoffeeMachine.h"
#include <iostream>

//class CoffeeMachine;
enum class DrinkProgramStatus;

// CoffeeMachineState
void CoffeeMachineState::changeState(CoffeeMachine& context, CoffeeMachineState* newState)
{
    context.setState(newState);
}

// Sleep
void Sleep::showMenu(CoffeeMachine& context)
{
	std::cout << "1. POWER ON\n";
}
void Sleep::receiveInput(CoffeeMachine& context)
{
	std::cout << "Choice: ";
	std::cin >> input;
	context.setCurrentChoice(input);
}
void Sleep::update(CoffeeMachine& context)
{
	if (context.getCurrentChoice() == 1)
	{
		std::cout << "\nGrrrr... Self diagnostics... Checking water level...\n";

		if (context.getWaterReservoir()->getVolume() <= 0.0f)
		{	
			changeState(context, new LowWater());
		}
		else
		{
			changeState(context, new MainMenu());
		}
	}
}

// PowerOff
void PowerOff::showMenu(CoffeeMachine& context)
{
	std::cout << "Grrrrrr.... Bye-bye... (Cool animation's playing)\n\n\n";
}
void PowerOff::update(CoffeeMachine& context)
{
	context.setPowerOffRequest(true);
}

// MainMenu
void MainMenu::showMenu(CoffeeMachine& context)
{
	std::cout << "\n1. Prepare Drink\n";
	std::cout << "2. Access Water Reservoir\n";
	std::cout << "3. Access Milk Reservoir\n";
	std::cout << "4. Access Coffe Grain Container\n";
	std::cout << "5. Select coffee strength\n";
	std::cout << "6. Clean\n";
	std::cout << "0. Power off\n";
}
void MainMenu::receiveInput(CoffeeMachine& context)
{
	std::cout << "Choice: ";
	std::cin >> input;
	context.setCurrentChoice(input);
}
void MainMenu::update(CoffeeMachine& context)
{
	switch (context.getCurrentChoice())
	{
	case 1:
		changeState(context, new DrinkSelection());
		break;
	case 2:
		changeState(context, new WaterReservoirState());
		break;
	case 3:
		changeState(context, new MilkReservoirState());
		break;
	case 4:
		changeState(context, new CoffeeGrainsContainerState());
		break;
	case 5:
		changeState(context, new CoffeeStrength());
		break;
	case 6:
		changeState(context, new Clean());
		break;
	case 0:
		changeState(context, new PowerOff());
		break;
	default:
		changeState(context, new MainMenu());
		break;
	}
}

// DrinkSelection
void DrinkSelection::showMenu(CoffeeMachine& context)
{
	context.showListOfDrinks();
}
void DrinkSelection::receiveInput(CoffeeMachine& context)
{
	std::cout << "Choice: ";
	std::cin >> input;
	context.setCurrentChoice(input);
}
void DrinkSelection::update(CoffeeMachine& context)
{
	context.selectDrink();
	if (context.getSelectedDrink() != nullptr)
	{
		changeState(context, new DrinkPreparation());
	}
	else
	{
		changeState(context, new DrinkSelection());
	}
}

// DrinkPreparation
void DrinkPreparation::update(CoffeeMachine& context)
{
	if (context.getSelectedDrink() == nullptr)
	{
		changeState(context, new DrinkSelection());
		return;
	}

	const DrinkProgramStatus status = context.getSelectedDrink()->prepare();

	if (status == DrinkProgramStatus::Success)
	{
		changeState(context, new MainMenu());
	}
	else if (status == DrinkProgramStatus::CleanNeeded)
	{
		changeState(context, new CleanNeeded());
	}
	else if (status == DrinkProgramStatus::LowWater)
	{
		changeState(context, new LowWater());
	}
	else if (status == DrinkProgramStatus::LowCoffeeGrains)
	{
		changeState(context, new LowCoffeeGrains());
	}
	else if (status == DrinkProgramStatus::LowMilk)
	{
		changeState(context, new LowMilk());
	}
	else if (status == DrinkProgramStatus::SpoiledMilk)
	{
		changeState(context, new SpoiledMilk());
	}
}

// Clean
void Clean::showMenu(CoffeeMachine& context)
{
	std::cout << "1. Clean Coffee Machine\n";
	std::cout << "2. Back to main\n";
}
void Clean::receiveInput(CoffeeMachine& context)
{
	std::cout << "Choice: ";
	std::cin >> input;
	context.setCurrentChoice(input);
}
void Clean::update(CoffeeMachine& context)
{
	switch (context.getCurrentChoice())
	{
	case 1:
		DrinkProgram::clean();
		break;
	case 2:
		changeState(context, new MainMenu());
		break;
	}
	changeState(context, new MainMenu());
}

// WaterReservoir
void WaterReservoirState::showMenu(CoffeeMachine& context)
{
	context.getWaterReservoir()->showOperations();
}
void WaterReservoirState::receiveInput(CoffeeMachine& context)
{
	context.getWaterReservoir()->receiveInput();
}
void WaterReservoirState::update(CoffeeMachine& context)
{
	context.getWaterReservoir()->update();
	changeState(context, new MainMenu());
}

// MilkReservoir
void MilkReservoirState::showMenu(CoffeeMachine& context)
{
	context.getMilkReservoir()->showOperations();
}
void MilkReservoirState::receiveInput(CoffeeMachine& context)
{
	context.getMilkReservoir()->receiveInput();
}
void MilkReservoirState::update(CoffeeMachine& context)
{
	context.getMilkReservoir()->update();
	changeState(context, new MainMenu());
}

// CoffeeGrainsContainer
void CoffeeGrainsContainerState::showMenu(CoffeeMachine& context)
{
	context.getCoffeeContainer()->showOperations();
}
void CoffeeGrainsContainerState::receiveInput(CoffeeMachine& context)
{
	context.getCoffeeContainer()->receiveInput();
}
void CoffeeGrainsContainerState::update(CoffeeMachine& context)
{
	context.getCoffeeContainer()->update();
	changeState(context, new MainMenu());
}

// CoffeeStrength
void CoffeeStrength::showMenu(CoffeeMachine& context)
{
	std::cout << "\nCoffee strength level\n";
	std::cout << "1. Mild\n";
	std::cout << "2. Medium\n";
	std::cout << "3. Strong\n";
	std::cout << "4. Very Strong\n";
	std::cout << "5. Extra Strong\n";
}
void CoffeeStrength::receiveInput(CoffeeMachine& context)
{
	std::cout << "Choice: ";
	std::cin >> input;
	context.setCurrentChoice(input);
}
void CoffeeStrength::update(CoffeeMachine& context)
{
	switch (context.getCurrentChoice())
	{
	case 1:
		Coffee::setStrength(context.getCurrentChoice());
		break;
	case 2:
		Coffee::setStrength(context.getCurrentChoice());
		break;
	case 3:
		Coffee::setStrength(context.getCurrentChoice());
		break;
	case 4:
		Coffee::setStrength(context.getCurrentChoice());
		break;
	case 5:
		Coffee::setStrength(context.getCurrentChoice());
		break;
	default:
		Coffee::setStrength(3);
		break;
	}
	changeState(context, new MainMenu());
}

// CleeCleanNeedednNeeded
void CleanNeeded::showMenu(CoffeeMachine& context)
{
	std::cout << "Please clean the coffee machine!\n";
}
void CleanNeeded::update(CoffeeMachine& context)
{
	changeState(context, new MainMenu());
}

// LowWater
void LowWater::showMenu(CoffeeMachine& context)
{
	std::cout << "LOW WATER, please refill the water container!\n";
}
void LowWater::update(CoffeeMachine& context)
{
	changeState(context, new MainMenu());
}

// LowCoffeeGrains
void LowCoffeeGrains::showMenu(CoffeeMachine& context)
{
	std::cout << "LOW COFFEE GRAINS, please refill the coffee grains container!\n";
}
void LowCoffeeGrains::update(CoffeeMachine& context)
{
	changeState(context, new MainMenu());
}

// LowMilk
void LowMilk::showMenu(CoffeeMachine& context)
{
	std::cout << "LOW MILK, please refill the milk container!\n";
}
void LowMilk::update(CoffeeMachine& context)
{
	changeState(context, new MainMenu());
}


// SpoiledMilk
void SpoiledMilk::showMenu(CoffeeMachine& context)
{
	std::cout << "MILK SPOILED, please replace the milk!\n";
}
void SpoiledMilk::update(CoffeeMachine& context)
{
	changeState(context, new MainMenu());
}
#include "CoffeeMachine.h"

void CoffeeMachine::initDefaultDrinks()
{
    m_recipes.push_back(new Espresso("Espresso", *this));
    m_recipes.push_back(new Cappuccino("Cappuccino", *this));
    m_recipes.push_back(new Latte("Latte", *this));
    m_recipes.push_back(new BlackTea("Black tea", 90, *this));
    m_recipes.push_back(new GreenTea("Green tea", 85, *this));
    m_recipes.push_back(new MatchaTea("Matcha tea", 76, *this));
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
}
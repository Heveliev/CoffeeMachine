#include "WaterReservoir.h"
#include <iostream>

void WaterReservoir::showOperations()
{
    std::cout << "\n--- Current water level: " << getVolume() << "l out of " << MaxVolume << "l max ---\n";
    std::cout << "1. Empty reservoir\n";
    std::cout << "2. Fill up with water\n";
    std::cout << "3. Back to main\n";
}

void WaterReservoir::receiveInput()
{
    //TODO, general: Validate input
    std::cout << "Choice: ";
    std::cin >> m_Operation;
}

void WaterReservoir::update()
{
    switch (m_Operation)
    {
    case 1:
        m_Volume = 0.0f;
        break;
    case 2:
    {
        float newVolume = 0.0f;
        std::cout << "Filling...";
        std::cout << "How much have you filled up? (Max: " << MaxVolume << "l) ";
        std::cin >> newVolume;

        m_Volume = std::min(newVolume, MaxVolume);

        std::cout << std::endl;
        break;
    }
    case 3:
    default:
        break;
    }
}

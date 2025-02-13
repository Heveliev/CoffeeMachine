#include "MilkReservoir.h"
#include <iostream>
#include <ctime>
#include "./validationReservoirInput/validationReservoirInput.h"

void MilkReservoir::showOperations()
{
    std::cout << "\n--- Current milk level: " << getVolume() << "l out of " << MaxVolume << "l max ---\n";
    std::cout << "1. Empty reservoir\n";
    std::cout << "2. Fill up with milk\n";
    std::cout << "3. Back to main\n";
}

void MilkReservoir::receiveInput()
{
    //TODO, general: Validate input
    Validation status = Validation::Invalid;
    int input = 0;
    while (status != Validation::Success)
    {

        std::cout << "Choice: ";
        std::cin >> input;
        status = validationReservoirInput(input);
        if (status == Validation::Success) 
        {
            m_Operation = input;
            break;
        }

        if (status == Validation::Invalid)
        {
            std::cout << "Invalid Value" << std::endl << std::endl;
            continue;
        }
    }
}


void MilkReservoir::update()
{
    switch (m_Operation)
    {
    case 1:
        empty();
        break;
    case 2:
    {
        float newVolume = 0.0f;
        std::cout << "Filling...";
        std::cout << "How much have you filled up? (Max: " << MaxVolume << "l) ";
        std::cin >> newVolume;
        fill(newVolume);
        std::cout << std::endl;
        break;
    }
    case 3:
    default:
        break;
    }
}

void MilkReservoir::empty()
{
    m_Volume = 0.0f;
    m_milkState = MilkState::Fresh;
    m_startTime = 0;
}

void MilkReservoir::fill(float volume)
{
    m_milkState = MilkState::Fresh;
    m_startTime = timeNow();
    m_Volume = std::min(volume, MaxVolume);
}

MilkState MilkReservoir::getMilkState()
{ 
    int time = (timeNow() - m_startTime);
    if (time > m_spoilTime)
    {
        m_milkState = MilkState::Spoiled;
    }
    return m_milkState; 
}

int MilkReservoir::timeNow()
{
	return static_cast<int>(std::time(nullptr));
}
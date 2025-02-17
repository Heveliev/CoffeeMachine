#include "Reservoir.h"
#include <iostream>
#include <string>
#include "./validationReservoirInput/validationReservoirInput.h"


void Reservoir::showOperations()
{
    std::cout << "\n--- Current " << m_content << " level: " << getVolume() << m_unit << " out of " 
        << m_MaxVolume << m_unit << " max ---\n";
    std::cout << "1. Empty reservoir\n";
    std::cout << "2. Fill up with " << m_content << std::endl;
    std::cout << "3. Back to main\n";
}


void Reservoir::receiveInput()
{
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

void Reservoir::update()
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
        std::cout << "How much have you filled up? (Max: " << m_MaxVolume << "l) ";
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


// MilkReservoir
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
    m_Volume = std::min(volume, m_MaxVolume);
}

MilkState MilkReservoir::getMilkState()
{
    int time = (timeNow() - m_startTime);
    if (time > m_spoilTime && m_startTime != 0)
    {
        m_milkState = MilkState::Spoiled;
    }
    return m_milkState;
}

int MilkReservoir::timeNow()
{
    return static_cast<int>(std::time(nullptr));
}
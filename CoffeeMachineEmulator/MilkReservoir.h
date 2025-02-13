#pragma once
#include <algorithm>


enum class MilkState
{
    Fresh,
    Spoiled
};

class MilkReservoir
{
    //TODO HW: Need to implement MilkReservoir logic to be able to prepare Cappuccino
    //See WaterReservoir for reference, the logic here will be very similar
public:
    void showOperations();
    void receiveInput();

    void fill(float volume);

    void getMilk(float volume) { m_Volume -= volume; }

    MilkState getMilkState();

    void empty();

    float getVolume() const { return m_Volume; }

    void update();

    //TODO HW ADDITIONAL: implement milk freshness logic
    //E.g.: start new timer after every empty/fill operation
    //and once this specified time is passed(in seconds/minutes for simplicity to test - mark that milk as gone bad and you can't prepare new Milk-required drinks
    //until the MilkReservoir is emptied and filled once again

private:
    int timeNow();

private:

    int m_Operation = -1;
    int m_spoilTime = 20;
    int m_startTime = 0;
    float m_Volume = 0.0f;
    const float MaxVolume = 2.0f;
    MilkState m_milkState = MilkState::Fresh;
};
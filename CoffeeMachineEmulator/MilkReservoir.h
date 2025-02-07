#pragma once

class MilkReservoir
{
    //TODO HW: Need to implement MilkReservoir logic to be able to prepare Cappuccino
    //See WaterReservoir for reference, the logic here will be very similar
public:
    void showOperations() {}
    void receiveInput() {}

    void fill(float volume) {};
    void getMilk(float volume) {};

    void empty() {};
    float getVolume() { return 0.0f; }


    //TODO HW ADDITIONAL: implement milk freshness logic
    //E.g.: start new timer after every empty/fill operation
    //and once this specified time is passed(in seconds/minutes for simplicity to test - mark that milk as gone bad and you can't prepare new Milk-required drinks
    //until the MilkReservoir is emptied and filled once again

private:

};
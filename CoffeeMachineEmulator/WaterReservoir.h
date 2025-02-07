#pragma once

class WaterReservoir
{
public:
    void showOperations();
    void receiveInput();
    void update();

    float getVolume() const { return m_Volume; }
    void useWater(float Volume) { m_Volume -= Volume; }

private:
    int m_Operation = -1;

    float m_Volume = 0.0f;
    const float MaxVolume = 2.0f;
};
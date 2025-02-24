#pragma once
#include <string>


class Reservoir
{
public:
    Reservoir(const std::string& content, const char& unit, const float& maxValue) : m_content(content),
        m_unit(unit), m_MaxVolume(maxValue) {}

    void showOperations();

    void receiveInput();
    void update();

    virtual void fill(float volume) = 0;
    virtual void empty() = 0;

    float getVolume() const { return m_Volume; }

    void useVolume(float Volume) { m_Volume -= Volume; }

protected:
    const std::string m_content;
    const char m_unit;
    int m_Operation = -1;
    float m_Volume = 0.0f;
    const float m_MaxVolume = 2.0f;
};

// WaterReservoir
class WaterReservoir : public Reservoir
{
public:
    WaterReservoir() : Reservoir("water", 'l', 2.0f) {}

    void fill(float volume) override { m_Volume = std::min(volume, m_MaxVolume); };
    void empty() override { m_Volume = 0.0f; };
};


// MilkReservoir
enum class MilkState
{
    Fresh,
    Spoiled
};

class MilkReservoir : public Reservoir
{
public:
    MilkReservoir() : Reservoir("milk",'l', 2.0f) {}

    MilkState getMilkState();
    void fill(float volume) override;
    void empty() override;

private:
    int timeNow();

private:
    int m_spoilTime = 20;
    int m_startTime = 0;
    MilkState m_milkState = MilkState::Fresh;
};

// CoffeeGrainsContainer
class CoffeeGrainsContainer : public Reservoir
{
public:
    CoffeeGrainsContainer() : Reservoir("coffee grains", 'g', 1000.0f) {}

    void fill(float volume) override { m_Volume = std::min(volume, m_MaxVolume); };
    void empty() override { m_Volume = 0.0f; };

};
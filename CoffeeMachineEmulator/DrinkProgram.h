#pragma once
#include <string>

enum class DrinkType
{
    Espresso,
    Cappuccino
};

enum class DrinkProgramStatus
{
    Success = 0,
    LowWater,
    CleanNeeded,
    LowMilk,
    SpoiledMilk,
    LowCoffeeGrains,

    Count,
};

// DrinkProgram class
class DrinkProgram
{
protected:
    DrinkProgram(std::string drinkName, class CoffeeMachine& context);
    DrinkProgram(std::string drinkName, unsigned short temperature, CoffeeMachine& context);

public:
    void showInfo();
    virtual DrinkProgramStatus prepare() = 0;
    static void clean() { m_useAmount = 0; }

protected:
    virtual void checkReservoirs() = 0;

    CoffeeMachine& getContext() { return m_context; }

    void finishPreparation();
    static bool getUse() { return m_useAmount; }
    void checkUses();
protected:
    static unsigned short m_useAmount;
    const unsigned short m_useAmountMax = 1;
    DrinkProgramStatus status = DrinkProgramStatus::Success;
    std::string m_name;
    unsigned short m_temperature = 85;
    class CoffeeMachine& m_context;

};

// Coffee class
class Coffee : public DrinkProgram
{
protected:
    Coffee(std::string drinkName, class CoffeeMachine& context) : 
        DrinkProgram(drinkName, context) {}

    Coffee(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        DrinkProgram(drinkName, temperature, context) {}

public:
    static void setStrength(unsigned short strength);

protected:
    void checkReservoirs() override;
    void grindGrains();


protected:
    const float EsspressoWaterVolume = 0.05f;
    static unsigned short m_strength;
    const unsigned short m_coffeeDose = 5;

};
// Espresso class
class Espresso : public Coffee
{
public:
    Espresso(std::string drinkName, class CoffeeMachine& context) :
        Coffee(drinkName, context) {}

    Espresso(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Coffee(drinkName, temperature, context) {}

    DrinkProgramStatus prepare() override;

private:
};

// Cappuccino class
class Cappuccino : public Coffee
{
public:
    Cappuccino(std::string drinkName, class CoffeeMachine& context) :
        Coffee(drinkName, context) {}

    Cappuccino(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Coffee(drinkName, temperature, context) {}

    DrinkProgramStatus prepare() override;

private:
    void checkReservoirs();

private:
    const float MilkVolume = 0.2f;
};

//Latte class
class Latte : public Coffee
{
public:
    Latte(std::string drinkName, class CoffeeMachine& context) :
        Coffee(drinkName, context) {}

    Latte(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Coffee(drinkName, temperature, context) {}

    DrinkProgramStatus prepare() override;

private:
    void checkReservoirs();

private:
    const float MilkVolume = 0.3f;
};


class Tea : public DrinkProgram
{
public:
    Tea(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        DrinkProgram(drinkName, temperature, context) {}
  
protected:
    void checkReservoirs() override;
    void prepareWater();



protected:
    float m_waterAmount = 0.25f;
};

class BlackTea : public Tea
{
public:
    BlackTea(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Tea(drinkName, temperature, context) {}

    DrinkProgramStatus prepare() override;
};

class GreenTea : public Tea
{
public:
    GreenTea(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Tea(drinkName, temperature, context) {}

    DrinkProgramStatus prepare() override;
};

class MatchaTea : public Tea
{
public:
    MatchaTea(std::string drinkName, unsigned short temperature, CoffeeMachine& context) :
        Tea(drinkName, temperature, context)
    {
        m_waterAmount = 0.05f;
    }

    DrinkProgramStatus prepare() override;
private:
    void checkReservoirs() override;

private:
    const float MilkVolume = 0.2f;
};

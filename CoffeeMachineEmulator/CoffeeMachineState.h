#pragma once

class CoffeeMachine;

class CoffeeMachineState
{
public:
    virtual ~CoffeeMachineState() = default;

    virtual void showMenu(class CoffeeMachine& context) = 0;
    virtual void update(CoffeeMachine& context) = 0;
    virtual void receiveInput(CoffeeMachine& context) = 0;

protected:
    void changeState(CoffeeMachine& context, CoffeeMachineState* newState);

protected:
    int input;
};

class Sleep : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
};

// PowerOff
class PowerOff : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {}
};

// MainMenu
class MainMenu : public CoffeeMachineState
{
public:
	void showMenu(CoffeeMachine& context) override;
	void receiveInput(CoffeeMachine& context) override;
	void update(CoffeeMachine& context) override;
};

// DrinkSelection
class DrinkSelection : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// DrinkPreparation
class DrinkPreparation : public CoffeeMachineState
{
public:
    void update(CoffeeMachine& context) override;
    void showMenu(CoffeeMachine& context) {};
    void receiveInput(CoffeeMachine& context) {};
};

// Clean
class Clean : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// WaterReservoir
class WaterReservoirState : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// MilkReservoir
class MilkReservoirState : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// CoffeeGrainsContainer
class CoffeeGrainsContainerState : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// CoffeeStrength
class CoffeeStrength : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
};

// CleanNeeded
class CleanNeeded : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {};
};

// LowWater
class LowWater : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {};
};

// LowCoffeeGrains
class LowCoffeeGrains : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {};
};

// LowMilk
class LowMilk : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {};
};


// SpoiledMilk
class SpoiledMilk : public CoffeeMachineState
{
public:
    void showMenu(CoffeeMachine& context) override;
    void update(CoffeeMachine& context) override;
    void receiveInput(CoffeeMachine& context) {};
};
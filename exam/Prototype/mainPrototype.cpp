#include <iostream>
#include <memory>
#include <string>

// Базовый интерфейс прототипа
class Character {
public:
    virtual ~Character() = default;
    virtual std::unique_ptr<Character> clone() const = 0;
    virtual void printInfo() const = 0;
};

// Конкретный класс: Воин
class Warrior : public Character {
private:
    std::string weapon;
    int health;

public:
    Warrior(std::string weapon, int health)
            : weapon(std::move(weapon)), health(health) {}

    std::unique_ptr<Character> clone() const override {
        return std::make_unique<Warrior>(*this);
    }

    void printInfo() const override {
        std::cout << "Warrior | Weapon: " << weapon
                  << " | Health: " << health << std::endl;
    }
};

// Конкретный класс: Маг
class Mage : public Character {
private:
    std::string spell;
    int mana;

public:
    Mage(std::string spell, int mana)
            : spell(std::move(spell)), mana(mana) {}

    std::unique_ptr<Character> clone() const override {
        return std::make_unique<Mage>(*this);
    }

    void printInfo() const override {
        std::cout << "Mage | Spell: " << spell
                  << " | Mana: " << mana << std::endl;
    }
};

int main() {
    // Создаем прототипы
    auto originalWarrior = std::make_unique<Warrior>("Sword", 100);
    auto originalMage = std::make_unique<Mage>("Fireball", 200);

    // Клонируем объекты
    auto clonedWarrior = originalWarrior->clone();
    auto clonedMage = originalMage->clone();

    // Выводим информацию
    clonedWarrior->printInfo(); // Warrior | Weapon: Sword | Health: 100
    clonedMage->printInfo();    // Mage | Spell: Fireball | Mana: 200

    return 0;
}
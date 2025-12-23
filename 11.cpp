#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>

// ========================================================
// 1. MagicSpell — реализация "Правила пяти" (Rule of Five)
// ========================================================
class MagicSpell {
private:
    char* spellName_ = nullptr;
    int powerLevel_ = 0;

public:
    explicit MagicSpell(const char* name, int power = 0) 
        : powerLevel_(power) {
        if (name) {
            size_t len = std::strlen(name) + 1;
            spellName_ = new char[len];
            std::strcpy(spellName_, name);
        }
        std::cout << "MagicSpell created: " << (spellName_ ? spellName_ : "null") << '\n';
    }

    ~MagicSpell() {
        std::cout << "MagicSpell destroyed: " << (spellName_ ? spellName_ : "null") << '\n';
        delete[] spellName_;
    }

    MagicSpell(const MagicSpell& other) 
        : powerLevel_(other.powerLevel_) {
        if (other.spellName_) {
            size_t len = std::strlen(other.spellName_) + 1;
            spellName_ = new char[len];
            std::strcpy(spellName_, other.spellName_);
        } else {
            spellName_ = nullptr;
        }
        std::cout << "MagicSpell copied: " << (spellName_ ? spellName_ : "null") << '\n';
    }

    MagicSpell& operator=(const MagicSpell& other) {
        if (this != &other) {
            delete[] spellName_;
            powerLevel_ = other.powerLevel_;
            if (other.spellName_) {
                size_t len = std::strlen(other.spellName_) + 1;
                spellName_ = new char[len];
                std::strcpy(spellName_, other.spellName_);
            } else {
                spellName_ = nullptr;
            }
            std::cout << "MagicSpell copy-assigned: " << (spellName_ ? spellName_ : "null") << '\n';
        }
        return *this;
    }

    MagicSpell(MagicSpell&& other) noexcept
        : spellName_(other.spellName_), powerLevel_(other.powerLevel_) {
        other.spellName_ = nullptr;
        other.powerLevel_ = 0;
        std::cout << "MagicSpell moved (constructor)\n";
    }

    MagicSpell& operator=(MagicSpell&& other) noexcept {
        if (this != &other) {
            delete[] spellName_;
            spellName_ = other.spellName_;
            powerLevel_ = other.powerLevel_;
            other.spellName_ = nullptr;
            other.powerLevel_ = 0;
            std::cout << "MagicSpell moved (assignment)\n";
        }
        return *this;
    }

    void cast() const {
        if (spellName_) {
            std::cout << "Casting spell: " << spellName_ 
                      << " (power: " << powerLevel_ << ")\n";
        } else {
            std::cout << "Spell is empty (was moved from)\n";
        }
    }

    void boostPower(int amount) {
        powerLevel_ += amount;
    }

    bool empty() const {
        return spellName_ == nullptr;
    }
};

// ========================================================
// 2. Wizard — эксклюзивное владение через unique_ptr
// ========================================================
class Wizard {
private:
    std::string name_;
    std::unique_ptr<MagicSpell> exclusiveSpell_;

public:
    explicit Wizard(std::string name) : name_(std::move(name)) {
        std::cout << "Wizard " << name_ << " created\n";
    }

    ~Wizard() {
        std::cout << "Wizard " << name_ << " destroyed\n";
    }

    void learnSpell(std::unique_ptr<MagicSpell> spell) {
        exclusiveSpell_ = std::move(spell);
        std::cout << name_ << " learned a new spell!\n";
    }

    std::unique_ptr<MagicSpell> transferSpell() {
        std::cout << name_ << " transfers spell ownership\n";
        return std::move(exclusiveSpell_);
    }

    void castSpell() const {
        std::cout << name_ << " attempts to cast: ";
        if (exclusiveSpell_) {
            exclusiveSpell_->cast();
        } else {
            std::cout << "No spell learned!\n";
        }
    }

    bool hasSpell() const {
        return static_cast<bool>(exclusiveSpell_);
    }
};

// ========================================================
// 3. Arena — общий ресурс
// ========================================================
class Arena {
public:
    const std::string name;

    explicit Arena(std::string arenaName) : name(std::move(arenaName)) {
        std::cout << "Arena '" << name << "' created\n";
    }

    ~Arena() {
        std::cout << "Arena '" << name << "' destroyed\n";
    }

    void battleInfo() const {
        std::cout << "Battle taking place at: " << name << '\n';
    }
};

// ========================================================
// 4. Team — совместное владение ареной
// ========================================================
class Team {
private:
    std::string teamName_;
    std::shared_ptr<Arena> battleArena_;

public:
    Team(std::string name, std::shared_ptr<Arena> arena)
        : teamName_(std::move(name)), battleArena_(std::move(arena)) {
        std::cout << "Team '" << teamName_ << "' formed\n";
        std::cout << "Arena use_count: " << battleArena_.use_count() << '\n';
    }

    void displayArenaInfo() const {
        if (battleArena_) {
            std::cout << "Team '" << teamName_ << "' is at arena: ";
            battleArena_->battleInfo();
            std::cout << "Current use_count: " << battleArena_.use_count() << '\n';
        }
    }

    std::shared_ptr<Arena> getArena() const {
        return battleArena_;
    }

    std::string getName() const {
        return teamName_;
    }
};

// ========================================================
// 5. Spectator — наблюдение через weak_ptr
// ========================================================
class Spectator {
private:
    std::string name_;
    std::weak_ptr<Arena> observedArena_;

public:
    Spectator(std::string name, std::weak_ptr<Arena> arena)
        : name_(std::move(name)), observedArena_(std::move(arena)) {
        std::cout << "Spectator '" << name_ << "' arrived\n";
    }

    void watchBattle() const {
        if (auto arena = observedArena_.lock()) {
            std::cout << name_ << " is watching battle at: " << arena->name << '\n';
            std::cout << "Arena is alive (use_count: " << arena.use_count() << ")\n";
        } else {
            std::cout << name_ << " sees no battle — arena is destroyed!\n";
        }
    }
};

// ========================================================
// Тесты с фэнтези-именами
// ========================================================
void testMagicSpell() {
    std::cout << "\n=== Test 1: MagicSpell (Rule of Five) ===\n";
    MagicSpell spell("Огненный Вихрь", 100);
    spell.cast();

    MagicSpell copy = spell;
    copy.boostPower(30);
    copy.cast();

    MagicSpell moved = std::move(spell);
    moved.cast();
    spell.cast();
}

void testWizard() {
    std::cout << "\n=== Test 2: Wizard (unique_ptr) ===\n";
    Wizard elrion("Эльриан");
    Wizard morwen("Морвен Штормоглас");

    auto spell = std::make_unique<MagicSpell>("Ледяной Взрыв", 95);
    elrion.learnSpell(std::move(spell));
    elrion.castSpell();

    morwen.learnSpell(elrion.transferSpell());
    elrion.castSpell();  // больше нет заклинания
    morwen.castSpell();  // теперь у Морвена
}

void testTeamAndSpectator() {
    std::cout << "\n=== Test 3: Team & Spectator (shared_ptr + weak_ptr) ===\n";
    auto arena = std::make_shared<Arena>("Арена Вечного Пламени");
    std::cout << "Initial arena use_count: " << arena.use_count() << '\n';

    Team crimsonOrder("Орден Алого Листа", arena);
    Team ashHawks("Пепельные Ястребы", arena);

    Spectator silentWatcher("Орин Безмолвный", arena);
    silentWatcher.watchBattle();

    std::cout << "\n--- Destroying all teams ---\n";
    arena.reset();

    std::cout << "After arena destruction:\n";
    silentWatcher.watchBattle();
}

// ========================================================
// MAIN
// ========================================================
int main() {
    std::cout << "===== C++ Smart Pointers & Move Semantics: Realm of Arcana =====\n";

    testMagicSpell();
    testWizard();
    testTeamAndSpectator();

    std::cout << "\n===== The magic fades... =====\n";
    return 0;
}
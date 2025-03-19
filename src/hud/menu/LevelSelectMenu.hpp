#ifndef WORLDSELECTMENU_HPP
#define WORLDSELECTMENU_HPP

#include "Menu.hpp"
#include "Button.hpp"
#include <vector>

class WorldSelectMenu : public Menu {
private:
    virtual void initButtons() override;

public:
    WorldSelectMenu();
    ~WorldSelectMenu() = default;
};

#endif // WORLDSELECTMENU_HPP
#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>

class ControllerManager {
  private:
    std::map<std::string, int> actionKeyName;
    std::map<int, bool> keysDown;

    std::map<std::string, int> mouseButtonName;
    std::map<int, bool> mouseButtonsDown;
    int mousePosX;
    int mousePosY;

  public:
    ControllerManager();
    ~ControllerManager();

    void clear();
    
    //Keyboard
    void addActionKey(const std::string& action, int keyCode);
    void keyDown(int keyCode);
    void keyUp(int keyCode);
    bool isActionActivated(const std::string& action) const;

    //mouse
    void addMouseButton(const std::string& name, int buttonCode);
    void mouseButtonDown(int buttonCode);
    void mouseButtonUp(int buttonCode);
    bool isMouseButtonDown(const std::string& name);

    void setMousePosition (int x, int y);
    std::tuple<int, int> getMousePosition();
};

#endif // CONTROLLERMANAGER_HPP
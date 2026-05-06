#include "ControllerManager.hpp"

#include <iostream>
#include <map>
#include <string>

ControllerManager::ControllerManager() {
    std::cout << "[CONTROLLERMANAGER] Se ejecuta el constructor" << std::endl;
}

ControllerManager::~ControllerManager() {
    std::cout << "[CONTROLLERMANAGER] Se ejecuta el destructor" << std::endl;
}

void ControllerManager::clear() {
    actionKeyName.clear();
    keysDown.clear();
}

void ControllerManager::addActionKey(const std::string& action, int keyCode){
    actionKeyName.emplace(action, keyCode);
    keysDown.emplace(keyCode, false);
}
void ControllerManager::keyDown(int keyCode){
    auto it = keysDown.find(keyCode);
    if (it != keysDown.end()) {
        keysDown[keyCode] = true;
    }
}
void ControllerManager::keyUp(int keyCode){
    auto it = keysDown.find(keyCode);
    if (it != keysDown.end()) {
        keysDown[keyCode] = false;
    }
}
bool ControllerManager::isActionActivated(const std::string& action) const{
    auto it = actionKeyName.find(action);
    if (it != actionKeyName.end()) {
        int keyCode = it->second;
        return keysDown.at(keyCode);
    }
    return false;
}

void ControllerManager::addMouseButton(const std::string& name, int buttonCode) {
    mouseButtonName.emplace(name, buttonCode);
    mouseButtonsDown.emplace(buttonCode, false);
}

void ControllerManager::mouseButtonDown(int buttonCode) {
    auto it = mouseButtonsDown.find(buttonCode);
    if (it != mouseButtonsDown.end()) {
        mouseButtonsDown[buttonCode] = true;
    }
}

void ControllerManager::mouseButtonUp(int buttonCode) {
    auto it = mouseButtonsDown.find(buttonCode);
    if (it != mouseButtonsDown.end()) {
        mouseButtonsDown[buttonCode] = false;
    }
}

bool ControllerManager::isMouseButtonDown(const std::string& name) {
    auto it = mouseButtonName.find(name);
    if (it != mouseButtonName.end()) {
        int buttonCode = mouseButtonName[name];
        return mouseButtonsDown[buttonCode];
    }
    return false;
}

void ControllerManager::setMousePosition (int x, int y){
    mousePosX = x;
    mousePosY = y;

}

std::tuple<int, int> ControllerManager::getMousePosition() {
    return {mousePosX, mousePosY};
}
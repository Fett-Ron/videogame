#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "SceneLoader.hpp"

class SceneManager {
  private:
    std::map<std::string, std::string> scenes;
    std::string nextScene;
    bool isSceneRunning = false;
    std::unique_ptr<SceneLoader> sceneLoader;

  public:
    SceneManager();
    ~SceneManager();

    void loadSceneFromScript(const std::string& path, sol::state& lua);
    void loadScene();

    std::string getNextScene() const;
    void setNextScene(const std::string& nextScene);

    bool IsSceneRunning() const;
    void startScene();
    void stopScene();
};

#endif // SCENEMANAGER_HPP
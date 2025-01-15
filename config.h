#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    Config();
    int getGridSize() {return gridSize;};
    int getSceneSize() {return sceneSize;};
    void setGridSize(int gridSize) {this->gridSize = gridSize;};
    void setSceneSize(int sceneSize) {this->sceneSize = sceneSize;};

private:
    int gridSize = 40;
    int sceneSize = 2000;
};

#endif // CONFIG_H

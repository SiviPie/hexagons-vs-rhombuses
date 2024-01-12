#pragma once

#include "components/simple_scene.h"
#include "hexaghon.h"
#include "rhombus.h"
#include "resource.h"
#include "bullet.h"

namespace m1 {
    class Tema1 : public gfxc::SimpleScene {
    public:
        Tema1();
        ~Tema1();

        void Init() override;
    
    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // RENDER
        void RenderBoard();
        void RenderHealthBar(float posX, float gap);
        void RenderStarStats(float posX,float gap);
        void RenderHUD();
        void RenderHeroes();
        void RenderEnemies();
        void RenderResources();
        void RenderBullets();

        // SPAWN
        void SpawnResource(float posx, float posy);
        void SpawnResourcesRandom(float deltaTimeSeconds);
        void SpawnEnemy(float posx, float posy, int type, int health);
        void SpawnEnemyRandom(float deltaTimeSeconds);
        void SpawnBullet(float posx, float posy, int type);
        
        // UPDATE OBJECTS
        void UpdateObjectsAttributes(float deltaTimeSeconds); // MOVE AND SCALE ENEMIES AND BULLETS

        // CHECK
        void CheckLives(); // IF LIVES == 0, EXIT
        void CheckEnemiesHealth();
        void CheckFinishLine(); // CHECK IF ENEMY CROSSED FINISH LINE
        void CheckDamage(); // 
        void CheckBonus();

        // OTHER
        bool isEqualFloat(float f1, float f2);

    protected:
        glm::ivec2 resolution;
        glm::mat3 modelMatrix;

        // MESHES
        std::vector<char*> enemies;
        std::vector<char*> heroes;
        std::vector<char*> bullets;

        std::vector<Hexaghon> enemies_vec;
        std::vector<Rhombus> heroes_vec;
        std::vector<Resource> resources_vec;
        std::vector<Bullet> bullet_vec;
        
        Rhombus aux_hero;

        // DIMENSIONS
        float board_cell_side;
        float board_cell_gap;
        float hud_cell_side;
        float hud_cell_gap;
        float health_side;
        float star_side_small;
        float star_side_big;
        float bullet_side;
        float soldier_side;

        // STATS
        int lives; // 0-3
        int money; // 
        int kill_bonus_count;
        bool is_buying;
        bool pause;

        // POSITIONS
        float lines_posx[4];
        float lines_posy[3];
        float hud_posx[4];
        float hud_posy;

        // OTHER
        int prices[4];
        bool board_cells[3][3]; // TRUE IF HERO IN CELL

        // TIME
        float time_total;
        float time_spawn_enemy;
        float time_spawn_stars;
    };
}   // namespace m1


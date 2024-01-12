#include "lab_m1/tema1/tema1.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/shapes.h"
#include <iostream>

using namespace std;
using namespace m1;
using namespace shapes;

#define EPSILON 0.0005f;

// RENDER
void Tema1::RenderBoard() {
    // FINISH LINE
    modelMatrix = transform2D::Translate(lines_posx[0], lines_posy[1]);
    RenderMesh2D(meshes["finish_line"], shaders["VertexColor"], modelMatrix);

    // BOARD CELLS
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelMatrix = transform2D::Translate(lines_posx[i + 1], lines_posy[j]);
            RenderMesh2D(meshes["board_cell"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::RenderHealthBar(float posX, float gap) {
    for (int i = 0; i < lives; i++) {
        modelMatrix = transform2D::Translate(posX + (health_side + gap) * i, hud_posy);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderStarStats(float posX, float gap) {
    for (int i = 0; i < money; i++) {
        modelMatrix = transform2D::Translate(posX + (star_side_small + gap) * i, hud_posy - 75);
        RenderMesh2D(meshes["star_small"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderHUD() {
    for (int i = 0; i < 4; i++) {
        modelMatrix = transform2D::Translate(hud_posx[i], hud_posy);
        RenderMesh2D(meshes["hud_cell"], shaders["VertexColor"], modelMatrix);
        if(money >= prices[i])
            RenderMesh2D(meshes[heroes[i]], shaders["VertexColor"], modelMatrix);
        else
            RenderMesh2D(meshes[heroes[4]], shaders["VertexColor"], modelMatrix);

        // COST
        for (int j = 0; j < prices[i]; j++) {
            modelMatrix = transform2D::Translate(hud_posx[i] - 50 + 50 * j, hud_posy - 80);
            RenderMesh2D(meshes["star_small"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::RenderResources() {
    for (auto it = resources_vec.begin(); it != resources_vec.end(); ++it) {
        modelMatrix = transform2D::Translate((*it).getPosx(), (*it).getPosy());
        RenderMesh2D(meshes["star_big"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderHeroes() {
    for (auto it = heroes_vec.begin(); it != heroes_vec.end(); ++it) {
        modelMatrix = transform2D::Translate((*it).getPosx(), (*it).getPosy());
        if (!(*it).getIsAlive())
            modelMatrix *= transform2D::Scale((*it).getScale(), (*it).getScale());
        RenderMesh2D(meshes[heroes[(*it).getType()]], shaders["VertexColor"], modelMatrix);
    }

    // Render aux hero
    if (is_buying) {
        modelMatrix = transform2D::Translate(aux_hero.getPosx(), aux_hero.getPosy());
        RenderMesh2D(meshes[heroes[aux_hero.getType()]], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderEnemies() {
    for (auto it = enemies_vec.begin(); it != enemies_vec.end(); ++it) {
        modelMatrix = transform2D::Translate((*it).getPosx(), (*it).getPosy());
        if (!(*it).getIsAlive())
            modelMatrix *= transform2D::Scale((*it).getScale(), (*it).getScale());
        RenderMesh2D(meshes[enemies[(*it).getType()]], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderBullets() {
    for (auto it = bullet_vec.begin(); it != bullet_vec.end(); ++it) {
        modelMatrix = transform2D::Translate((*it).getPosx(), (*it).getPosy());
        modelMatrix *= transform2D::Rotate((*it).getRotation());
        RenderMesh2D(meshes[bullets[(*it).getType()]], shaders["VertexColor"], modelMatrix);
    }
}

// SPAWN
void Tema1::SpawnResource(float posx, float posy) {
    resources_vec.push_back(Resource(posx, posy));
}

void Tema1::SpawnResourcesRandom(float deltaTimeSeconds) {
    time_spawn_stars += deltaTimeSeconds;
    if (time_spawn_stars >= 20.0) {
        int spawn_chance = rand() % 10000;
        if (spawn_chance >= 9980) {
            SpawnResource(rand() % 1281, rand() % 721);
            SpawnResource(rand() % 1281, rand() % 721);
            SpawnResource(rand() % 1281, rand() % 721);
            cout << "Time: " << time_total << ": Spawned 3 stars after " << time_spawn_stars <<" seconds" << endl;
            time_spawn_stars = 0.0f;
        }
    }
}

void Tema1::SpawnEnemy(float posx, float posy, int type, int health) {
    enemies_vec.push_back(Hexaghon(posx, posy, type, health));
    cout << "Time: " << time_total << ": Spawned enemy type " << enemies_vec.back().getType() << " after " << time_spawn_enemy << " seconds" << endl;
    time_spawn_enemy = 0.0f;
}

void Tema1::SpawnEnemyRandom(float deltaTimeSeconds) {
    time_spawn_enemy += deltaTimeSeconds;

    if (time_spawn_enemy >= 10.0) {
        SpawnEnemy(1280, lines_posy[rand() % 3], rand() % 4, 3);
    }
    else {
        int spawn_chance = rand() % 10000;
        if (spawn_chance >= 9990) {
            SpawnEnemy(1280, lines_posy[rand() % 3], rand() % 4, 3);
        }
    }
}

void Tema1::SpawnBullet(float posx, float posy, int type) {
    bullet_vec.push_back(Bullet(posx, posy, type));
    cout << "Time: " << time_total << ": Spawned bullet type " << bullet_vec.back().getType() << endl;
}

// MOVE
void Tema1::UpdateObjectsAttributes(float deltaTimeSeconds) {
    // ENEMIES
    for (auto it = enemies_vec.begin(); it != enemies_vec.end(); ) {
        if ((*it).getIsAlive()) {
            (*it).setPosx((*it).getPosx() - 70 * deltaTimeSeconds);
            ++it;
        }
        else {
            (*it).setScale((*it).getScale() - 5 * deltaTimeSeconds);
            if ((*it).getScale() <= 0.0)
                it = enemies_vec.erase(it);
            else
                ++it;
        }
    }

    // HEROES
    for (auto it = heroes_vec.begin(); it != heroes_vec.end(); ) {
        if ((*it).getIsAlive()) {
            (*it).setTimeLastBullet((*it).getTimeLastBullet() + deltaTimeSeconds);
            ++it;
        }
        else {
            (*it).setScale((*it).getScale() - 5 * deltaTimeSeconds);
            if ((*it).getScale() <= 0.0)
                it = heroes_vec.erase(it);
            else
                ++it;
        }
    }

    // BULLETS
    for (auto it = bullet_vec.begin(); it != bullet_vec.end(); ++it) {
        (*it).setPosx((*it).getPosx() + 800 * deltaTimeSeconds);
        (*it).setRotation((*it).getRotation() - 10 * deltaTimeSeconds);
    }
}

// CHECK
void Tema1::CheckLives() {
    if (lives <= 0)
        exit(1);
}

void Tema1::CheckEnemiesHealth() {
    for (auto it = enemies_vec.begin(); it != enemies_vec.end(); it++) {
        if ((*it).getIsAlive() && ((*it).getHealth() == 0)) {
            cout << "Time: " << time_total << ": Enemy type " << (*it).getType() << " killed" << endl;
            (*it).setIsAlive(false);
            ++kill_bonus_count;
        }
    }
}

void Tema1::CheckFinishLine() {
    for (auto it = enemies_vec.begin(); it != enemies_vec.end(); ) {
        if ((*it).getPosx() <= lines_posx[0]) {
            lives--;
            it = enemies_vec.erase(it);
        }
        else
            ++it;
    }
}

void Tema1::CheckDamage() {
    // CHECK FOR BULLETS TO SPAWN OR HEROES TO DIE
    for (auto it_heroes = heroes_vec.begin(); it_heroes != heroes_vec.end(); ++it_heroes) {
        for (auto it_enemies = enemies_vec.begin(); it_enemies != enemies_vec.end(); ++it_enemies) {
            // CHECK IF SAME LINE
            if((*it_heroes).getLine() == (*it_enemies).getLine() && ((*it_heroes).getPosx() <= (*it_enemies).getPosx() - soldier_side / 2)){
                // IF SAME COLOR, SHOOT
                if (((*it_heroes).getType() == (*it_enemies).getType()) && 
                    (*it_enemies).getIsAlive() && ((*it_heroes).getTimeLastBullet() >= 2.0f )) {
                    SpawnBullet((*it_heroes).getPosx(), (*it_heroes).getPosy(), (*it_heroes).getType());
                    (*it_heroes).setTimeLastBullet(0.0f);
                }
            } // ELSE IF DISTANCE TOO SMALL, KILL HERO
            else if ((*it_heroes).getIsAlive()) {
                float distance = glm::distance(glm::vec2((*it_heroes).getPosx(), (*it_heroes).getPosy()), glm::vec2((*it_enemies).getPosx(), (*it_enemies).getPosy()));
                if (distance <= soldier_side / 2) {
                    (*it_heroes).setIsAlive(false);
                    board_cells[(*it_heroes).getLine()][(*it_heroes).getColumn()] = false;
                    cout << "Time: " << time_total << " Hero died on line " << (*it_heroes).getType() << endl;
                }
            }
        }
    }

    // CHECK IF BULLET HIT SAME COLOR ENEMY
    for (auto it_bullet = bullet_vec.begin(); it_bullet != bullet_vec.end(); ) {
        for (auto it_enemy = enemies_vec.begin(); it_enemy != enemies_vec.end(); ++it_enemy) {
            if ((*it_enemy).getIsAlive() &&
                isEqualFloat((*it_bullet).getPosy(), (*it_enemy).getPosy()) && 
                isEqualFloat((*it_bullet).getType(), (*it_enemy).getType()) &&
                (*it_bullet).getPosx() >= (*it_enemy).getPosx())  {
                    (*it_enemy).setHealth((*it_enemy).getHealth() - 1);
                    cout << "Time: " << time_total << ": Enemy type " << (*it_enemy).getType() << " shot" << endl;
                    it_bullet = bullet_vec.erase(it_bullet);
                    goto end_iteration;
            }
        }

        if ((*it_bullet).getPosx() >= resolution.x) {
            it_bullet = bullet_vec.erase(it_bullet);
            goto end_iteration;
        }

        ++it_bullet;

        end_iteration:
            continue;
    }
}

void Tema1::CheckBonus() {
    if (kill_bonus_count == 5) {
        ++money;
        ++kill_bonus_count;
        cout << "Received bonus 1 star " << endl;
    }
    else if (kill_bonus_count == 11) {
        ++money;
        ++lives;
        cout << "Received bonus 1 star and 1 life" << endl;
        kill_bonus_count = 0;
    }
}

// OTHER
bool Tema1::isEqualFloat(float f1, float f2) {
    return fabs(f1 - f2) <= EPSILON;
}
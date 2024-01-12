#include "lab_m1/tema1/tema1.h"
//#include "lab_m1/tema1/enemy.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/shapes.h"

using namespace std;
using namespace m1;
using namespace shapes;


Tema1::Tema1() { }


Tema1::~Tema1() { }


void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    // MESHES
    enemies.push_back("enemy1");
    enemies.push_back("enemy2");
    enemies.push_back("enemy3");
    enemies.push_back("enemy4");

    heroes.push_back("hero1");
    heroes.push_back("hero2");
    heroes.push_back("hero3");
    heroes.push_back("hero4");
    heroes.push_back("hero_inactive");

    bullets.push_back("bullet1");
    bullets.push_back("bullet2");
    bullets.push_back("bullet3");
    bullets.push_back("bullet4");

    aux_hero = NULL;

    // DIMENSIONS
    board_cell_side = 100;
    board_cell_gap = 50;
    hud_cell_side = 110;
    hud_cell_gap = 20;
    health_side = 80;
    star_side_small = 35;
    star_side_big = 100;
    bullet_side = 50;
    soldier_side = 100;

    // STATS
    lives = 3;
    money = 6;
    kill_bonus_count = 0;
    is_buying = false;
    pause = false;

    // POSITIONS
    lines_posx[0] = 50; // red bar
    lines_posx[1] = lines_posx[0] + (board_cell_side + board_cell_gap) - 20;
    lines_posx[2] = lines_posx[1] + (board_cell_side + board_cell_gap);
    lines_posx[3] = lines_posx[2] + (board_cell_side + board_cell_gap);

    lines_posy[0] = 400;
    lines_posy[1] = lines_posy[0] - (board_cell_side + board_cell_gap);
    lines_posy[2] = lines_posy[1] - (board_cell_side + board_cell_gap);

    hud_posx[0] = 100;
    hud_posx[1] = hud_posx[0] + (hud_cell_side + hud_cell_gap);
    hud_posx[2] = hud_posx[1] + (hud_cell_side + hud_cell_gap);
    hud_posx[3] = hud_posx[2] + (hud_cell_side + hud_cell_gap);

    hud_posy = 650;

    // OTHER
    prices[0] = 1;
    prices[1] = 2;
    prices[2] = 2;
    prices[3] = 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board_cells[i][j] = false;

    // TIME
    time_total = 0.0;
    time_spawn_enemy = 0.0;
    time_spawn_stars = 0.0;

    // THE BOARD
    Mesh* board_cell = CreateRectangle("board_cell", corner, board_cell_side, board_cell_side, glm::vec3(0, 0.75f, 0.4f), true);
    Mesh* finish_line = CreateRectangle("finish_line", corner, board_cell_side / 2, board_cell_side * 3 + 2 * board_cell_gap, glm::vec3(1, 0, 0), true);

    AddMeshToList(board_cell);
    AddMeshToList(finish_line);

    // STARS
    Mesh* star_small = CreateStar("star_small", corner, star_side_small, glm::vec3(0.7f, 0.7f, 0.7f));
    Mesh* star_big = CreateStar("star_big", corner, star_side_big, glm::vec3(1, 0, 1));
   
    AddMeshToList(star_small);
    AddMeshToList(star_big);

    Mesh* bullet1 = CreateStar("bullet1", corner, bullet_side, glm::vec3(1, 0.5, 0)); // ORANGE
    Mesh* bullet2 = CreateStar("bullet2", corner, bullet_side, glm::vec3(0, 0, 1)); // BLUE
    Mesh* bullet3 = CreateStar("bullet3", corner, bullet_side, glm::vec3(1, 1, 0)); // YELLOW
    Mesh* bullet4 = CreateStar("bullet4", corner, bullet_side, glm::vec3(1, 0, 1)); // PINK

    AddMeshToList(bullet1);
    AddMeshToList(bullet2);
    AddMeshToList(bullet3);
    AddMeshToList(bullet4);

    // HEART
    Mesh* heart = CreateRectangle("heart", corner, health_side, health_side, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);

    // HUD
    Mesh* hud_cell = CreateRectangle("hud_cell", corner, hud_cell_side, hud_cell_side, glm::vec3(0, 0, 0), false);
    AddMeshToList(hud_cell);

    // SOLDIERS
    Mesh* hero1 = CreateHero(heroes[0], 1, corner, soldier_side, glm::vec3(1, 0.4, 0)); // ORANGE
    Mesh* hero2 = CreateHero(heroes[1], 2, corner, soldier_side, glm::vec3(0, 0.3, 0.7)); // BLUE
    Mesh* hero3 = CreateHero(heroes[2], 3, corner, soldier_side, glm::vec3(1, 1, 0)); // YELLOW
    Mesh* hero4 = CreateHero(heroes[3], 4, corner, soldier_side, glm::vec3(1, 0, 1)); // PINK
    Mesh* hero5 = CreateHero(heroes[4], 0, corner, soldier_side, glm::vec3(0.2, 0.2, 0.2)); // INACTIVE

    AddMeshToList(hero1);
    AddMeshToList(hero2);
    AddMeshToList(hero3);
    AddMeshToList(hero4);
    AddMeshToList(hero5);

    Mesh* enemy1 = CreateEnemy(enemies[0], 1, corner, soldier_side, glm::vec3(1, 0.4, 0), glm::vec3(1, 0.7, 0)); // ORANGE
    Mesh* enemy2 = CreateEnemy(enemies[1], 2, corner, soldier_side, glm::vec3(0, 0.3, 0.7), glm::vec3(0, 0.5, 0.5)); // BLUE
    Mesh* enemy3 = CreateEnemy(enemies[2], 3, corner, soldier_side, glm::vec3(1, 1, 0), glm::vec3(0, 0.5, 0.5)); // YELLOW
    Mesh* enemy4 = CreateEnemy(enemies[3], 4, corner, soldier_side, glm::vec3(1, 0, 1), glm::vec3(0.5, 0, 1)); // PINK

    AddMeshToList(enemy1);
    AddMeshToList(enemy2);
    AddMeshToList(enemy3);
    AddMeshToList(enemy4);
}


void Tema1::FrameStart() {

    glClearColor(0.15f, 0.15f, 0.15f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds) {

    CheckLives();

    RenderBoard();
    RenderHUD();
    RenderStarStats(825, 10);
    RenderHealthBar(850, 25);

    RenderEnemies();
    RenderHeroes();
    RenderBullets();
    RenderResources();

    if (pause) return;

    time_total += deltaTimeSeconds;

    UpdateObjectsAttributes(deltaTimeSeconds);

    SpawnEnemyRandom(deltaTimeSeconds);
    SpawnResourcesRandom(deltaTimeSeconds);

    CheckDamage();
    CheckEnemiesHealth();
    CheckFinishLine();
    CheckBonus();
}


void Tema1::FrameEnd() { }


void Tema1::OnInputUpdate(float deltaTime, int mods) { }


void Tema1::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_P) {
        pause = !pause;

        if (pause)
            cout << "Paused game" << endl;
        else
            cout << "Unpaused game" << endl;
    }
}


void Tema1::OnKeyRelease(int key, int mods) { }


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    if (is_buying) {
        aux_hero.setPos(mouseX, resolution.y - mouseY);
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (button == 1) {
        // CHECK CLICK IN HUD
        if ((mouseY >= resolution.y - hud_posy - hud_cell_side / 2) && (mouseY <= resolution.y - hud_posy + hud_cell_side / 2)) {
            for (int i = 0; i < 4; i++) {
                if ((mouseX >= hud_posx[i] - hud_cell_side / 2) && (mouseX <= hud_posx[i] + hud_cell_side / 2)) {
                    is_buying = true;
                    aux_hero = Rhombus(mouseX, resolution.y - mouseY, i);
                    if (prices[i] > money) {
                        is_buying = false;
                        cout << "Not enough money, you need " << prices[i] << " stars" << endl;
                    }
                    break;
                }   
            }
        }
        // CHECK CLICK ON RESOURCES
        for (auto it = resources_vec.begin(); it != resources_vec.end(); ) {
            if ((mouseX >= (*it).getPosx() - star_side_big / 2) && (mouseX <= (*it).getPosx() + star_side_big / 2) &&
                (mouseY >= resolution.y - (*it).getPosy() - star_side_big / 2) && (mouseY <= resolution.y - (*it).getPosy() + star_side_big / 2)) {
                money++;
                it = resources_vec.erase(it);
                continue;
            }
            ++it;
        }
    }
    else if (button == 2) {
        for (int i = 0; i < 3; i++) {
            if ((mouseX >= lines_posx[i + 1] - board_cell_side / 2) && (mouseX <= lines_posx[i + 1] + board_cell_side / 2)) {
                for (int j = 0; j < 3; j++) {
                    if ((mouseY >= resolution.y - lines_posy[j] - board_cell_side / 2) && (mouseY <= resolution.y - lines_posy[j] + board_cell_side / 2)) {
                        for (auto it_heroes = heroes_vec.begin(); it_heroes != heroes_vec.end(); ) {
                            if (isEqualFloat((*it_heroes).getPosx(), lines_posx[i + 1]) && isEqualFloat((*it_heroes).getPosy(), lines_posy[j])) {
                                money += prices[(*it_heroes).getType()] / 2;
                                it_heroes = heroes_vec.erase(it_heroes);
                                board_cells[j][i] = false;
                                continue;
                            }
                            ++it_heroes;
                        }
                    }
                }
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    if (button == 1) {
        //CHECK IF WE WERE CARRYING A HERO
        if (!is_buying) return;

        is_buying = false;
        // CHECK IF RELEASED ON VALID CELL
        for (int i = 0; i < 3; i++) {
            if ((mouseY >= resolution.y - lines_posy[i] - board_cell_side / 2) && (mouseY <= resolution.y - lines_posy[i] + board_cell_side / 2)) {
                for (int j = 0; j < 3; j++) {
                    if ((mouseX >= lines_posx[j + 1] - board_cell_side / 2) && (mouseX <= lines_posx[j + 1] + board_cell_side / 2)) {
                        if (board_cells[i][j])
                            cout << "Can't place hero on already occupied cell" << endl;
                        else {
                            cout << "Time: " << time_total << ": Placed hero on line " << i << " column " << j << endl;
                            heroes_vec.push_back(Rhombus(lines_posx[j + 1], lines_posy[i], aux_hero.getType()));
                            money -= prices[aux_hero.getType()];
                            board_cells[i][j] = true;
                        }
                       break;
                    }
                }
            }
        }
        aux_hero = NULL;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
    // Treat mouse scroll event
}


void Tema1::OnWindowResize(int width, int height) {
    // Treat window resize event
}


scene = {
    -- Tabla de sprites e imagenes
    sprites = {
        [0] =
        {assetId = "enemy_alan", filePath = "./assets/images/enemy_alan.png"},
        {assetId = "player_ship", filePath = "./assets/images/player_ship.png"},
        {assetId = "terrain_tile_77", filePath = "./assets/terrain/Zombie-Tileset---_0077_Capa-78.png"},
        {assetId = "terrain_tile_78", filePath = "./assets/terrain/Zombie-Tileset---_0078_Capa-79.png"},
        {assetId = "terrain_tile_79", filePath = "./assets/terrain/Zombie-Tileset---_0079_Capa-80.png"},
        {assetId = "terrain_tile_80", filePath = "./assets/terrain/Zombie-Tileset---_0080_Capa-81.png"},
        {assetId = "player_idle_up", filePath = "./assets/gun/Idle/Character_up_idle_no_hands.png"},
        {assetId = "player_idle_side", filePath = "./assets/gun/Idle/Character_side_idle_no_hands.png"},
        {assetId = "player_idle_side_left", filePath = "./assets/gun/Idle/Character_side-left_idle_no_hands.png"},
        {assetId = "player_idle_down", filePath = "./assets/gun/Idle/Character_down_idle_no_hands.png"},
        {assetId = "player_run_up", filePath = "./assets/gun/Run/Character_up_run_no_hands.png"},
        {assetId = "player_run_side", filePath = "./assets/gun/Run/Character_side_run_no_hands.png"},
        {assetId = "player_run_side_left", filePath = "./assets/gun/Run/Character_side-left_run_no_hands.png"},
        {assetId = "player_run_down", filePath = "./assets/gun/Run/Character_down_run_no_hands.png"},
        -- Zombie sprites
        {assetId = "zombie_idle_up", filePath = "./assets/zombie_small/walk/Zombie_Small_Up_Walk-Sheet6.png"},
        {assetId = "zombie_idle_side", filePath = "./assets/zombie_small/walk/Zombie_Small_Side_Walk-Sheet6.png"},
        {assetId = "zombie_idle_side_left", filePath = "./assets/zombie_small/walk/Zombie_Small_Side-left_Walk-Sheet6.png"},
        {assetId = "zombie_idle_down", filePath = "./assets/zombie_small/walk/Zombie_Small_Down_walk-Sheet6.png"},
        -- Zombie attack sprites
        {assetId = "zombie_attack_up", filePath = "./assets/zombie_small/attack1/Zombie_Small_Up_First-Attack-Sheet4.png"},
        {assetId = "zombie_attack_side", filePath = "./assets/zombie_small/attack1/Zombie_Small_Side_First-Attack-Sheet4.png"},
        {assetId = "zombie_attack_side_left", filePath = "./assets/zombie_small/attack1/Zombie_Small_Side-left_First-Attack-Sheet4.png"},
        {assetId = "zombie_attack_down", filePath = "./assets/zombie_small/attack1/Zombie_Small_Down_First-Attack-Sheet4.png"},
        -- Firing sprites (muzzle flash animation)
        {assetId = "fire_up", filePath = "./assets/firing/Fire_Up-Sheet3.png"},
        {assetId = "fire_side", filePath = "./assets/firing/Fire_side-Sheet3.png"},
        {assetId = "fire_side_left", filePath = "./assets/firing/Fire_side-left-Sheet3.png"},
        {assetId = "fire_down", filePath = "./assets/firing/Fire_Down-Sheet3.png"},
        -- Bullet sprite
        {assetId = "bullet", filePath = "./assets/bullets/Pistol-bullet_Bullet.png"},
        -- Containers para decoración de bordes
        {assetId = "container_gray_v", filePath = "./assets/building/Container_1_Gray_Vertical.png"},
        {assetId = "container_gray_bleak_v", filePath = "./assets/building/Container_2_Gray_Vertical_Overgrown_Bleak-Yellow.png"},
        {assetId = "container_gray_h", filePath = "./assets/building/Container_3_Gray_Horizontal.png"},
        {assetId = "container_gray_bleak_h", filePath = "./assets/building/Container_4_Gray_Horizontal_Overgrown_Bleak-Yellow.png"},
        {assetId = "container_green_bleak_v", filePath = "./assets/building/Container_10_Green_Vertical_Overgrown_Bleak-Yellow.png"},
        {assetId = "container_green_h", filePath = "./assets/building/Container_11_Green_Horizontal.png"},
        {assetId = "container_green_bleak_h", filePath = "./assets/building/Container_12_Green_Horizontal_Overgrown_Bleak-Yellow.png"},
        {assetId = "container_green_v", filePath = "./assets/building/Container_9_Green_Vertical.png"},
    },

    -- Tabla de fuentes
    fonts = {
        [0] =
        {fontId = "press_start_11", filePath = "./assets/fonts/PressStart2P-Regular.ttf", fontSize = 11,}
    },

    -- Tabla de acciones y teclas
    keys = {
        [0] = 
        {name = "up", key = 119},
        {name = "left", key = 97},
        {name = "down", key = 115},
        {name = "right", key = 100},
        {name = "shoot", key = 106},
        {name = "pause", key = 112},
    },

    -- Tabla de acciones y botones
    buttons = {
        [0] = 
        {name = "mouse_left_button", button = 1}
    },

    -- Tabla de entidades
    entities = {},
}

-- Generar grid de terreno que llena toda la pantalla
-- Ventana 800x600, tiles 16x16 = 50x37.5 tiles (50x38)
local tileSize = 16
local terrains = {"terrain_tile_77", "terrain_tile_78", "terrain_tile_79", "terrain_tile_80"}
local tilesX = 50
local tilesY = 38
local entityIndex = 0
local terrainIndex = 1

for y = 0, tilesY - 1 do
    for x = 0, tilesX - 1 do
        -- Distribución ponderada: 77 y 78 predominan (40% cada uno), 79 y 80 son minoría (10% cada uno)
        local rand = math.random()
        local terrainAsset
        
        if rand < 0.4 then
            terrainAsset = terrains[1] -- terrain_tile_77 (40%)
        elseif rand < 0.8 then
            terrainAsset = terrains[2] -- terrain_tile_78 (40%)
        elseif rand < 0.9 then
            terrainAsset = terrains[3] -- terrain_tile_79 (10%)
        else
            terrainAsset = terrains[4] -- terrain_tile_80 (10%)
        end
        
        scene.entities[entityIndex] = {
            components = {
                sprite = {
                    assetId = terrainAsset,
                    width = tileSize,
                    height = tileSize,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = x * tileSize, y = y * tileSize},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        }
        entityIndex = entityIndex + 1
    end
end

-- Player
scene.entities[entityIndex] = {
            components = {       
                animation = {
                    num_frames = 6,
                    speed_rate = 10,
                    is_loop = true,
                },      
                circle_collider = {
                    radius = 8,
                    width = 16,
                    height = 16,
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                health = {
                    max_health = 10,
                    current_health = 10,
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "player_idle_down",
                    width = 16,
                    height = 16,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 400, y = 300},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                }
            }
        }
        
entityIndex = entityIndex + 1

-- HUD - Texto de vida
scene.entities[entityIndex] = {
    components = {
        text = {
            text = "HP: 10",
            fontId = "press_start_11",
            r = 255,
            g = 255,
            b = 255,
            a = 255,
        },
        visible = {
            value = true
        },
        script = {
            path = "./assets/scripts/hud.lua"
        },
        transform = {
            position = {x = 10, y = 10},
            scale = {x = 1.0, y = 1.0},
            rotation = 0.0,
        }
    }
}

entityIndex = entityIndex + 1

scene.entities[entityIndex] = {
    components = {
        script = {
            path = "./assets/scripts/wave_manager.lua"
        }
    }
}

entityIndex = entityIndex + 1

scene.entities[entityIndex] = {
    components = {
        text = {
            text = "GAME OVER",
            fontId = "press_start_11",
            r = 255,
            g = 0,
            b = 0,
            a = 255,
        },
        visible = {
            value = false
        },
        script = {
            path = "./assets/scripts/game_over_text.lua"
        },
        transform = {
            position = {x = 280, y = 220},
            scale = {x = 1.0, y = 1.0},
            rotation = 0.0,
        }
    }
}

entityIndex = entityIndex + 1

scene.entities[entityIndex] = {
    components = {
        clickable = {},
        text = {
            text = "Restart",
            fontId = "press_start_11",
            r = 255,
            g = 255,
            b = 255,
            a = 255,
        },
        visible = {
            value = false
        },
        script = {
            path = "./assets/scripts/restart_button.lua"
        },
        transform = {
            position = {x = 300, y = 300},
            scale = {x = 1.0, y = 1.0},
            rotation = 0.0,
        }
    }
}

entityIndex = entityIndex + 1

scene.entities[entityIndex] = {
    components = {
        clickable = {},
        text = {
            text = "Menu",
            fontId = "press_start_11",
            r = 255,
            g = 255,
            b = 255,
            a = 255,
        },
        visible = {
            value = false
        },
        script = {
            path = "./assets/scripts/menu_button_gameover.lua"
        },
        transform = {
            position = {x = 300, y = 350},
            scale = {x = 1.0, y = 1.0},
            rotation = 0.0,
        }
    }
}

entityIndex = entityIndex + 1
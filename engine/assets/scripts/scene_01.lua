scene = {
    -- Tabla de sprites e imagenes
    sprites = {
        [0] =
        {assetId = "enemy_alan", filePath = "./assets/images/enemy_alan.png"},
        {assetId = "player_ship", filePath = "./assets/images/player_ship.png"},
    },

    -- Tabla de fuentes
    fonts = {
        [0] =
        {fontId = "press_start", filePath = "./assets/fonts/PressStart2P-Regular.ttf", fontSize = 24,}
    },

    -- Tabla de acciones y teclas
    keys = {
        [0] = 
        {name = "up", key = 119},
        {name = "left", key = 97},
        {name = "down", key = 115},
        {name = "right", key = 100},
    },

    -- Tabla de acciones y botones
    buttons = {
        [0] = 
        {name = "mouse_left_button", button = 1}
    },

    -- Tabla de entidades
    entities = {
        [0] = 
        -- Player
        {
            components = {                
                circle_collider = {
                    radius = 8,
                    width = 16,
                    height = 16,
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "player_ship",
                    width = 16,
                    height = 16,
                    src_rect = {x = 16, y = 0},
                },
                transform = {
                    position = {x = 400, y = 300},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                }
            }
        },
        {
            components = {
                clickable = {},
                text = {
                    text = "Score: 100",
                    fontId = "press_start",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 500.0, y = 50.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
    }
}
scene = {
    -- Tabla de sprites e imagenes
    sprites = {},

    -- Tabla de fuentes
    fonts = {
        [0] =
        {fontId = "press_start_24", filePath = "./assets/fonts/PressStart2P-Regular.ttf", fontSize = 24,},
        {fontId = "press_start_32", filePath = "./assets/fonts/PressStart2P-Regular.ttf", fontSize = 32,}
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
        {
            components = {
                clickable = {},
                text = {
                    text = "zombiE gunN",
                    fontId = "press_start_32",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 50.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        {
            components = {
                clickable = {},
                script = {
                    path = "./assets/scripts/menu_button_01.lua",
                },
                text = {
                    text = "Jugar",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 150.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        {
            components = {
                clickable = {},
                text = {
                    text = "muevase con WASD",
                    fontId = "press_start_24",
                    r = 200,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 300.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        {
            components = {
                clickable = {},
                text = {
                    text = "dispare con J",
                    fontId = "press_start_24",
                    r = 200,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 350.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },{
            components = {
                clickable = {},
                text = {
                    text = "cierre el juego con ESC",
                    fontId = "press_start_24",
                    r = 200,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 400.0},
                    scale  = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
    }
}
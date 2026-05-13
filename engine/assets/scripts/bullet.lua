-- Crear un sistema de bullets si no existe
if not BULLET_SYSTEM then
    BULLET_SYSTEM = {
        counter = 0,
        states = {}
    }
end

-- Asignar un ID único a esta bala
BULLET_SYSTEM.counter = BULLET_SYSTEM.counter + 1
local bullet_id = BULLET_SYSTEM.counter

-- Inicializar el estado de esta bala
-- El script que crea la bala debe establecer velocity antes de ejecutar update
BULLET_SYSTEM.states[bullet_id] = {
    velocity_x = 0,
    velocity_y = 0,
    speed = 300,
    lifetime = 0,
    max_lifetime = 5000  -- 5 segundos máximo
    
}

local my_state = BULLET_SYSTEM.states[bullet_id]

function update()
    -- Obtener posición actual
    local pos = get_position(this)
    
    -- Establecer velocidad basada en el estado global (se configura desde el jugador)
    -- local player_direction = _G["player_direction"]
    
    -- if player_direction == "up" then
    --     my_state.velocity_x = 0
    --     my_state.velocity_y = -my_state.speed
    -- elseif player_direction == "down" then
    --     my_state.velocity_x = 0
    --     my_state.velocity_y = my_state.speed
    -- elseif player_direction == "side" then
    --     my_state.velocity_x = my_state.speed
    --     my_state.velocity_y = 0
    -- elseif player_direction == "side_left" then
    --     my_state.velocity_x = -my_state.speed
    --     my_state.velocity_y = 0
    -- end
    
    -- set_velocity(this, my_state.velocity_x, my_state.velocity_y)
    
    -- Incrementar tiempo de vida
    my_state.lifetime = my_state.lifetime + 16  -- ~16ms per frame at 60fps
    
    -- Eliminar si pasó el máximo tiempo
    if my_state.lifetime > my_state.max_lifetime then
        this:kill()
        return
    end
    
    -- Eliminar si sale del mapa (800x600)
    if pos.x <= 0 or pos.x >= 792 or pos.y <= 0 or pos.y >= 592 then
        this:kill()
        return
    end
end

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

-- Inicializar el estado de esta bala con su propio ID capturado
BULLET_SYSTEM.states[bullet_id] = {
    bullet_id = bullet_id,
    velocity_x = 0,
    velocity_y = 0,
    speed = 300,
    lifetime = 0,
    max_lifetime = 5000  -- 5 segundos máximo
}

-- Capturar el ID de forma segura en una closure
local my_bullet_id = bullet_id

function update()
    -- Usar el ID específico de esta bala
    local my_state = BULLET_SYSTEM.states[my_bullet_id]
    if not my_state then
        this:kill()
        return
    end
    
    -- Obtener posición actual
    local pos = get_position(this)
    
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

-- Crear un sistema de estados para zombies si no existe
if not ZOMBIE_SYSTEM then
    ZOMBIE_SYSTEM = {
        counter = 0,
        states = {}
    }
end

-- Asignar un ID único a este zombie
ZOMBIE_SYSTEM.counter = ZOMBIE_SYSTEM.counter + 1
local zombie_id = ZOMBIE_SYSTEM.counter

-- Inicializar el estado de este zombie
ZOMBIE_SYSTEM.states[zombie_id] = {
    velocity = 80,
    direction = "down",
    last_attack_time = 0,
    is_attacking = false
}

local my_state = ZOMBIE_SYSTEM.states[zombie_id]

function get_direction_to_player(zombie_pos, player_pos)
    local dx = player_pos.x - zombie_pos.x
    local dy = player_pos.y - zombie_pos.y
    
    if math.abs(dy) > math.abs(dx) then
        if dy < 0 then
            return "up"
        else
            return "down"
        end
    else
        if dx < 0 then
            return "side_left"
        else
            return "side"
        end
    end
end

function get_velocity_towards_player(zombie_pos, player_pos, speed)
    local dx = player_pos.x - zombie_pos.x
    local dy = player_pos.y - zombie_pos.y
    
    local distance = math.sqrt(dx * dx + dy * dy)
    
    if distance < 1 then
        return 0, 0
    end
    
    local vel_x = (dx / distance) * speed
    local vel_y = (dy / distance) * speed
    
    return vel_x, vel_y
end

function change_zombie_animation(direction)
    local anim_name = "zombie_idle_" .. direction
    change_animation(this, anim_name, 6, 10, true)
end

function change_zombie_attack_animation(direction)
    local anim_name = "zombie_attack_" .. direction
    change_animation(this, anim_name, 4, 10, false)
end

function update()
    local player_pos = _G["player_position"]
    
    if player_pos == nil then
        set_velocity(this, 0, 0)
        return
    end
    
    local zombie_pos = get_position(this)
    local new_direction = get_direction_to_player(zombie_pos, player_pos)
    local vel_x, vel_y = get_velocity_towards_player(zombie_pos, player_pos, my_state.velocity)
    
    -- Calcular distancia al jugador
    local dx = player_pos.x - zombie_pos.x
    local dy = player_pos.y - zombie_pos.y
    local distance = math.sqrt(dx * dx + dy * dy)
    
    -- Distancia de ataque: ancho del sprite escalado (16 * 2.0 = 32)
    local attack_range = 32
    local current_time = os.clock()
    
    -- Verificar si el zombie debe atacar
    if distance < attack_range and (current_time - my_state.last_attack_time) >= 2.0 then
        -- Ejecutar ataque
        my_state.is_attacking = true
        my_state.last_attack_time = current_time
        
        -- Cambiar a animación de ataque
        change_zombie_attack_animation(new_direction)
        
        -- Frenar el movimiento durante el ataque
        set_velocity(this, 0, 0)
        
        -- TODO: Aplicar daño al jugador si está en el rango de ataque
        -- TODO: Considerar si el daño debe ser direccional (solo si está frente al zombie)
    else        
        -- No atacar, volver a movimiento normal
        if my_state.is_attacking then
            my_state.is_attacking = false
            change_zombie_animation(new_direction)
        end
        
        set_velocity(this, vel_x, vel_y)
        
        if new_direction ~= my_state.direction then
            my_state.direction = new_direction
            change_zombie_animation(my_state.direction)
        end
    end
end

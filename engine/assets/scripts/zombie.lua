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
    velocity = 40,
    direction = "down",
    last_attack_time = -3000,  -- Iniciar en pasado negativo para permitir primer ataque inmediato
    is_attacking = false,
    attack_start_time = 0,
    attack_duration = 500,  -- Duración de la animación de ataque en ms
    damage_applied = false  -- Para evitar aplicar daño múltiples veces por ataque
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

function is_facing_player(zombie_pos, player_pos, zombie_direction)
    local dx = player_pos.x - zombie_pos.x
    local dy = player_pos.y - zombie_pos.y
    
    if zombie_direction == "up" then
        return dy < 0
    elseif zombie_direction == "down" then
        return dy > 0
    elseif zombie_direction == "side_left" then
        return dx < 0
    elseif zombie_direction == "side" then
        return dx > 0
    end
    
    return false
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
    local attack_range = 35
    local current_time = get_time_miliseconds()
  
    -- Si está atacando actualmente, mantener la animación de ataque hasta que termine
    if my_state.is_attacking then
        set_velocity(this, 0, 0)
        
        -- Aplicar daño al jugador si está en rango y mirando hacia él
        if not my_state.damage_applied then
            local player_entity = _G["player_entity"]
            if player_entity ~= nil and is_facing_player(zombie_pos, player_pos, my_state.direction) then
                damage_entity(player_entity, 1)
                my_state.damage_applied = true
                print("[ZOMBIE] Aplicó daño. Salud del jugador: " .. get_health(player_entity))
            end
        end
        
        -- Verificar si la animación de ataque ha terminado
        if (current_time - my_state.attack_start_time) >= my_state.attack_duration then
            my_state.is_attacking = false
            my_state.damage_applied = false  -- Reset para el próximo ataque
            -- Volver a animación de movimiento
            change_zombie_animation(new_direction)
            my_state.direction = new_direction
        end
    -- Verificar si debería iniciar un nuevo ataque
    elseif distance < attack_range and (current_time - my_state.last_attack_time) >= 2000 then
        -- Iniciar ataque
        my_state.is_attacking = true
        my_state.attack_start_time = current_time
        my_state.last_attack_time = current_time
        my_state.damage_applied = false  -- Reset flag para este nuevo ataque
        change_zombie_attack_animation(new_direction)
        set_velocity(this, 0, 0)
    -- Movimiento normal si no está atacando
    else
        set_velocity(this, vel_x, vel_y)
        
        if new_direction ~= my_state.direction then
            my_state.direction = new_direction
            change_zombie_animation(my_state.direction)
        end
    end
end

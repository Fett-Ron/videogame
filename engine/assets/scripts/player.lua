-- Variables Globales
player_velocity = 150;
fixed_player_velocity = math.sqrt((player_velocity * player_velocity) / 2)

-- Variables de estado (locales para esta instancia)
local current_direction = "down"
local current_state = "idle"  -- "idle" o "run"
local last_shot_time = -1000  -- Para cooldown de disparo
local shoot_cooldown = 200    -- Milisegundos entre disparos

function get_direction(vel_x, vel_y)
    -- Determinar dirección basada en velocidad
    if vel_y < 0 then
        return "up"
    elseif vel_y > 0 then
        return "down"
    elseif vel_x < 0 then
        return "side_left"
    else  -- vel_x > 0
        return "side"
    end
end

function change_player_animation(direction, state)
    local anim_name = "player_" .. state .. "_" .. direction
    local speed_rate = 10
    
    if state == "run" then
        speed_rate = 15  -- Animación de correr más rápida
    end
    
    change_animation(this, anim_name, 6, speed_rate, true)
end

function get_fire_offset(direction)
    -- Retorna el offset x, y para la posición de la bala según la dirección
    if direction == "up" then
        return 16, 0
    elseif direction == "down" then
        return 16, 16
    elseif direction == "side" then
        return 16, 16
    elseif direction == "side_left" then
        return 0, 16
    end
    return 0, 0
end

function update()
    -- Exponer posición global para otros scripts
    _G["player_entity"] = this
    local pos = get_position(this)
    _G["player_position"] = pos
    _G["player_direction"] = current_direction  -- Exponer dirección para las balas
    
    set_velocity(this, 0, 0);
    vel_x = 0
    vel_y = 0

    if is_action_activated("up") then
        vel_y = vel_y + -1
    end
    if is_action_activated("left") then
        vel_x = vel_x + -1
    end
    if is_action_activated("down") then
        vel_y = vel_y + 1
    end
    if is_action_activated("right") then
        vel_x = vel_x + 1
    end

    if vel_x ~= 0 and vel_y ~=0 then
        vel_x = vel_x * fixed_player_velocity
        vel_y = vel_y * fixed_player_velocity
    else
        vel_x = vel_x * player_velocity
        vel_y = vel_y * player_velocity
    end

    set_velocity(this, vel_x, vel_y)
    
    -- Determinar estado (idle o run) y dirección
    local new_state = "idle"
    local new_direction = current_direction
    
    if vel_x ~= 0 or vel_y ~= 0 then
        new_state = "run"
        new_direction = get_direction(vel_x, vel_y)
    else
        new_state = "idle"
    end
    
    -- Cambiar animación si el estado o dirección cambió
    if new_state ~= current_state or new_direction ~= current_direction then
        current_state = new_state
        current_direction = new_direction
        change_player_animation(current_direction, current_state)
    end
    
    -- Manejar disparo (J)
    if is_action_activated("shoot") then
        local current_time = get_time_miliseconds()
        if (current_time - last_shot_time) >= shoot_cooldown then
            -- Crear bala
            local offset_x, offset_y = get_fire_offset(current_direction)
            local bullet_x = pos.x + offset_x
            local bullet_y = pos.y + offset_y
            
            create_bullet(bullet_x, bullet_y, current_direction)
            play_gunshot_sound()
            -- Mostrar animación de disparo
            --local fire_anim = "fire_" .. current_direction
            --change_animation(this, fire_anim, 3, 10, false)
            
            last_shot_time = current_time
            
            -- Después de mostrar la animación de disparo, volver a la animación normal
            -- Esto se manejaría en un siguiente frame
        end
    end
end


-- Variables Globales
player_velocity = 150;
fixed_player_velocity = math.sqrt((player_velocity * player_velocity) / 2)

-- Variables de estado
current_direction = "down"
current_state = "idle"  -- "idle" o "run"

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

function update()
    set_velocity(this, 0, 0);
    vel_x = 0
    vel_y = 0

    if is_action_activated("up") then
        vel_y = vel_y + -1
        print("up")
    end
    if is_action_activated("left") then
        vel_x = vel_x + -1
        print("left")
    end
    if is_action_activated("down") then
        vel_y = vel_y + 1
        print("down")
    end
    if is_action_activated("right") then
        vel_x = vel_x + 1
        print("right")
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
end

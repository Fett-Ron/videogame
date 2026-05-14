function update()

    local player_entity =
        _G["player_entity"]

    if player_entity == nil then
        return
    end

    local current_health =
        get_health(player_entity)

    -- GAME OVER
    if current_health <= 0 then
        
        set_visible(_G["game_over_title"], true)        
        set_visible(_G["restart_button"], true)        
        set_visible(_G["menu_button"], true)
        set_game_over(true)
    end

    local current_wave =
        _G["current_wave"] or 1

    local wave_total_zombies =
        _G["wave_total_zombies"] or 0

    local total_zombies_killed =
        _G["total_zombies_killed"] or 0

    local alive_zombies =
        get_alive_zombies()

    local text =
        "HP: " .. current_health ..
        " | STAGE: " .. current_wave ..
        " | WAVE ZOMBIES: " ..
        wave_total_zombies ..
        " | ALIVE: " ..
        alive_zombies ..
        " | TOTAL KILLS: " ..
        total_zombies_killed

    set_text(this, text)
end
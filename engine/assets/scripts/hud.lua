-- HUD Script - Actualiza la información en pantalla
function update()
    local player_entity = _G["player_entity"]
    
    if player_entity ~= nil then
        local current_health = get_health(player_entity)
        local text = "HP: " .. current_health
        set_text(this, text)
    end
end

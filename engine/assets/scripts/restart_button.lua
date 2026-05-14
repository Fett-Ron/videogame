function update()

    _G["restart_button"] = this

    if is_game_over() then
        set_text_color(this, 255, 255, 255, 255)
    else
        set_text_color(this, 255, 255, 255, 0)
    end
end

function on_click()

    if is_game_over() then
        set_game_over(false)
        go_to_scene("level_01")
    end
end
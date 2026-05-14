function update()
    _G["menu_button"] = this
    if is_game_over() then
        set_text_color(this, 255, 255, 255, 255)
    else
        set_text_color(this, 255, 255, 255, 0)
    end
end

function on_click()

    if is_game_over() then
        set_game_over(false)
        go_to_scene("main_menu")
    end
end
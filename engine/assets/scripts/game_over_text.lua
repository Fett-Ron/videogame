function update()
    _G["game_over_title"] = this

    if is_game_over() then
        set_text_color(this, 255, 0, 0, 255)
    else
        set_text_color(this, 255, 0, 0, 0)
    end
end
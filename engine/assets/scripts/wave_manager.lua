current_wave = 1

local zombies_to_spawn = 0
local zombies_spawned = 0

local spawn_delay = 500
local next_spawn_time = 0

local waiting_next_wave = false
local next_wave_time = 0

local wave_break = 4000

local corners = {
    {x = 50, y = 50},
    {x = 700, y = 50},
    {x = 50, y = 500},
    {x = 700, y = 500}
}

function calculate_wave_size(wave)

    local amount =
        math.floor(
            4 * (1.5 ^ (wave - 1))
        )

    if amount > 50 then
        amount = 50
    end

    return amount
end

function start_wave()

    zombies_to_spawn =
        calculate_wave_size(current_wave)

    zombies_spawned = 0

    next_spawn_time =
        get_time_miliseconds()

    print("Wave: " .. current_wave)
    print("Zombies: " .. zombies_to_spawn)
end

function update()

    local current_time =
        get_time_miliseconds()

    -- spawn gradual
    if zombies_spawned < zombies_to_spawn then

        if current_time >= next_spawn_time then

            local corner =
                corners[
                    (zombies_spawned % 4) + 1
                ]

            spawn_zombie(
                corner.x,
                corner.y
            )

            zombies_spawned =
                zombies_spawned + 1

            next_spawn_time =
                current_time + spawn_delay
        end
    end

    -- esperar siguiente wave
    if zombies_spawned >= zombies_to_spawn and
       get_alive_zombies() <= 0 then

        if not waiting_next_wave then

            waiting_next_wave = true

            next_wave_time =
                current_time + wave_break
        end
    end

    -- iniciar siguiente wave
    if waiting_next_wave and
       current_time >= next_wave_time then

        current_wave =
            current_wave + 1

        waiting_next_wave = false

        start_wave()
    end
end

start_wave()
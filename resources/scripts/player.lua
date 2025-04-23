local player_id = 1
local bullet_id = 2

function start()
    -- initialize network component;
    -- CreateServer or CreateClient
end

local players = {}
local online = 0

function OnClientConnected()
    print("HELLO NEW CLIENT!")
    table.insert(players, Entity.Copy(player_id, { 100, 200 }, 0, 0))
end

function OnClientDisconnected()
    for index, uuid in ipairs(players) do
        Entity.Destroy(uuid)
    end
end

local colddown = 0.5 -- Время до следующего выстрела
local colddown_timer = colddown

local bullet_speed = 1;
local bullets = {}
local bullet_count = 0
local max_impulse = 0.5
local angle_impulse = 0
local max_angle_impulse = 25
local radians = 0
local current_speed = 0
local speed = 5
local boost = 0
local impulse = 0

function update(dt)

    if(Input.IsKeyPressed(Input.Key_A())) then
        if angle_impulse >= -max_angle_impulse then
            angle_impulse = angle_impulse - dt * speed
        end
    else
        if angle_impulse < dt then
            angle_impulse = angle_impulse + dt * speed;
        end
    end
    if(Input.IsKeyPressed(Input.Key_D())) then
        if angle_impulse <= max_angle_impulse then
            angle_impulse = angle_impulse + dt * speed
        end
    else
        if angle_impulse > dt then
            angle_impulse = angle_impulse - dt * speed;
        end
    end

    if colddown_timer <= colddown then
        colddown_timer = colddown_timer + dt
    end
    if Input.IsKeyPressed(Input.Key_Space()) then
        if(colddown_timer >= colddown) then
            if bullet_count > 0 then
                for i,v in ipairs(bullets) do
                    table.remove(bullets, i)
                    Entity.Destroy(v)
                    bullet_count = bullet_count - 1
                end
            end
            table.insert(bullets, Entity.Copy(bullet_id, Entity.GetPosition(player_id), Entity.GetRotation(player_id)))
            bullet_count = bullet_count + 1
            colddown_timer = 0
        end
    end

    if(Input.IsKeyPressed(Input.Key_W())) then
        if(impulse <= max_impulse) then
            impulse = impulse + dt
            radians = math.rad(Entity.GetRotation(player_id))
        end
    else
        if impulse >= dt then
            impulse = impulse - dt
        end
    end
    boost = impulse / dt
    local moveX = math.sin(radians) * boost
    local moveY = -math.cos(radians) * boost
    Entity.Move(player_id, moveX, moveY)
    Entity.Rotate(player_id, angle_impulse)

    local bullet_boost = bullet_speed / dt
    for index, id in ipairs(bullets) do
        radians = math.rad(Entity.GetRotation(id))
        Entity.Move(id, math.sin(radians) * bullet_boost, -math.cos(radians) * bullet_boost)
    end
end
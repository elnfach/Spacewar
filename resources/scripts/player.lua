local player_id = 1
local bullet_id = 2

local players = {}
local online = 0

-- Network
local difference = 0.0
local position = { x = 0, y = 0 }
local rotation = 0.0
local scale = { x = 0, y = 0 }
local network_transform_sensitivity = 0.1

local colddown = 0.5 -- Время до следующего выстрела
local colddown_timer = colddown

local max_impulse = 0.5
local angle_impulse = 0
local max_angle_impulse = 25
local radians = 0
local speed = 5
local boost = 0
local impulse = 0

function update(dt)
    difference = math.abs((transform.position.x - position.x) + (transform.position.y - position.y) + (transform.rotation - rotation) + (transform.scale.x - scale.x) + (transform.scale.y - scale.y))
    if (difference > network_transform_sensitivity) then
        position = transform.position
        rotation = transform.rotation
        scale = transform.scale
        network:Send(transform.position, transform.rotation, transform.scale)
    end
    if(input:IsKeyPressed(input.key.a)) then
        if angle_impulse >= -max_angle_impulse then
            angle_impulse = angle_impulse - dt * speed
        end
    else
        if angle_impulse < dt then
            angle_impulse = angle_impulse + dt * speed;
        end
    end
    if(input:IsKeyPressed(input.key.d)) then
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
    if input:IsKeyPressed(input.key.space) then
        if(colddown_timer >= colddown) then
            Entity.Copy(bullet_id, Entity.GetPosition(player_id), Entity.GetRotation(player_id))
            colddown_timer = 0
        end
    end

    if(input:IsKeyPressed(input.key.w)) then
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
    transform:SetPosition(moveX, moveY)
    transform:SetRotation(angle_impulse)
end
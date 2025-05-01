
local bullet_speed = 1;

local colddown = 2 -- Время до исчезновения
local colddown_timer = colddown

function update(dt)
    if colddown_timer <= colddown then
        colddown_timer = colddown_timer + dt
    end
    if colddown_timer >= colddown then
        Entity.Destroy(gameobject_id)
    end
    -- gameobject_id is global variable
    local bullet_boost = bullet_speed / dt
    radians = math.rad(Entity.GetRotation(gameobject_id))
    Entity.Move(gameobject_id, math.sin(radians) * bullet_boost, -math.cos(radians) * bullet_boost)
end
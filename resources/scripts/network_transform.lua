local difference = 0.0
local position = { 0, 0 }
local rotation = 0.0
local scale = { 0, 0 }
local network_transform_sensitivity = 0.1

function update(dt)
    difference = math.abs((transform.position - position) + (transform.rotation - rotation) + (transform.scale - scale))
    if (difference > network_transform_sensitivity) then
        position = transform.position
        rotation = transform.rotation
        scale = transform.scale
        network:Send(transform.position, transform.rotation, transform.scale)
    end
end
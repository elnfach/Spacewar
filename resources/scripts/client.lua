local player_id = 1
local players = {}
local online = 0

function OnClientReceiveData(position, rotation)
    print("x: ", position[1], ", y: ", position[2], ", rotation: ", rotation)
end

function connect()
    print("connect")
    network:Connect("127.0.0.1", "666")
end
function Listen()
    --Entity.SetPosition(1, )
end
function OnClientDisconnected()
print("HELLO CLIENT DISCONNECTED!")
    for index, uuid in ipairs(players) do
        Entity.Destroy(uuid)
    end
end
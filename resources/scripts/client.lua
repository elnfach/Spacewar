local player_id = 1
local players = {}
local online = 0

function CreateClient()
    print("CreateClient")
    Network.CreateClient()
end
function Listen()
    --Entity.SetPosition(1, )
end
--[[function SendPosition()
    --Network.SendData(Entity.GetPosition(player_id), Entity.GetRotation(player_id))
end]]
function OnClientConnected()
    print("HELLO NEW CLIENT!")
    table.insert(players, Entity.Copy(player_id, { 100, 200 }, 0, 0))
end
function OnClientDisconnected()
print("HELLO CLIENT DISCONNECTED!")
    for index, uuid in ipairs(players) do
        Entity.Destroy(uuid)
    end
end
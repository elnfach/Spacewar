local players = {}
local online = 0

local player_id = 1

function CreateServer()
    print("Create server!")
    Network.CreateServer("666")
end

function ReceivePositions()
    
end

function SendPosition()
    if online > 1 then
        Network.SendData(Entity.GetPosition(player_id), Entity.GetRotation(player_id))
    end
end
function OnServerClientConnected(client_socket)
    print("socket:", client_socket)
    table.insert(players, Entity.Copy(player_id, { 500, 500 }, 0))
    online = online + 1
--    Network.SendData(Entity.GetPosition(), 0)
end
function OnServerClientDisconnected()
    online = online - 1
end
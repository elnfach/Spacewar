local players = {}
local online = 0

local player_id = 1

function CreateServer()
    print("Create server!")
    Network.CreateServer()
end

function ReceivePositions()

end

function SendPosition()
    if online > 1 then
        Network.SendData(Entity.GetPosition(player_id), Entity.GetRotation(player_id))
    end
end
function OnServerClientConnected()
    print("CLIENT CONNECTED")
    table.insert(players, Entity.Copy(player_id, { 500, 500 }, 0))
    online = online + 1
    Network.SendData({500, 500}, 0)
end
function OnServerClientDisconnected()
    online = online - 1
end
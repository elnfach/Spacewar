local players = {}
local online = 0

local player_id = 1

function startServer()
    print("Start Server!")
    network:StartServer("666")
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
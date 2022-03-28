--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)


--[[message
Incorrect interaction with Chaos Phantom vs Hero Mask
]]
--Main Deck
Debug.AddCard(21844576,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--GY
Debug.AddCard(21208154,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(69247929,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(30312361,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(21208154,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(75141056,0,0,LOCATION_SZONE,1,10)
Debug.ReloadFieldEnd()
--aux.BeginPuzzle()
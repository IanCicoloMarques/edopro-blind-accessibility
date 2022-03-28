--[[message
Gogogo Aristera and Dexia, when used as Xyz Material with Utopic Unomatopoeia does not trigger. The second part of its condition, that checks if there is a number of monsters that belong to "Gogogo" in the group of cards used for the Xyz summon equal to the number of materials used fails.


]]

--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(6983839,0,0,LOCATION_EXTRA,0,8)
--Monster Zones
Debug.AddCard(91718579,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(8512558,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(91718579,0,0,LOCATION_MZONE,3,1,true)
--Monster Zones
Debug.AddCard(8512558,1,1,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()
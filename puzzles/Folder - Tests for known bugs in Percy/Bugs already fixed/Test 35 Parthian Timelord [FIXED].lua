--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
Parthian Shot doesn't actually skip the end of the Battle Phase (can still use Gladiator Beast effects). (The same thing probably happens with some other cards with similar effect.)
]]

--Main Deck
Debug.AddCard(41470137,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(78868776,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(29185231,0,0,LOCATION_SZONE,2,10)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()
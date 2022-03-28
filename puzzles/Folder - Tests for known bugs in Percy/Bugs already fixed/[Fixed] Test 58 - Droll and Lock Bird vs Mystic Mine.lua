--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	1-Pass the turn
	2-Activate ROTA
	3-Replace Mystic Mine for SS ARea Zero
	Droll can now be activated which is incorrect. If Mystic Mine is not there, the interaction works properly.
]]
--Hand
Debug.AddCard(94145021,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(14536035,0,0,LOCATION_MZONE,1,1,true)
--Spell & Trap Zones
Debug.AddCard(19230407,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(5318639,0,0,LOCATION_SZONE,4,10)
--Main Deck
Debug.AddCard(26077387,1,1,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(50005218,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(32807846,1,1,LOCATION_HAND,0,POS_FACEDOWN)
--Spell & Trap Zones
Debug.AddCard(76375976,1,1,LOCATION_SZONE,5,5)
--Debug.AddCard(76375976,1,1,LOCATION_SZONE,5,5)
Debug.ReloadFieldEnd()

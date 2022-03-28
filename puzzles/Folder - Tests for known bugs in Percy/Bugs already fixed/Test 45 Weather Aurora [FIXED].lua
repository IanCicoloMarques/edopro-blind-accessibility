--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
	--[[message
	If the card added to the player's hand is Special Summoned on the field in the same timing that it was added to the hand, then the now Summoned on the field card is getting banished by Auroral's effect.
	
	Edit the file by removing the comments to swap the fields and test it from the other player's perspective
	]]
--[[
--Main Deck
Debug.AddCard(67964209,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(83968380,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(67964209,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(6285791,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(15394083,0,0,LOCATION_MZONE,0,1,true)
--Spell & Trap Zones
Debug.AddCard(35149085,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(83968380,0,0,LOCATION_SZONE,3,10)
--Monster Zones
Debug.AddCard(65017789,1,1,LOCATION_MZONE,3,4,true)
--Spell & Trap Zones
Debug.AddCard(52834429,1,1,LOCATION_SZONE,3,5)

--]]



--Main Deck
Debug.AddCard(67964209,1,1,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(83968380,1,1,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(67964209,1,1,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(6285791,1,1,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(15394083,1,1,LOCATION_MZONE,0,1,true)
--Spell & Trap Zones
Debug.AddCard(35149085,1,1,LOCATION_SZONE,1,10)
Debug.AddCard(83968380,1,1,LOCATION_SZONE,3,10)
--Monster Zones
Debug.AddCard(65017789,0,0,LOCATION_MZONE,3,4,true)
--Spell & Trap Zones
Debug.AddCard(52834429,0,0,LOCATION_SZONE,3,5)


Debug.ReloadFieldEnd()
aux.BeginPuzzle()
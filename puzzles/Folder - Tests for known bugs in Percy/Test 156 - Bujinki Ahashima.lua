--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--[[message
A puzzle to demonstrate the issues with "Bujinki Ahashima".


1 - The monster selected from your hand is never special summoned

2 - Interactions with "Zoodiac" Xyz monsters; being able to use the alternative Xyz summon method, and by doing so, no materials will be used
]]
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(15520842,0,0,LOCATION_DECK,0,POS_FACEDOWN) --Photon Hand
--Extra Deck
Debug.AddCard(71095768,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(41375811,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(84013237,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(25236056,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(25236056,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(18063928,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(4367330,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(27068117,0,0,LOCATION_HAND,0,POS_FACEDOWN) --Overlay Regen
--MZ
Debug.AddCard(8165596,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(32491822,0,0,LOCATION_MZONE,1,1,true) --Hamon, Lord of Striking Thunder
--Spell & Trap Zones
Debug.AddCard(70368879,1,1,LOCATION_SZONE,3,10) --Upstart Goblin

Debug.AddCard(82324105,0,0,LOCATION_SZONE,3,10) --Limit Impulse

Debug.ReloadFieldEnd()
--aux.BeginPuzzle()

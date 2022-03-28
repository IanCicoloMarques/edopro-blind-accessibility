--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)


--[[message
2+0 == 2
1-Move to the opponent's battle Phase
2-Activate "Ceasefire", chain "Magical Hats"
	Magical Hats special ummons Pot of Greed
	Ceasefire flips Pot of Greed
3-Activate Urgent Tuning
4-You now can summon Formula Synchro by using a Formula Synchro + 1 Pot of Greed


]]
--Main Deck
Debug.AddCard(55144522,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(55144522,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(595626,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(595626,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(82744076,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(8487449,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(50091196,0,0,LOCATION_EXTRA,0,8)
--Monster Zones
Debug.AddCard(82744076,0,0,LOCATION_MZONE,0,POS_FACEDOWN_DEFENSE,true)
Debug.AddCard(50091196,0,0,LOCATION_MZONE,1,4,true)
Debug.AddCard(8487449,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(81210420,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(94634433,0,0,LOCATION_SZONE,0,10)
Debug.AddCard(36468556,0,0,LOCATION_SZONE,1,10)
Debug.ReloadFieldEnd()

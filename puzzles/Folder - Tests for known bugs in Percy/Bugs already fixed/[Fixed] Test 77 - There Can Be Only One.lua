--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(92204263,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(28692962,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(24207889,0,0,LOCATION_SZONE,1,5)

Debug.AddCard(69351984,0,0,LOCATION_HAND,1,5)
Debug.AddCard(7868571,0,0,LOCATION_HAND,1,5)

Debug.AddCard(69351984,0,0,LOCATION_PZONE,1,5)
Debug.AddCard(7868571,0,0,LOCATION_PZONE,0,5)
--Spell & Trap Zones
Debug.AddCard(38120068,1,1,LOCATION_SZONE,3,10)
Debug.ReloadFieldEnd()

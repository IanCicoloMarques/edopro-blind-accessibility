--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(92204263,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(36553319,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(28692962,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(90846359,0,0,LOCATION_SZONE,2,5)
Debug.ReloadFieldEnd()
--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(5929801,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(58988903,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(3298689,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(1621413,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(81927732,0,0,LOCATION_EXTRA,0,8)
--Monster Zones
Debug.AddCard(36429703,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(73347079,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(5929801,0,0,LOCATION_MZONE,2,1,true)

Debug.AddCard(16195942,0,0,LOCATION_MZONE,3,1,true)
Debug.ReloadFieldEnd()

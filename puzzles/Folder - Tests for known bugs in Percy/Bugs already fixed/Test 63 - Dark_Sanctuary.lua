--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(16625614,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(31893528,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Spell & Trap Zones
Debug.AddCard(89208725,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(94212438,0,0,LOCATION_SZONE,2,5)
Debug.ReloadFieldEnd()

--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_TEST_MODE,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Player's hand
Debug.AddCard(39238953,0,0,LOCATION_HAND,0,POS_FACEDOWN) --Lullaby

--Opp's field
Debug.AddCard(23898021,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK) --Lilith (trigger Diabolos)
Debug.AddCard(27053506,1,1,LOCATION_SZONE,0,POS_FACEDOWN) --Secret Barrel (trigger Multifaker)
Debug.AddCard(99590524,1,1,LOCATION_SZONE,1,POS_FACEDOWN) --Treacherous Trap Hole (trigger Nepenthes)

--Opp's deck
Debug.AddCard(27053506,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Secret Barrel (turn on Lilith)
Debug.AddCard(27053506,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Secret Barrel (turn on Lilith)
Debug.AddCard(27053506,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Secret Barrel (turn on Lilith)
Debug.AddCard(42790071,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Multifaker
Debug.AddCard(50383626,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Diabolos
Debug.AddCard(28201945,1,1,LOCATION_DECK,0,POS_FACEDOWN) --Nepenthes

Debug.ReloadFieldEnd()
--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand (yours)
Debug.AddCard(71797713,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(83032858,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19036557,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.ReloadFieldEnd()
Debug.ShowHint("No matter where in the field is your card, you will always follow the same path to activate it's effect. Let's try to use effects from the hand and the graveyard now.")
Debug.ShowHint("Press the key C to see what cards can be activated.")
Debug.ShowHint("Select the card Elementsaber Lapauila Mana with Enter and press the key F to use the card effect.")
Debug.ShowHint("The effect will be activated and will ask for you to choose two cards to send to the graveyard.")
Debug.ShowHint("Press they key Z to see the targetable cards, Select the card you want to target with Enter and press the key P to confirm. Do it twice, once for each card")
Debug.ShowHint("Now, just follow the same recipe to activate Elementsaber Makani and Elementsaber Aina effects from the graveyard");
aux.BeginPuzzle()
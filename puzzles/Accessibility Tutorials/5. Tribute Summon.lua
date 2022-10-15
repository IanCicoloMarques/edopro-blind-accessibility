--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.SetAIName("TutorialBot")
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI+DUEL_PSEUDO_SHUFFLE,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,2000,0,0)

--Hand (yours)
Debug.AddCard(92176681,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(50690129,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--Monster Zones (yours)
Debug.AddCard(50690129,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)
Debug.AddCard(50690129,0,0,LOCATION_MZONE,1,POS_FACEUP_ATTACK,true)
Debug.AddCard(29716911,0,0,LOCATION_MZONE,2,POS_FACEUP_ATTACK,true)

--Monster Zones (opponent's)
Debug.AddCard(15025844,1,1,LOCATION_MZONE,1,POS_FACEUP_DEFENSE,true)

Debug.ReloadFieldEnd()
Debug.ShowHint("Press the key Q to look at your hand.")
Debug.ShowHint("Select the card you want to summon with Enter and press the key A to select the Summon Command.")
Debug.ShowHint("Press the key Z to see the cards you can select as a sacrifice and confirm the key P. You should hear a sound to confirm that the card was selected.")
aux.BeginPuzzle()
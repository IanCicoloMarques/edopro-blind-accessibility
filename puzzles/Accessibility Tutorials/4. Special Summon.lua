--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,100,0,0)

Debug.ShowHint("Press the key X to look at the cards you can special summon.")
Debug.ShowHint("Select the card you want to play. Try to select Cannon, the Melodious Diva")
Debug.ShowHint("Press the key D to special summon the selected card.")
Debug.ShowHint("Press one key from NUMBER 1 TO 5 to select the zone where to play the card.")
Debug.ShowHint("You can press the key COMMA to summon the monster in attack mode or the key DOT to summon the monster in defense mode.")

--Hand (yours)
Debug.AddCard(16021142,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--Monster Zones (yours)
Debug.AddCard(41767843,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()
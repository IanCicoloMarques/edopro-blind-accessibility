--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,100,0,0)

Debug.ShowHint("Press the key Q to look at your hand.")
Debug.ShowHint("Select the card you want to play. Try to select Winged Dragon, Guardian of the Fortress 1")
Debug.ShowHint("Press the key A to normal summon the selected card.")
Debug.ShowHint("Press one key from NUMBER 1 TO 5 to select the zone where to play the card.")
Debug.ShowHint("When able to, you can press the key COMMA to summon the monster in attack mode or the key DOT to summon the monster in defense mode.")
--Hand (yours)
Debug.AddCard(58257569,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(87796900,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--Monster Zones (opponent's)
Debug.AddCard(79335209,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()
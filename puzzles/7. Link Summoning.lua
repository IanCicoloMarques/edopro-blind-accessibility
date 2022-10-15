--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck (yours)
Debug.AddCard(34755994,0,0,LOCATION_EXTRA,0,POS_FACEDOWN)

--Monster Zones (yours)
Debug.AddCard(86120752,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK,true)

Debug.ReloadFieldEnd()
Debug.ShowHint("Press the key X to see what cards can be special summoned.")
Debug.ShowHint("The special summonable cards will be displayed to you. You can press the key Enter after you see the cards. After this, press D to open the special summon menu.")
Debug.ShowHint("Select the card you want to summon with Enter.")
Debug.ShowHint("Press they key Z to see the targetable cards to select the cards used as sacrifices to summon. Select the card you want to target with Enter and press the key P to confirm.")
Debug.ShowHint("Since you are summoning a link monster, you need to summon it in a link zone. For this, press the Key V two times to go to the Link Zone and summon the monster there.")
aux.BeginPuzzle()
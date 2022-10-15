--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand (yours)
Debug.AddCard(45702014,0,0,LOCATION_MZONE,0,POS_FACEUP_ATTACK, true)
Debug.AddCard(71797713,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.ReloadFieldEnd()
Debug.ShowHint("Press the key C to see what cards can be activated.")
Debug.ShowHint("Select the card you want to activate with Enter and press the key F to use the card effect.")
Debug.ShowHint("The effect will be activated.")
Debug.ShowHint("If the effect affect other cards and you need to choose which card you want to target, press they key Z to see the targetable cards, Select the card you want to target with Enter and press the key P to confirm.")
aux.BeginPuzzle()
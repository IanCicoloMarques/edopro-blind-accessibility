--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand (yours)
Debug.AddCard(74605254,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19302550,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(44186624,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(47198668,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.ReloadFieldEnd()

Debug.ShowHint("Press the key C to see what cards can be activated.")
Debug.ShowHint("Select the card D/D Savant Galilei with Enter and press the key F to use the card effect.")
Debug.ShowHint("The effect will be activated and will ask for you to choose where to play the card.")
Debug.ShowHint("Since this is a Pendulum, you need to select a Pendulum Zone. Press the key V to go to the spell field and the key 1 to select the left Pendulum Zone")
Debug.ShowHint("Again, press the key C to see what cards can be activated.")
Debug.ShowHint("Select the card D/D Savant Newton with Enter and press the key F to use the card effect.")
Debug.ShowHint("The effect will be activated and will ask for you to choose where to play the card.")
Debug.ShowHint("Since this is a Pendulum, you need to select a Pendulum Zone. Press the key V to go to the spell field and the key 5 to select the right Pendulum Zone")
Debug.ShowHint("Press they key X to see the effects you can activate. Your Pendulum monster can be activated. Select D/D Savant Galilei with Enter and press the key D to use it's effect.")
Debug.ShowHint("Press they key Z to see the targetable cards. Select the cards you want to pendulum summon with Enter and press the key P to confirm.")
Debug.ShowHint("Press they key Comma if you want to stop the summoning effect.")

aux.BeginPuzzle()
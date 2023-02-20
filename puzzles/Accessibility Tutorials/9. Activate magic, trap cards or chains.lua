--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--Partially rewritten by edo9300
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,5)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Hand (yours)
Debug.AddCard(5318639,0,0,LOCATION_HAND,0,POS_FACEDOWN)

--GY (yours)
Debug.AddCard(46986417,0,0,LOCATION_GRAVE,0,POS_FACEUP)

--Monster Zones (yours)
Debug.AddCard(46986417,0,0,LOCATION_MZONE,2,POS_FACEUP_ATTACK,true)

--Spell & Trap Zones (yours)
Debug.AddCard(5318639,0,0,LOCATION_SZONE,1,POS_FACEDOWN)

--Spell & Trap Zones (opponent's)
Debug.AddCard(34815282,1,1,LOCATION_SZONE,2,POS_FACEDOWN)

Debug.ReloadFieldEnd()
Debug.ShowHint("No matter if it's a trap or spell card, you will always follow the same path to activate it's effect.")
Debug.ShowHint("Press the key Q to see what cards you have in your hand.")
Debug.ShowHint("Select your magic card with Enter. After that, you can press the key F to activate the card or the key S to set it on the field. Let's press the key F to use the card.")
Debug.ShowHint("The effect will be activated and will ask for you to choose a card to destroy.")
Debug.ShowHint("Press they key Z to see the cards you can destroy. Usually, you won't be able to see the enemy face down card, but you can here since it is a tutorial.")
Debug.ShowHint("Select Miniaturize with Enter and press the key P to confirm.")
Debug.ShowHint("The game will ask you if you want to chain an effect. Press the key comma to select Yes. If you don't want to chain, press the key Dot to select No")
Debug.ShowHint("Press they key C to see the cards that can be chained. Select your magic card with Enter and press the key F to use it's effect.")
Debug.ShowHint("Press they key Z again to see the cards you can destroy and follow the game as before.")

aux.BeginPuzzle()
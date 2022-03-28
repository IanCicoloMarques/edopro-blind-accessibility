--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)


--[[message
Master Peace, the True Dracoslaying King + Metaltron XII, the True Dracombatant (similar cards include Horus The Black Flame Dragon LV6) are still changed to Defense Position by the effect of cards such as Level Limit - Area B and Bagooska, even when being immune to respective card types' effects. Happens only if you Tribute Summon these cards with a card effect, such as Disciples of the True Dracophoenix, True King's Return or Arrivalrivals. Does not happen if you Tribute Summon these cards normally.
]]
--Hand
Debug.AddCard(57761191,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(57761191,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(75878039,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,4,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,5,1,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,6,1,true)
--Spell & Trap Zones
Debug.AddCard(75425320,0,0,LOCATION_SZONE,1,5)
--Monster Zones
Debug.AddCard(90590303,1,1,LOCATION_MZONE,2,4,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()
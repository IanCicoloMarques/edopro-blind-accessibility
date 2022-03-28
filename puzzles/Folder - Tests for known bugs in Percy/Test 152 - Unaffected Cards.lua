--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
--[[message
	1-Consider a card that makes others unaffected.
	In this test: Metamorformation + a Metalfoes monster and Aquarium Stage + a Aquaactress monster
	2-If you attempt to return only the unaffected card to the hand by using an effect, you are unable to, which is correct.
	3-Now if you attempt to return both the unaffected card AND the card that makes it unaffected, you are able to, which is wrong.
	
	Use Dragite to test this.

]]

Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(32912040,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(32912040,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(66668900,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(66668900,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(66668900,0,0,LOCATION_DECK,0,POS_FACEDOWN)

--Monster Zones
Debug.AddCard(9464441,0,0,LOCATION_MZONE,1,1,true)
--Monster Zones
Debug.AddCard(66668900,1,1,LOCATION_MZONE,0,1,true)
Debug.AddCard(9464441,1,1,LOCATION_MZONE,1,1,true)
Debug.AddCard(32912040,1,1,LOCATION_MZONE,2,1,true)
Debug.AddCard(69351984,1,1,LOCATION_MZONE,3,1,true)
--Spell & Trap Zones
Debug.AddCard(29047353,1,1,LOCATION_SZONE,2,5)

--Spell & Trap Zones
Debug.AddCard(33256280,0,0,LOCATION_PZONE,0,5)
--Spell & Trap Zones
Debug.AddCard(46500985,1,1,LOCATION_SZONE,5,5)
Debug.AddCard(69351984,1,1,LOCATION_PZONE,1,5)
Debug.AddCard(7868571,1,1,LOCATION_PZONE,0,5)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()

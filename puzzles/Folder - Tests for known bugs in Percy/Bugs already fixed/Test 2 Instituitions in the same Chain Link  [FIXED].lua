--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
 Demonstrates the problem with SEGOC when the costs can only be paid once
]]

--Spell & Trap Zones
Debug.AddCard(53582587,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(53842431,1,1,LOCATION_MZONE,3,1)
Debug.AddCard(53842431,0,0,LOCATION_MZONE,1,1)
Debug.AddCard(53582587,0,0,LOCATION_SZONE,4,10)
Debug.AddCard(53842431,0,0,LOCATION_HAND,4,10)
local b=Debug.AddCard(65342096,0,0,LOCATION_SZONE,2,5)
local c=Debug.AddCard(65342096,0,0,LOCATION_SZONE,3,5)
--Spell & Trap Zones
local a=Debug.AddCard(03611830,1,1,LOCATION_PZONE,0,5)
Debug.ReloadFieldEnd()

Debug.PreAddCounter(a,COUNTER_SPELL,6)
Debug.PreAddCounter(b,COUNTER_SPELL,5)
Debug.PreAddCounter(c,COUNTER_SPELL,5)
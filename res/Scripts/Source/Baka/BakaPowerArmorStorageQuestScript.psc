Scriptname BakaPowerArmorStorageQuestScript extends Quest Hidden Conditional

Bool Property bShiftHeld Auto Conditional
Int Property iKeyCode Auto Hidden

Event OnQuestInit()
	Register()
	RegisterForRemoteEvent(Game.GetPlayer(), "OnPlayerLoadGame")
EndEvent

Event Actor.OnPlayerLoadGame(Actor akSender)
	Register()
EndEvent

Event OnKeyDown(int aiKeyCode)
	bShiftHeld = True
EndEvent

Event OnKeyUp(int aiKeyCode, float afTime)
	bShiftHeld = False
EndEvent

Function Register()
	RegisterForExternalEvent("OnMCMClose", "OnMCMClose")
	UpdateBindings()
EndFunction

Function OnMCMClose()
	BakaPowerArmorStorage.UpdateSettings()
	UpdateBindings()
EndFunction

Function UpdateBindings()
	UnregisterForKey(160)
	UnregisterForKey(iKeyCode)

	iKeyCode = BakaPowerArmorStorage.GetKeyCode()
	RegisterForKey(iKeyCode)
	RegisterForKey(Input.GetMappedKey("Sprint", 2))
EndFunction

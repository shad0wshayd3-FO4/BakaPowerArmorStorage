Scriptname BakaPowerArmorStoragePlacedScript extends ObjectReference Hidden Const

Function DoRegister()
    StartTimer(120, 10)
    StartTimer(110, 20)
    StartTimer(60, 30)
    RegisterForDistanceGreaterThanEvent(Game.GetPlayer(), Self, 4000.0)
    RegisterForRemoteEvent(Game.GetPlayer(), "OnPlayerUseWorkbench")
EndFunction

Function DoCreateToken()
    If (!IsDisabled())
        BakaPowerArmorStorage.CreateToken(Self)
    EndIf
EndFunction

Function Unregister()
    CancelTimer(10)
    CancelTimer(20)
    CancelTimer(30)
    UnregisterForDistanceEvents(Game.GetPlayer(), Self)
EndFunction

Function UnregisterAll()
    Unregister()
    UnregisterForAllRemoteEvents()
EndFunction

; -------------------------------------------------------------------------------------------------
; Distance/Time Events
; -------------------------------------------------------------------------------------------------
Event OnDistanceGreaterThan(ObjectReference akSourceRef, ObjectReference akTargetRef, float afDistance)
    BakaPowerArmorStorage.ShowNotification(0)
    UnregisterAll()
    DoCreateToken()
EndEvent

Event OnTimer(int aiTimerID)
    If (aiTimerID == 10)
        BakaPowerArmorStorage.ShowNotification(0)
        UnregisterAll()
        DoCreateToken()
    ElseIf (aiTimerID == 20)
        BakaPowerArmorStorage.ShowNotification(10)
    ElseIf (aiTimerID == 30)
        BakaPowerArmorStorage.ShowNotification(60)
    EndIf
EndEvent

; -------------------------------------------------------------------------------------------------
; Activation Events
; -------------------------------------------------------------------------------------------------
Event OnActivate(ObjectReference akActionRef)
    Actor akSender = akActionRef as Actor
    If (akSender)
        Unregister()
        RegisterForRemoteEvent(akSender, "OnGetUp")
    EndIf
EndEvent

Event Actor.OnPlayerUseWorkBench(Actor akSender, ObjectReference akWorkBench)
    If (akWorkBench == Self)
        Unregister()
        RegisterForRemoteEvent(akSender, "OnGetUp")
    EndIf
EndEvent

Event Actor.OnGetUp(Actor akSender, ObjectReference akFurniture)
    If (!IsDisabled())
        If (akFurniture == Self)
            DoRegister()
            UnregisterForRemoteEvent(akSender, "OnGetUp")
        EndIf
    EndIf
EndEvent

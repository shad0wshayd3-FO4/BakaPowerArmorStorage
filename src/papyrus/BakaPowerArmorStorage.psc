Scriptname BakaPowerArmorStorage extends ScriptObject Native

{ Create a Power Armor Token from a given Power Armor Frame Furniture Reference, returns True if successful }
bool Function CreateToken(ObjectReference akPAFrame) Native Global

{ If the passed Power Armor Token is valid, start the Workshop to place down the corresponding Frame, returns True if successful }
bool Function HandleToken(ObjectReference akPAToken) Native Global

{ Remove BakaPowerArmorStoragePlacedScript data from a placed Power Armor Frame Furniture, returns True if successful }
bool Function RemoveScript(ObjectReference akPAFrame) Native Global

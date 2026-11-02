#if defined _INC_SSI_EXTRA_INLINE_OBJECT
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_OBJECT

#include <open.mp>
#include <streamer>
#include <SSI\iterator>
#include <SSI\hooks>
#include <SSI\inline>

/**
 * Dynamic objects that call an inline when they finish moving, while a player
 * edits them, or when a player selects one:
 *
 *     #include <SSI_Extra\inline-object>
 *
 *     OpenGate(playerid, STREAMER_TAG_OBJECT:gate) {
 *         inline OnOpened() {
 *             SendClientMessage(playerid, -1, "The gate is open.");
 *         }
 *
 *         DynamicObject_MoveInline(gate, 10.0, 0.0, 3.0, 2.0, using inline OnOpened);
 *     }
 *
 *     Place(playerid, STREAMER_TAG_OBJECT:objectid) {
 *         inline OnEdited(EDIT_RESPONSE:response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
 *             if (response != EDIT_RESPONSE_FINAL) {
 *                 @return;
 *             }
 *
 *             SetDynamicObjectPos(objectid, x, y, z);
 *             SetDynamicObjectRot(objectid, rx, ry, rz);
 *         }
 *
 *         DynamicObject_EditInline(playerid, objectid, using inline OnEdited);
 *     }
 *
 * - A move calls its inline once, when the object reaches the place it was
 *   sent to. A new move with an inline replaces the old one. An object that
 *   is stopped, or moved somewhere else without an inline, never calls the old
 *   inline, which is freed on the next arrival.
 * - An edit calls its inline on every update, and frees it after the last
 *   answer, kept or cancelled.
 * - A selection calls its inline once, with the object, its model and where
 *   it was hit.
 * - A player edits or selects one thing at a time: a new edit or selection
 *   frees the inline of the old one, and so does leaving.
 * - A move keeps its inline and where it goes in the object's own streamer
 *   data, under keys of their own, so `E_STREAMER_EXTRA_ID` stays free and an
 *   id the streamer hands out again starts with none.
 * - `DestroyDynamicObject` frees the inlines of the object.
 *   `Streamer_DestroyAllItems` does not: destroy the objects one by one.
 */

/**
 * # Header
 */

Inline_Signature(iffffff)
Inline_Signature(iifff)

static enum {
    SSI_INLINE_OBJECT_MOVE = E_STREAMER_CUSTOM(0x53534906),
    SSI_INLINE_OBJECT_X = E_STREAMER_CUSTOM(0x53534907),
    SSI_INLINE_OBJECT_Y = E_STREAMER_CUSTOM(0x53534908),
    SSI_INLINE_OBJECT_Z = E_STREAMER_CUSTOM(0x53534909)
};

static stock
    Inline:SSI@objectEdit[MAX_PLAYERS] = { INVALID_INLINE, ... },
    STREAMER_TAG_OBJECT:SSI@objectEdited[MAX_PLAYERS],
    Inline:SSI@objectSelect[MAX_PLAYERS] = { INVALID_INLINE, ... },
    SSI@objectEditing
;

/**
 * # Functions
 */

/**
 * @brief      Move an object, then call an inline when it gets there.
 *
 * @param      objectid  The object.
 * @param      x         Where to, on the x axis.
 * @param      y         Where to, on the y axis.
 * @param      z         Where to, on the z axis.
 * @param      speed     The speed.
 * @param      callback  The inline, as `using inline Name`, taking nothing.
 * @param      rx        The rotation on the x axis, `-1000.0` to keep it.
 * @param      ry        The rotation on the y axis, `-1000.0` to keep it.
 * @param      rz        The rotation on the z axis, `-1000.0` to keep it.
 *
 * @return     - the time the move takes, in milliseconds
 *             - `0` the inline is freed, when:
 *                 + the inline could not be captured
 *                 + the object could not move
 */
forward DynamicObject_MoveInline(STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z, Float:speed, Inline:callback<>, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0);

/**
 * @brief      Let a player edit an object, and call an inline with each
 *             answer.
 *
 * @param      playerid  The player.
 * @param      objectid  The object.
 * @param      callback  The inline, as `using inline Name`, taking the
 *                       response and the position and rotation.
 *
 * @return     - `true` the editor is open
 *             - `false` the inline is freed, when:
 *                 + the inline could not be captured
 *                 + the player is not connected
 *                 + the object does not exist
 */
forward bool:DynamicObject_EditInline(playerid, STREAMER_TAG_OBJECT:objectid, Inline:callback<iffffff>);

/**
 * @brief      Let a player select an object, and call an inline with it.
 *
 * @param      playerid  The player.
 * @param      callback  The inline, as `using inline Name`, taking the object,
 *                       its model and where it was hit.
 *
 * @return     - `true` the player is selecting
 *             - `false` the inline is freed, when:
 *                 + the inline could not be captured
 *                 + the player is not connected
 */
forward bool:DynamicObject_SelectInline(playerid, Inline:callback<iifff>);

/**
 * # Internal
 */

static stock Inline:SSI_ObjectMoveEndInternal(STREAMER_TAG_OBJECT:objectid) {
    if (!Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_MOVE)) {
        return INVALID_INLINE;
    }

    new const
        Inline:closure = Inline:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_MOVE)
    ;

    Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_MOVE);
    Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_X);
    Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Y);
    Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Z);

    return closure;
}

static stock SSI_ObjectPlayerEndInternal(playerid) {
    if (Inline_Free(SSI@objectEdit[playerid])) {
        --SSI@objectEditing;
    }

    Inline_Free(SSI@objectSelect[playerid]);
    SSI@objectEdit[playerid] = INVALID_INLINE;
    SSI@objectSelect[playerid] = INVALID_INLINE;
}

/**
 * # Object
 */

stock DynamicObject_MoveInline(STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z, Float:speed, Inline:callback<>, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return 0;
    }

    Inline_Free(SSI_ObjectMoveEndInternal(objectid));

    new const
        time = MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz)
    ;

    if (time == 0) {
        Inline_Free(closure);

        return 0;
    }

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_MOVE, _:closure);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_X, _:x);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Y, _:y);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Z, _:z);

    return time;
}

stock bool:DynamicObject_EditInline(playerid, STREAMER_TAG_OBJECT:objectid, Inline:callback<iffffff>) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        Inline_Free(closure);

        return false;
    }

    if (!IsValidDynamicObject(objectid)) {
        Inline_Free(closure);

        return false;
    }

    SSI_ObjectPlayerEndInternal(playerid);

    if (!EditDynamicObject(playerid, objectid)) {
        Inline_Free(closure);

        return false;
    }

    SSI@objectEdit[playerid] = closure;
    SSI@objectEdited[playerid] = objectid;
    ++SSI@objectEditing;

    return true;
}

stock bool:DynamicObject_SelectInline(playerid, Inline:callback<iifff>) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        Inline_Free(closure);

        return false;
    }

    SSI_ObjectPlayerEndInternal(playerid);

    if (!BeginObjectSelecting(playerid)) {
        Inline_Free(closure);

        return false;
    }

    SSI@objectSelect[playerid] = closure;

    return true;
}

/**
 * # Calls
 */

hook OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid) {
    if (!Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_MOVE)) {
        return 1;
    }

    new
        Float:x,
        Float:y,
        Float:z
    ;

    GetDynamicObjectPos(objectid, x, y, z);

    x -= Float:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_X);
    y -= Float:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Y);
    z -= Float:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, SSI_INLINE_OBJECT_Z);

    new const
        bool:arrived = (VectorSize(x, y, z) < 0.01),
        Inline:closure = SSI_ObjectMoveEndInternal(objectid)
    ;

    if (!arrived) {
        Inline_Free(closure);

        return 1;
    }

    Inline_CallOnce(closure);

    return 1;
}

hook OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    if (!Inline_IsValid(SSI@objectEdit[playerid])) {
        return 1;
    }

    if (SSI@objectEdited[playerid] != objectid) {
        return 1;
    }

    if (EDIT_RESPONSE:response == EDIT_RESPONSE_UPDATE) {
        Inline_Call(SSI@objectEdit[playerid], response, x, y, z, rx, ry, rz);

        return 1;
    }

    new const
        Inline:closure = SSI@objectEdit[playerid]
    ;

    SSI@objectEdit[playerid] = INVALID_INLINE;
    --SSI@objectEditing;
    Inline_CallOnce(closure, response, x, y, z, rx, ry, rz);

    return 1;
}

hook OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z) {
    new const
        Inline:closure = SSI@objectSelect[playerid]
    ;

    if (!Inline_IsValid(closure)) {
        return 1;
    }

    SSI@objectSelect[playerid] = INVALID_INLINE;
    Inline_CallOnce(closure, _:objectid, modelid, x, y, z);

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    SSI_ObjectPlayerEndInternal(playerid);

    return 1;
}

hook native DestroyDynamicObject(STREAMER_TAG_OBJECT:objectid) {
    Inline_Free(SSI_ObjectMoveEndInternal(objectid));

    if (SSI@objectEditing == 0) {
        return DestroyDynamicObject(objectid);
    }

    foreach (new i : Character) {
        if (SSI@objectEdited[i] != objectid) {
            continue;
        }

        if (Inline_Free(SSI@objectEdit[i])) {
            --SSI@objectEditing;
        }

        SSI@objectEdit[i] = INVALID_INLINE;
    }

    return DestroyDynamicObject(objectid);
}

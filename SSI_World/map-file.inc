#if defined _INC_SSI_WORLD_MAP_FILE
    #endinput
#endif
#define _INC_SSI_WORLD_MAP_FILE

#include <open.mp>
#include <streamer>
#include <SSI\iterator>

#include <SSI\hooks>

/**
 * Loads a map file kept in scriptfiles, so a map is changed without touching
 * the gamemode. A map file is the lines a mapping tool writes: `CreateObject`,
 * `CreateDynamicObject`, `SetObjectMaterial`, `SetObjectMaterialText`,
 * `RemoveBuildingForPlayer` and `AddSimpleModel`.
 *
 *     options(world, interior, stream distance)
 *
 * sets the world, interior and stream distance of the objects after it in the
 * same file. `//` starts a comment, on its own line or after a call.
 *
 * A material or a text goes on the last object made; the object id written in
 * the call is ignored. A removal is done for every player connected now and
 * later, as one made by `RemoveMapBuilding`. A model is only added when its id
 * is free, since the server keeps the custom models when the gamemode
 * restarts.
 *
 * Based on Southclaws' samp-object-loader, rewritten as an include.
 */

/**
 * # Header
 */

#if !defined MAP_LINE_SIZE
    #define MAP_LINE_SIZE (512)
#endif

#if !defined MAX_MAP_REMOVALS
    #define MAX_MAP_REMOVALS (256)
#endif

#if !defined MAP_DEFAULT_STREAM_DISTANCE
    #define MAP_DEFAULT_STREAM_DISTANCE (STREAMER_OBJECT_SD)
#endif

#define MAX_MAP_CALL_NAME (48)
#define MAX_MAP_ARGUMENTS (12)
#define MAX_MAP_ARGUMENT_SIZE (160)

static enum _:E_MAP_REMOVAL {
    E_MAP_REMOVAL_MODEL,

    Float:E_MAP_REMOVAL_X,
    Float:E_MAP_REMOVAL_Y,
    Float:E_MAP_REMOVAL_Z,
    Float:E_MAP_REMOVAL_RADIUS
};

static
    gMapRemoval[MAX_MAP_REMOVALS][E_MAP_REMOVAL],
    gMapRemovalCount
;

static const
    gMapMaterialSizeName[][] = {
        "32x32",
        "64x32",
        "64x64",
        "128x32",
        "128x64",
        "128x128",
        "256x32",
        "256x64",
        "256x128",
        "256x256",
        "512x64",
        "512x128",
        "512x256",
        "512x512"
    }
;

/**
 * # Functions
 */

/**
 * @brief      Make everything a map file says.
 *
 * @param      filename    File to read, from scriptfiles.
 * @param      worldid     World the objects are in until an options line says
 *                         otherwise, `-1` for every world.
 * @param      interiorid  Interior the objects are in until an options line
 *                         says otherwise, `-1` for every interior.
 * @param      objects     Reads back the objects made, in the order the file
 *                         makes them. Left out, nothing is read back.
 * @param      size        Size of `objects`. Objects past it are still made.
 *
 * @return     - how many objects were made
 *             - `-1` the file could not be opened
 */
forward LoadMap(const filename[], worldid = -1, interiorid = -1, STREAMER_TAG_OBJECT:objects[] = { STREAMER_TAG_OBJECT:INVALID_STREAMER_ID }, size = 0);

/**
 * @brief      Remove buildings of the map for every player connected now and
 *             later.
 *
 * @param      modelid  Model to remove, or `-1` for every model.
 * @param      x        Centre on the X axis.
 * @param      y        Centre on the Y axis.
 * @param      z        Centre on the Z axis.
 * @param      radius   Distance from the centre.
 *
 * @return     - `true` the removal was kept
 *             - `false` there are already `MAX_MAP_REMOVALS`
 */
forward bool:RemoveMapBuilding(modelid, Float:x, Float:y, Float:z, Float:radius);

/**
 * @brief      How many buildings the loaded maps and `RemoveMapBuilding`
 *             remove.
 *
 * @return     - the count, up to `MAX_MAP_REMOVALS`
 */
forward GetMapRemovalCount();

/**
 * # Events
 */

/**
 * @brief      Buildings of the map were removed for every player, so what else
 *             knows the map, such as physics, can remove them too.
 *
 * @param      modelid  Model removed, or `-1` for every model.
 * @param      x        Centre on the X axis.
 * @param      y        Centre on the Y axis.
 * @param      z        Centre on the Z axis.
 * @param      radius   Distance from the centre.
 */
event OnMapBuildingRemoved(modelid, Float:x, Float:y, Float:z, Float:radius);

/**
 * # Internal
 */

/**
 * @brief      Whether a character is a space, a tab or a line ending.
 *
 * @param      character  Character to check.
 *
 * @return     - `true` it is blank
 *             - `false` it is not
 */
static stock bool:IsMapBlankInternal(character) {
    return (character == ' ' || character == '\t' || character == '\r' || character == '\n');
}

/**
 * @brief      Split a line into the name of the call and what is between its
 *             brackets.
 *
 * A comment is cut off first, unless it is inside quotes. An assignment in
 * front of the call is dropped, so `tmpobjid = CreateObject(` names
 * `CreateObject`.
 *
 * @param      line      Line to split. Its comment is cut off in place.
 * @param      name      Reads back the name of the call.
 * @param      args      Reads back what is between the brackets.
 *
 * @return     - `true` it is a call
 *             - `false` it is blank, a comment, or not a call
 */
static stock bool:SplitMapLineInternal(line[], name[MAX_MAP_CALL_NAME], args[MAP_LINE_SIZE]) {
    new
        bool:quoted,
        open = -1,
        close = -1
    ;

    for (new i; line[i] != EOS; ++i) {
        if (line[i] == '"') {
            quoted = !quoted;

            continue;
        }

        if (quoted) {
            continue;
        }

        if (line[i] == '/' && line[i + 1] == '/') {
            line[i] = EOS;

            break;
        }

        if (line[i] == '(' && open == -1) {
            open = i;
        }

        if (line[i] == ')') {
            close = i;
        }
    }

    if (open == -1) {
        return false;
    }

    if (close < open) {
        return false;
    }

    new
        start,
        end = open
    ;

    for (new i; i != open; ++i) {
        if (line[i] == '=') {
            start = i + 1;
        }
    }

    while (start < end && IsMapBlankInternal(line[start])) {
        ++start;
    }

    while (end > start && IsMapBlankInternal(line[end - 1])) {
        --end;
    }

    if (start == end) {
        return false;
    }

    strmid(name, line, start, end, MAX_MAP_CALL_NAME);
    strmid(args, line, open + 1, close, MAP_LINE_SIZE);

    return true;
}

/**
 * @brief      Split the arguments of a call at the commas outside quotes.
 *
 * Each one is trimmed, and a string loses its quotes.
 *
 * @param      args       What is between the brackets.
 * @param      arguments  Reads back each argument.
 *
 * @return     - how many arguments there are
 */
static stock SplitMapArgumentsInternal(const args[], arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE]) {
    new
        count,
        length,
        bool:quoted
    ;

    for (new i; args[i] != EOS; ++i) {
        new const
            character = args[i]
        ;

        if (character == '"') {
            quoted = !quoted;

            continue;
        }

        if (character == ',' && !quoted) {
            while (length > 0 && IsMapBlankInternal(arguments[count][length - 1])) {
                --length;
            }

            arguments[count][length] = EOS;
            length = 0;

            if (++count == MAX_MAP_ARGUMENTS) {
                return count;
            }

            continue;
        }

        if (length == 0 && !quoted && IsMapBlankInternal(character)) {
            continue;
        }

        if (length == MAX_MAP_ARGUMENT_SIZE - 1) {
            continue;
        }

        arguments[count][length++] = character;
    }

    while (length > 0 && IsMapBlankInternal(arguments[count][length - 1])) {
        --length;
    }

    arguments[count][length] = EOS;

    if (count == 0 && length == 0) {
        return 0;
    }

    return count + 1;
}

/**
 * @brief      Read a whole number written in decimal or as `0x` hexadecimal.
 *
 * @param      argument  Text to read.
 *
 * @return     - the number
 */
static stock ReadMapIntegerInternal(const argument[]) {
    if (argument[0] != '0') {
        return strval(argument);
    }

    if (argument[1] != 'x' && argument[1] != 'X') {
        return strval(argument);
    }

    new
        value
    ;

    for (new i = 2; argument[i] != EOS; ++i) {
        new const
            character = argument[i]
        ;

        if ('0' <= character <= '9') {
            value = (value << 4) | (character - '0');

            continue;
        }

        if ('a' <= character <= 'f') {
            value = (value << 4) | (character - 'a' + 10);

            continue;
        }

        if ('A' <= character <= 'F') {
            value = (value << 4) | (character - 'A' + 10);

            continue;
        }

        break;
    }

    return value;
}

/**
 * @brief      Read a material size, as its number or as the name of its
 *             constant.
 *
 * @param      argument  Text to read.
 *
 * @return     - the size
 *             - `OBJECT_MATERIAL_SIZE_256x128` when it is neither
 */
static stock ReadMapMaterialSizeInternal(const argument[]) {
    if ('0' <= argument[0] <= '9') {
        return strval(argument);
    }

    for (new i = sizeof (gMapMaterialSizeName) - 1; i != -1; --i) {
        if (strfind(argument, gMapMaterialSizeName[i]) != -1) {
            return (i + 1) * 10;
        }
    }

    return _:OBJECT_MATERIAL_SIZE_256x128;
}

/**
 * @brief      Turn `\n` written in a material text into a new line.
 *
 * @param      text  Text to change, in place.
 */
static stock ReadMapTextInternal(text[]) {
    for (new i; text[i] != EOS; ++i) {
        if (text[i] != '\\') {
            continue;
        }

        if (text[i + 1] != 'n') {
            continue;
        }

        strdel(text, i, i + 1);
        text[i] = '\n';
    }
}

/**
 * @brief      Put a text on the last object made.
 *
 * `SetObjectMaterialText` writes the text before the material index and
 * `SetDynamicObjectMaterialText` after it. Everything from the size on is in the
 * same place in both, and what is left out takes the streamer's default.
 *
 * @param      objectid   Object to write on.
 * @param      arguments  Arguments of the line. The text is changed in place.
 * @param      count      How many it has.
 * @param      index      Which argument is the material index.
 * @param      text       Which argument is the text.
 */
static stock SetMapMaterialTextInternal(STREAMER_TAG_OBJECT:objectid, arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE], count, index, text) {
    if (count <= text) {
        return;
    }

    new
        materialSize = _:OBJECT_MATERIAL_SIZE_256x128,
        font[MAX_MAP_ARGUMENT_SIZE] = "Arial",
        fontSize = 24,
        bold = 1,
        fontColour = 0xFFFFFFFF,
        backColour,
        alignment
    ;

    if (count > 3) {
        materialSize = ReadMapMaterialSizeInternal(arguments[3]);
    }

    if (count > 4) {
        strcopy(font, arguments[4]);
    }

    if (count > 5) {
        fontSize = strval(arguments[5]);
    }

    if (count > 6) {
        bold = strval(arguments[6]);
    }

    if (count > 7) {
        fontColour = ReadMapIntegerInternal(arguments[7]);
    }

    if (count > 8) {
        backColour = ReadMapIntegerInternal(arguments[8]);
    }

    if (count > 9) {
        alignment = strval(arguments[9]);
    }

    ReadMapTextInternal(arguments[text]);

    SetDynamicObjectMaterialText(objectid, strval(arguments[index]), arguments[text], materialSize, font, fontSize, bold, fontColour, backColour, alignment);
}

/**
 * @brief      Whether a call makes an object.
 *
 * `CreateObject`, `CreateDynamicObject`, and any other name that starts with
 * Create and ends with Object. `CreatePlayerObject` is not one: its first
 * argument is a player.
 *
 * @param      name  Name of the call.
 *
 * @return     - `true` it makes an object
 *             - `false` it does not
 */
static stock bool:IsMapObjectCallInternal(const name[]) {
    new const
        length = strlen(name)
    ;

    if (length < 12) {
        return false;
    }

    if (!strequal(name, "Create", false, 6)) {
        return false;
    }

    if (!strequal(name[length - 6], "Object")) {
        return false;
    }

    return !strequal(name, "CreatePlayerObject");
}

/**
 * @brief      Make the object a line asks for.
 *
 * `CreateObject` takes a draw distance after the rotation. Every other call is
 * read as `CreateDynamicObject`: world, interior, player, stream distance and
 * draw distance, where a world or interior of `-1` or none at all takes the
 * file's.
 *
 * @param      name            Name of the call.
 * @param      arguments       Its arguments.
 * @param      count           How many it has.
 * @param      worldid         The file's world.
 * @param      interiorid      The file's interior.
 * @param      streamDistance  The file's stream distance.
 *
 * @return     - the object
 *             - `INVALID_STREAMER_ID` the line has too few arguments, or the
 *               streamer refused it
 */
static stock STREAMER_TAG_OBJECT:CreateMapObjectInternal(const name[], const arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE], count, worldid, interiorid, Float:streamDistance) {
    if (count < 7) {
        return STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    }

    new
        world = worldid,
        interior = interiorid,
        playerid = -1,
        Float:stream = streamDistance,
        Float:draw = STREAMER_OBJECT_DD
    ;

    if (strequal(name, "CreateObject")) {
        if (count > 7) {
            draw = floatstr(arguments[7]);
        }
    } else {
        if (count > 7 && strval(arguments[7]) != -1) {
            world = strval(arguments[7]);
        }

        if (count > 8 && strval(arguments[8]) != -1) {
            interior = strval(arguments[8]);
        }

        if (count > 9) {
            playerid = strval(arguments[9]);
        }

        if (count > 10) {
            stream = floatstr(arguments[10]);
        }

        if (count > 11) {
            draw = floatstr(arguments[11]);
        }
    }

    return CreateDynamicObject(
        strval(arguments[0]),
        floatstr(arguments[1]),
        floatstr(arguments[2]),
        floatstr(arguments[3]),
        floatstr(arguments[4]),
        floatstr(arguments[5]),
        floatstr(arguments[6]),
        world,
        interior,
        playerid,
        stream,
        draw
    );
}

/**
 * @brief      Add the custom model a line asks for, unless its id is taken.
 *
 * @param      arguments  Arguments of the `AddSimpleModel` line: world, base
 *                        model, new model, dff and txd.
 * @param      count      How many it has.
 *
 * @return     - `true` it is added
 *             - `false` when:
 *                 + the line has too few arguments
 *                 + the id is already a custom model
 *                 + the server refused it
 */
static stock bool:AddMapModelInternal(const arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE], count) {
    if (count < 5) {
        return false;
    }

    new const
        modelid = strval(arguments[2])
    ;

    if (IsValidCustomModel(modelid)) {
        return false;
    }

    return AddSimpleModel(strval(arguments[0]), strval(arguments[1]), modelid, arguments[3], arguments[4]);
}

/**
 * @brief      Remove the building of a `RemoveBuildingForPlayer` line.
 *
 * @param      arguments  Arguments of the line.
 * @param      count      How many it has.
 *
 * @return     - `true` it was kept
 *             - `false` when:
 *                 + the line has too few arguments
 *                 + there are already `MAX_MAP_REMOVALS`
 */
static stock bool:AddMapRemovalInternal(const arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE], count) {
    if (count < 6) {
        return false;
    }

    return RemoveMapBuilding(strval(arguments[1]), floatstr(arguments[2]), floatstr(arguments[3]), floatstr(arguments[4]), floatstr(arguments[5]));
}

/**
 * # External
 */

stock LoadMap(const filename[], worldid = -1, interiorid = -1, STREAMER_TAG_OBJECT:objects[] = { STREAMER_TAG_OBJECT:INVALID_STREAMER_ID }, size = 0) {
    new const
        File:handle = fopen(filename, io_read)
    ;

    if (!handle) {
        return -1;
    }

    new
        line[MAP_LINE_SIZE],
        name[MAX_MAP_CALL_NAME],
        args[MAP_LINE_SIZE],
        arguments[MAX_MAP_ARGUMENTS][MAX_MAP_ARGUMENT_SIZE],

        world = worldid,
        interior = interiorid,
        Float:streamDistance = MAP_DEFAULT_STREAM_DISTANCE,

        STREAMER_TAG_OBJECT:objectid = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID,
        made
    ;

    while (fread(handle, line)) {
        if (!SplitMapLineInternal(line, name, args)) {
            continue;
        }

        new const
            count = SplitMapArgumentsInternal(args, arguments)
        ;

        if (IsMapObjectCallInternal(name)) {
            objectid = CreateMapObjectInternal(name, arguments, count, world, interior, streamDistance);

            if (objectid == STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
                continue;
            }

            if (made < size) {
                objects[made] = objectid;
            }

            ++made;

            continue;
        }

        if (strequal(name, "options")) {
            if (count < 3) {
                continue;
            }

            world = strval(arguments[0]);
            interior = strval(arguments[1]);
            streamDistance = floatstr(arguments[2]);

            continue;
        }

        if (strequal(name, "RemoveBuildingForPlayer")) {
            AddMapRemovalInternal(arguments, count);

            continue;
        }

        if (strequal(name, "AddSimpleModel")) {
            AddMapModelInternal(arguments, count);

            continue;
        }

        if (objectid == STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
            continue;
        }

        if (strequal(name, "SetObjectMaterial") || strequal(name, "SetDynamicObjectMaterial")) {
            if (count < 5) {
                continue;
            }

            new
                colour
            ;

            if (count > 5) {
                colour = ReadMapIntegerInternal(arguments[5]);
            }

            SetDynamicObjectMaterial(objectid, strval(arguments[1]), strval(arguments[2]), arguments[3], arguments[4], colour);

            continue;
        }

        if (strequal(name, "SetObjectMaterialText")) {
            SetMapMaterialTextInternal(objectid, arguments, count, 2, 1);

            continue;
        }

        if (strequal(name, "SetDynamicObjectMaterialText")) {
            SetMapMaterialTextInternal(objectid, arguments, count, 1, 2);
        }
    }

    fclose(handle);

    return made;
}

stock bool:RemoveMapBuilding(modelid, Float:x, Float:y, Float:z, Float:radius) {
    if (gMapRemovalCount == MAX_MAP_REMOVALS) {
        return false;
    }

    new const
        index = gMapRemovalCount++
    ;

    gMapRemoval[index][E_MAP_REMOVAL_MODEL]  = modelid;
    gMapRemoval[index][E_MAP_REMOVAL_X]      = x;
    gMapRemoval[index][E_MAP_REMOVAL_Y]      = y;
    gMapRemoval[index][E_MAP_REMOVAL_Z]      = z;
    gMapRemoval[index][E_MAP_REMOVAL_RADIUS] = radius;

    foreach (new i : Player) {
        RemoveBuildingForPlayer(i, modelid, x, y, z, radius);
    }

    call OnMapBuildingRemoved(modelid, x, y, z, radius);

    return true;
}

stock GetMapRemovalCount() {
    return gMapRemovalCount;
}

/**
 * # Calls
 */

hook OnPlayerConnect(playerid) {
    for (new i; i != gMapRemovalCount; ++i) {
        RemoveBuildingForPlayer(playerid,
            gMapRemoval[i][E_MAP_REMOVAL_MODEL],
            gMapRemoval[i][E_MAP_REMOVAL_X],
            gMapRemoval[i][E_MAP_REMOVAL_Y],
            gMapRemoval[i][E_MAP_REMOVAL_Z],
            gMapRemoval[i][E_MAP_REMOVAL_RADIUS]
        );
    }

    return 1;
}

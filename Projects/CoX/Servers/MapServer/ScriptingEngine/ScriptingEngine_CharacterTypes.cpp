/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2019 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#include "DataHelpers.h"
#include "Common/GameData/Character.h"
#include "Common/GameData/CharacterHelpers.h"
#include "Common/GameData/Contact.h"
#include "Common/GameData/Entity.h"
#include "Common/GameData/Contact.h"
#include "Common/GameData/Task.h"
#include "ScriptingEngine.h"
#include "MapInstance.h"

/*!
 * @brief Initializes types related to characters and gameplay for the Lua scripting engine. Creates the Player table
 *        and defines the functions that can be called on it.
 */
void ScriptingEngine::register_CharacterTypes()
{
    // Clue
    m_private->m_lua.new_usertype<Clue>("Clue",
        sol::constructors<Clue()>(),
        "name", sol::property(&Clue::getName, &Clue::setName),
        "displayName", sol::property(&Clue::getDisplayName, &Clue::setDisplayName),
        "detail", sol::property(&Clue::getDetailText, &Clue::setDetailText),
        "iconFile", sol::property(&Clue::getIconFile, &Clue::setIconFile)
    );

    // Contact
    m_private->m_lua.new_usertype<Contact>("Contact",
        // 3 constructors
        sol::constructors<Contact()>(),
        // gets or set the value using member variable syntax
        "name", sol::property(&Contact::getName, &Contact::setName),
        "locationDescription", sol::property(&Contact::getLocationDescription, &Contact::setLocationDescription),
        "npcId", &Contact::m_npc_id,
        "currentStanding", &Contact::m_current_standing,
        "contactIdx", &Contact::m_contact_idx,
        "notifyPlayer", &Contact::m_notify_player,
        "taskIndex", &Contact::m_task_index,
        "hasLocation", &Contact::m_has_location,
        "location", &Contact::m_location,
        "confidantThreshold", &Contact::m_confidant_threshold,
        "friendThreshold", &Contact::m_friend_threshold,
        "completeThreshold", &Contact::m_complete_threshold,
        "canUseCell", &Contact::m_can_use_cell,
        "contactId", &Contact::m_contact_idx,
        "dialogScreenIdx", &Contact::m_dlg_screen,
        "settingTitle", &Contact::m_setting_title
    );

    // Destination
    m_private->m_lua.new_usertype<Destination>("Destination",
        sol::constructors<Destination()>(),
        "pointIdx", &Destination::point_idx,
        "location", &Destination::location,
        "name", sol::property(&Destination::getLocationName, &Destination::setLocationName),
        "mapName", sol::property(&Destination::getLocationMapName, &Destination::setLocationMapName)
    );

    // Hide and Seek
    m_private->m_lua.new_usertype<HideAndSeek>("HideAndSeek",
        sol::constructors<HideAndSeek()>(),
        "foundCount", &HideAndSeek::m_found_count
    );

    // Hunt
    m_private->m_lua.new_usertype<Hunt>("Hunt",
        sol::constructors<Hunt()>(),
        "type", sol::property(&Hunt::getTypeString, &Hunt::setTypeString),
        "count", &Hunt::m_count
    );

    // Relay Race Result
    m_private->m_lua.new_usertype<RelayRaceResult>("RelayRaceResult",
        sol::constructors<RelayRaceResult()>(),
        "segment", &RelayRaceResult::m_segment,
        "lastTime", &RelayRaceResult::m_last_time,
        "bestTime", &RelayRaceResult::m_best_time
    );

    // Souvenir
    m_private->m_lua.new_usertype<Souvenir>("Souvenir",
        sol::constructors<Souvenir()>(),
        "name", sol::property(&Souvenir::getName, &Souvenir::setName),
        "description", sol::property(&Souvenir::getDescription, &Souvenir::setDescription),
        "icon", sol::property(&Souvenir::getIcon, &Souvenir::setIcon)
    );

    // Task Entry
    m_private->m_lua.new_usertype<TaskEntry>("TaskEntry",
        sol::constructors<TaskEntry()>(),
        "dbId", &TaskEntry::m_db_id,
        "taskList", &TaskEntry::m_task_list,
        "resetSelectedTask", &TaskEntry::m_task_list
    );

    // Task
    m_private->m_lua.new_usertype<Task>("Task",
        sol::constructors<Task()>(),
        "dbId", &Task::m_db_id,
        "description", sol::property(&Task::getDescription, &Task::setDescription),
        "owner", sol::property(&Task::getOwner, &Task::setOwner),
        "detail", sol::property(&Task::getDetail, &Task::setDetail),
        "state", sol::property(&Task::getState, &Task::setState),
        "isComplete", &Task::m_is_complete,
        "inProgressMaybe", &Task::m_in_progress_maybe,
        "hasLocation", &Task::m_has_location,
        "isDetailInvalid", &Task::m_detail_invalid,
        "location", &Task::m_location,
        "finishTime", &Task::m_finish_time,
        "taskIdx", &Task::m_task_idx,
        "isAbandoned", &Task::m_is_abandoned,
        "unknownInt1", &Task::m_unknown_1,
        "unknownInt2", &Task::m_unknown_2,
        "boardTrain", &Task::m_board_train
    );

    /* ************* *
     * Player Object *
     * ************* */

    // Create the Player Object itself.
    m_private->m_lua["Player"] = m_private->m_lua.create_table(); // Empty Table aka Object

    // Clear the Player's current target so they are no longer targeting anything.
    m_private->m_lua["Player"]["ClearTarget"] = [this]()
    {
        setTarget(*cl->m_ent, cl->m_ent->m_idx);
    };

    // Close the dialog window the Player currently has with a Contact.
    m_private->m_lua["Player"]["CloseContactDialog"] = [this]()
    {
        sendContactDialogClose(*cl);
    };

    // Set the Player's XP Debt to the passed value.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["SetDebt"] = [this](const int debt)
    {
        setDebt(*cl->m_ent->m_char, debt);
    };

    // Give the Player an amount of XP Debt equal to the passed value.
    m_private->m_lua["Player"]["GiveDebt"] = [this](const int debt)
    {
        giveDebt(*cl, debt);
    };

    // Give the Player the specified Enchancement at the specified Level.
    m_private->m_lua["Player"]["GiveEnhancement"] = [this](const char *name, int level)
    {
        QString e_name = QString::fromUtf8(name);
        giveEnhancement(*cl, e_name, level);
    };

    // Give the Player an amount of Endurance equal to the passed value.
    m_private->m_lua["Player"]["GiveEnd"] = [this](const float end)
    {
        giveEnd(*cl, end);
    };

    // Set the Player's Endurance to the passed value.
    m_private->m_lua["Player"]["SetEnd"] = [this](const float end)
    {
        setEnd(*cl->m_ent->m_char, end);
    };

    // Set the Player's HP to the passed value.
    m_private->m_lua["Player"]["SetHp"] = [this](const float hp)
    {
        setHP(*cl->m_ent->m_char, hp);
    };

    // Give the Player an amount of HP equal to the passed value.
    m_private->m_lua["Player"]["GiveHp"] = [this](const float hp)
    {
        giveHp(*cl, hp);
    };

    // Set the Player's Influence to the passed value.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["SetInf"] = [this](const int inf)
    {
        setInf(*cl->m_ent->m_char, inf);
    };

    // Give the Player an amount of Influence equal to the passed value.
    m_private->m_lua["Player"]["GiveInf"] = [this](const int inf)
    {
        modifyInf(*cl, inf);
    };

    // Give the Player the specified Inspiration.
    m_private->m_lua["Player"]["GiveInsp"] = [this](const char *name)
    {
        QString e_name = QString::fromUtf8(name);
        giveInsp(*cl, e_name);
    };

    // Set the Player's XP to the passed value.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["SetXp"] = [this](const int xp)
    {
        setXP(*cl->m_ent->m_char, xp);
    };

    // Give the Player an amount of XP equal to the passed value.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["GiveXp"] = [this](const int xp)
    {
        giveXp(*cl, xp);
    };

    // Send the specified number of floating damage numbers to display over the specified target.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["SendFloatingDamage"] = [this](const int tgt_idx, const int amount)
    {
        sendFloatingNumbers(*cl, tgt_idx, amount);
    };

    // Cause the Player to face the specified target.
    // TODO: Handle conversion from signed to unsigned int.
    m_private->m_lua["Player"]["FaceEntity"] = [this](const int tgt_idx)
    {
        sendFaceEntity(*cl, tgt_idx);
    };

    // Cause the Player to face the specified location.
    m_private->m_lua["Player"]["FaceLocation"] = [this](glm::vec3 &loc)
    {
        sendFaceLocation(*cl, loc);
    };

    // Add the specified Contact to the Player's Contact list.
    m_private->m_lua["Player"]["AddUpdateContact"] = [this](const Contact &contact)
    {
        updateContactStatusList(*cl, contact);
    };

    // Define the function that will be called with the dialog button is pressed.
    m_private->m_lua["Player"]["SetActiveDialogCallback"] = [this](std::function<void(int)> callback)
    {
        cl->m_ent->setActiveDialogCallback(callback);
    };

    // Remove the specified Contact from the Player's Contact list.
    m_private->m_lua["Player"]["RemoveContact"] = [this](const Contact &contact)
    {
        removeContact(*cl, contact);
    };

    // Send the specified task's details to the Player.
    m_private->m_lua["Player"]["UpdateTaskDetail"] = [this](const Task &task)
    {
        updateTaskDetail(*cl, task);
    };

    // Add the specified list of tasks to the Player's task list.
    m_private->m_lua["Player"]["AddListOfTasks"] = [this](const sol::as_table_t<std::vector<Task>> task_list)
    {
        const auto& listMap = task_list.source;
        vTaskList listToSend;
        for (const auto& kvp : listMap)
        {
          listToSend.push_back(kvp);
        }
        addListOfTasks(cl, listToSend);
    };

    // Add the specified task to the Player's task list.
    m_private->m_lua["Player"]["AddUpdateTask"] = [this](const Task &task)
    {
        sendUpdateTaskStatusList(*cl, task);
    };

    // Remove the specified task from the Player's task list.
    m_private->m_lua["Player"]["RemoveTask"] = [this](const Task &task)
    {
        removeTask(*cl, task);
    };

    // Make the specified task the Player's "selected task," thus making it appear red on the compass and map.
    m_private->m_lua["Player"]["SelectTask"] = [this](const Task &task)
    {
        selectTask(*cl, task);
    };

    // Start a timer for the specified length with the specified message.
    m_private->m_lua["Player"]["StartMissionTimer"] = [this](const char *message, float timer)
    {
        QString mess = QString::fromUtf8(message);
        sendMissionObjectiveTimer(*cl, mess, timer);
    };

    // Sets the Player's waypoint to the specifed location.
    m_private->m_lua["Player"]["SetWaypoint"] = [this](const int point_idx, glm::vec3 loc)
    {
        sendWaypoint(*cl, point_idx, loc);
    };

    // Causes the Player to immediately level up.
    m_private->m_lua["Player"]["LevelUp"] = [this]()
    {
        playerTrain(*cl);
    };

    // Open the Player's title selection window. Currently seems to only set the Player's title to their origin title.
    m_private->m_lua["Player"]["OpenTitleMenu"] = [this]()
    {
        QString origin = getOriginTitle(*cl->m_ent->m_char);
        setTitle(*cl, origin);
    };

    // Give the Player the specified temporary power.
    m_private->m_lua["Player"]["GiveTempPower"] = [this](const char *power)
    {
        giveTempPower(cl, power);
    };

    // Add the specified Clue to the Player's inventory.
    m_private->m_lua["Player"]["AddClue"] = [this](const Clue clue)
    {
        addClue(*cl, clue);
    };

    // Remove the specified Clue from the Player's inventory.
    m_private->m_lua["Player"]["RemoveClue"] = [this](const Clue clue)
    {
        removeClue(*cl, clue);
    };

    // Add the specified Souvenir from the Player's inventory.
    m_private->m_lua["Player"]["AddSouvenir"] = [this](const Souvenir souvenir)
    {
        addSouvenir(*cl, souvenir);
    };

    // Remove the specified Souvenir from the Player's inventory.
    m_private->m_lua["Player"]["RemoveSouvenir"] = [this](const Souvenir souvenir)
    {
        removeSouvenir(*cl, souvenir);
    };

    // Immediately revive the Player on the spot without returning to a Hospital. Different values for revive_lvl
    // result in different restoration values for HP and Endurance.
    m_private->m_lua["Player"]["Revive"] = [this](const int revive_lvl)
    {
        revive(cl, revive_lvl);
    };

    // Immediately respawn the player at the specified location.
    m_private->m_lua["Player"]["Respawn"] = [this](const char *loc_name)
    {
        respawn(*cl, loc_name);
    };

    // Add the specified number of points to the Player's Hide and Seek score.
    m_private->m_lua["Player"]["AddHideAndSeekPoint"] = [this](int points)
    {
        addHideAndSeekResult(*cl, points);
    };

    // Add the specified Relay Race result to the Player.
    m_private->m_lua["Player"]["AddRelayRaceResult"] = [this](RelayRaceResult *raceResult)
    {
        addRelayRaceResult(*cl, *raceResult);
    };

    // Get the specified Relay Race result from the Player.
    m_private->m_lua["Player"]["GetRelayRaceResult"] = [this](int segment)
    {
        return getRelayRaceResult(*cl, segment);
    };
}

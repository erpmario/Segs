/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#ifndef SCRIPTINGENGINE_H
#define SCRIPTINGENGINE_H
#include <memory>
#include <string>
#include "Common/GameData/Contact.h"

class QString;
struct MapClientSession;

class ScriptingEngine
{
public:
    ScriptingEngine();
    ~ScriptingEngine();
    void registerTypes();
    int loadAndRunFile(const QString &path);
    std::string callFuncWithClientContext(MapClientSession *client,const char *name,int arg1);
    std::string callFuncWithClientContext(MapClientSession *client,const char *name,int arg1, glm::vec3 loc);
    std::string callFuncWithClientContext(MapClientSession *client, const char *name, const char *arg1, glm::vec3 loc);
    std::string callFunc(const char *name,int arg1);
    std::string callFunc(const char *name,int arg1, glm::vec3 loc);
    std::string callFunc(const char *name, const char *arg1, glm::vec3 loc);
    std::string callFunc(const char *name, std::vector<Contact> contact_list);
    int runScript(const QString &script_contents,const char *script_name="unnamed script");
    int runScript(MapClientSession *client,const QString &script_contents,const char *script_name="unnamed script");
    bool setIncludeDir(const QString &path);
private:
#ifdef SCRIPTING_ENABLED
    struct ScriptingEnginePrivate;
    std::unique_ptr<ScriptingEnginePrivate> m_private;
#endif
};

#endif // SCRIPTINGENGINE_H

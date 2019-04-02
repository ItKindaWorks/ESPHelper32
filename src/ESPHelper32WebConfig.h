/*
ESPHelper32WebConfig.h
Copyright (c) 2019 ItKindaWorks All right reserved.
github.com/ItKindaWorks

This file is part of ESPHelper32

ESPHelper32 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ESPHelper32 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ESPHelper32.  If not, see <http://www.gnu.org/licenses/>.
*/



#ifndef ESPHELPER32_WEBCONFIG_H
#define ESPHELPER32_WEBCONFIG_H

#include "ESPHelper32.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>


class ESPHelper32WebConfig{

public:
	ESPHelper32WebConfig(int port, const char* URI);  //constructor
    ESPHelper32WebConfig(WebServer *server, const char* URI);

    bool begin(const char* hostname);
    bool begin();

    void fillConfig(netInfo* fillInfo);

    bool handle();

    netInfo getConfig();

    void setSpiffsReset(const char* uri);


private:
    void handleGet();
    void handlePost();
    void handleNotFound();
    void handleReset();

    WebServer *_server;
    WebServer _localServer;

    char _newSsid[64];
    char _newNetPass[64];
    char _newOTAPass[64];
    char _newHostname[64];
    char _newMqttHost[64];
    char _newMqttUser[64];
    char _newMqttPass[64];
    int _newMqttPort;

    const char* _resetURI;
    const char* _pageURI;

    netInfo* _fillData;
    bool _preFill = false;

    bool _resetSet = false;

    netInfo _config;
    bool _configLoaded = false;
    bool _runningLocal = false;


};

#endif

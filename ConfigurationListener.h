/**
 * \file   ConfigurationListener.h
 * \author Le Borgne
 *
 * \date Created on 20 février 2015, 18:03
 * 
 * Copyright (C) 2015 Laurent Le Borgne, <laurent.leborgne@neavia.com>
 * 
 */

#ifndef CONFIGURATIONLISTENER_H
#define	CONFIGURATIONLISTENER_H

#include <map>
#include <string>

using namespace std;

class Configuration;

class ConfigurationListener {
    
public:
    
    virtual ~ConfigurationListener() {};
    
    /**
     * Callback appelé lorsq'une section du fichier de configuration à changée
     * @param module    Nom de la section/module
     * @param cfg       Configuration
     */
    virtual void CfgChange ( string module, Configuration &cfg ) = 0;
};

#endif	/* CONFIGURATIONLISTENER_H */


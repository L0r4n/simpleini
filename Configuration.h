/**
 * \file   Configuration.h
 * \author Le Borgne
 *
 * \date Created on 20 février 2015, 18:03
 * 
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <vector>
#include <string>
#include "ConfigurationListener.h"

using namespace std;

class Configuration {
    
public:
    
    virtual ~Configuration() {};
    
    virtual bool addListener ( string section, ConfigurationListener* listener) = 0;
    virtual bool removeListener ( string section, ConfigurationListener* listener) = 0;
    
    /**
     * Récupère la valeur d'une section/clef en un tableau
     * @param Section   Nom de la section
     * @param Key       Nom de la clef
     * @param Default   Valeur par defaut
     * @return  Tableau contenant la valeur
     */
    virtual const char * GetValue(
        const char *Section, 
        const char *Key, 
        const char *Default = NULL 
        ) const = 0;
    
    virtual long GetLongValue(
        const char *Section, 
        const char *Key, 
        long  Default = 0
        ) const = 0;
    
    virtual double GetDoubleValue(
        const char *Section,
        const char *Key,
        double Default = 0
        ) const = 0 ;

    virtual bool GetBoolValue(
        const char *Section,
        const char *Key,
        bool  Default = false
        ) const = 0;
    
    virtual int SetValue(
        const char *Section,
        const char *Key,
        const char *Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        ) = 0;

    virtual int SetLongValue(
        const char *Section,
        const char *Key,
        long Value,
        const char *Comment = NULL,
        bool UseHex = false,
        bool ForceReplace = false,
        bool Save = true
        ) = 0;
    
    virtual int SetDoubleValue(
        const char *Section,
        const char *Key,
        double Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        ) = 0;

    virtual int SetBoolValue(
        const char *Section,
        const char *Key,
        bool Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        ) = 0;
    
    virtual string getRootPath() = 0;

};


#endif	/* CONFIGURATION_H */


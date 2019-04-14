/**
 * \file   ConfigurationImpl.h
 * \author Le Borgne
 *
 * \date Created on 20 février 2015, 18:08
 * 
 */

#ifndef CONFIGURATIONIMPL_H
#define	CONFIGURATIONIMPL_H

#include "ConfigurationListener.h"
#include "Configuration.h"
#include "SimpleIni.h"
#include <vector>
#include <pthread.h>
#include <set>

class ConfigurationImpl: public CSimpleIni::CSimpleIniEvent, public Configuration {
    
public:
    ConfigurationImpl( string file);
    virtual ~ConfigurationImpl();
    
    virtual bool addListener ( string section, ConfigurationListener* listener);
    virtual bool removeListener ( string section, ConfigurationListener* listener);
    virtual int CSimpleIniChange(CSimpleIni& r_CSimpleIni);
    
    virtual const char * GetValue(
        const char *Section, 
        const char *Key, 
        const char *Default = NULL 
    ) const;
    
    virtual long GetLongValue(
        const char *Section, 
        const char *Key, 
        long  Default = 0
    ) const;
    
    virtual double GetDoubleValue(
        const char *Section,
        const char *Key,
        double Default = 0
        ) const;
    
    virtual bool GetBoolValue(
        const char *Section,
        const char *Key,
        bool  Default = false
        ) const;
    
    virtual int SetValue(
        const char *Section,
        const char *Key,
        const char *Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        );
    
    virtual int SetLongValue(
        const char *Section,
        const char *Key,
        long Value,
        const char *Comment = NULL,
        bool UseHex = false,
        bool ForceReplace = false,
        bool Save = true
        );
    
    virtual int SetDoubleValue(
        const char *Section,
        const char *Key,
        double Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        );
    
    virtual int SetBoolValue(
        const char *Section,
        const char *Key,
        bool Value,
        const char *Comment = NULL,
        bool ForceReplace = false,
        bool Save = true
        );

    virtual string getRootPath();
    
private:
    
    string iniFile;
    CSimpleIniA simpleIni;
    multimap<string,ConfigurationListener*> listeners;
    pthread_mutex_t m_MutexListeners;
    
    void notifyChange ( string section );
    void saveFile();
    
};

#endif	/* CONFIGURATIONIMPL_H */


/**
 * \file   Configuration.cpp
 * \author Le Borgne
 *
 * \date Created on 20 février 2015, 18:08
 * 
 */

#include "ConfigurationImpl.h"
#include "sys/stat.h"
#include <unistd.h>

ConfigurationImpl::ConfigurationImpl( string file): iniFile(file) {
    
    pthread_mutex_init(&this->m_MutexListeners, NULL);
    
    simpleIni.Reset();
    simpleIni.LoadFile( this->iniFile.c_str() );
    
    simpleIni.SetCallbackEvent( this );
    
    simpleIni.StartCheckFile();
}

ConfigurationImpl::~ConfigurationImpl() {
    
    simpleIni.Reset();
}

int ConfigurationImpl::CSimpleIniChange(CSimpleIniA& r_CSimpleIni) {

    CSimpleIni::TSectionParameters change = r_CSimpleIni.GetSectionsChange();
    
    if ( !change.empty() ) {
        printf ("CSimpleIniChange::change !\n" );
        
        for ( typename CSimpleIni::TSectionParameters::iterator it = change.begin();
                it != change.end();
                it ++ ) {
            
            notifyChange ( (*it).first );
        }
    }
    
    printf ("CSimpleIniChange::Date file = %ld\n", r_CSimpleIni.GetFileDate() );
    
    return 0;
}

void ConfigurationImpl::notifyChange ( string section ) {
    
    pthread_mutex_lock(&this->m_MutexListeners);
    multimap<string,ConfigurationListener*>_listeners = this->listeners;
    pthread_mutex_unlock(&this->m_MutexListeners);
    
    for ( multimap<string,ConfigurationListener*>::iterator it = _listeners.begin();
            it != _listeners.end();
            it++ ) {

        //DEBUG("listener [%s]", it->first.c_str());

        if ( it->first.compare(section) == 0 ) {

            it->second->CfgChange( it->first, *this );
        }
    }
}

void ConfigurationImpl::saveFile() {
    
    this->simpleIni.SaveFile( this->iniFile.c_str() );
}

string ConfigurationImpl::getRootPath() {

    std::string rootPath = this->iniFile.substr(0, this->iniFile.rfind('/') + 1);
    return rootPath;
}

const char * ConfigurationImpl::GetValue(const char *Section, const char *Key, const char *Default ) const {
    return this->simpleIni.GetValue(Section, Key, Default);
}

long ConfigurationImpl::GetLongValue(const char *Section, const char *Key, long  Default) const {
    return this->simpleIni.GetLongValue(Section, Key, Default);
}

double ConfigurationImpl::GetDoubleValue(
        const char *Section,
        const char *Key,
        double Default
        ) const {
    return this->simpleIni.GetDoubleValue(Section, Key, Default);
}

 bool ConfigurationImpl::GetBoolValue(
        const char *Section,
        const char *Key,
        bool  Default
        ) const {
     return this->simpleIni.GetBoolValue( Section, Key, Default );
 }

int ConfigurationImpl::SetValue(
        const char *Section,
        const char *Key,
        const char *Value,
        const char *Comment,
        bool ForceReplace,
        bool Save
        ) {
    
    int ret = (int) this->simpleIni.SetValue(Section, Key, Value, Comment, ForceReplace);
    
    if ( ret >= 0 ) {
        if (Save) this->saveFile();
        this->notifyChange( Section );
    }
    
    return (int) ret;
}

int ConfigurationImpl::SetLongValue(
        const char *Section,
        const char *Key,
        long Value,
        const char *Comment,
        bool UseHex,
        bool ForceReplace,
        bool Save
        ) {
    
    int ret = (int) this->simpleIni.SetLongValue( Section, Key, Value, Comment, UseHex, ForceReplace);
    
    if ( ret >= 0 ) {
        if (Save) this->saveFile();
        this->notifyChange( Section );
    }
    
    return (int) ret;
}

int ConfigurationImpl::SetDoubleValue(
        const char *Section,
        const char *Key,
        double Value,
        const char *Comment,
        bool ForceReplace,
        bool Save
        ) {
    
    int ret = (int) this->simpleIni.SetDoubleValue(Section, Key, Value, Comment, ForceReplace);
    
    if ( ret >= 0 ) {
        if (Save) this->saveFile();
        this->notifyChange( Section );
    }
    
    return (int) ret;
}

 int ConfigurationImpl::SetBoolValue(
        const char *Section,
        const char *Key,
        bool Value,
        const char *Comment,
        bool ForceReplace,
        bool Save
        ) {
    
    int ret = (int) this->simpleIni.SetBoolValue( Section, Key, Value, Comment, ForceReplace);
    
    if ( ret >= 0 ) {
        if (Save) this->saveFile();
        this->notifyChange( Section );
    }
    
    return (int) ret;
 }

bool ConfigurationImpl::removeListener ( string section, ConfigurationListener* listener) {
    
    bool ret = false;
    
    pthread_mutex_lock(&this->m_MutexListeners);
    multimap<string,ConfigurationListener*>::iterator ref = this->listeners.end();
    for ( multimap<string,ConfigurationListener*>::iterator it = this->listeners.begin();
            it != this->listeners.end();
            it++ ) {
        if ( it->first == section && it->second == listener ) {
            ref = it;
            break;
        }
    }
    if ( ref != this->listeners.end() ) {
        this->listeners.erase( ref );
        ret = true;
    }
    pthread_mutex_unlock(&this->m_MutexListeners);

    return ret;
}

bool ConfigurationImpl::addListener ( string section, ConfigurationListener* listener) {
    
    bool ret = false, find = false;
    
    pthread_mutex_lock(&this->m_MutexListeners);
    for ( multimap<string,ConfigurationListener*>::iterator it = this->listeners.begin();
            it != this->listeners.end();
            it++ ) {
        if ( it->first == section && it->second == listener ) {
            find = true;
            break;
        }        
    }
    if ( !find ) {
        this->listeners.insert ( std::pair<string,ConfigurationListener*>(section,listener) );
        ret = true;
    }
    pthread_mutex_unlock(&this->m_MutexListeners);
    
    return ret;
}

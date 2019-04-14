/* 
 * File:   TestEvent.h
 * Author: La0r4ns
 *
 * Created on 23 janvier 2017, 21:06
 */

#ifndef TESTEVENT_H
#define	TESTEVENT_H

#include "ConfigurationImpl.h"

class TestEvent: public CSimpleIni::CSimpleIniEvent, public ConfigurationListener {
public:
    TestEvent();
    virtual ~TestEvent();
    

    virtual int CSimpleIniChange(CSimpleIni& r_CSimpleIni);
    virtual void CfgChange ( string module, Configuration &cfg );
    
private:
    CSimpleIni simpleIni;
    
    ConfigurationImpl *m_configuration;

};

#endif	/* TESTEVENT_H */


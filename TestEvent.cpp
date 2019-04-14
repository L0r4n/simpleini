/* 
 * File:   TestEvent.cpp
 * Author: La0r4ns
 * 
 * Created on 23 janvier 2017, 21:06
 */

#include "TestEvent.h"

#include <stdio.h>
#include <stdlib.h>

TestEvent::TestEvent() {
    
    m_configuration = new ConfigurationImpl("test.ini");
    
    m_configuration->addListener ( "section", this );
    
    simpleIni.Reset();
    simpleIni.LoadFile( "test.ini" );
    
    printf ("Date file = %ld\n", simpleIni.GetFileDate() );
    
    simpleIni.SetCallbackEvent( this );
    
    simpleIni.StartCheckFile();
}

TestEvent::~TestEvent() {
    
    if ( m_configuration != NULL ) {
        delete m_configuration;
    }
}

void TestEvent::CfgChange ( string module, Configuration &cfg ) {
    
}

int TestEvent::CSimpleIniChange(CSimpleIni& r_CSimpleIni) {

    CSimpleIni::TSectionParameters change = r_CSimpleIni.GetSectionsChange();
    
    if ( !change.empty() ) {
        printf ("CSimpleIniChange::change !\n" );
        
        for ( typename CSimpleIni::TSectionParameters::iterator it = change.begin();
                it != change.end();
                it ++ ) {
            
            for ( std::list<std::string>::iterator it2 = (*it).second.begin();
                    it2 != (*it).second.end();
                    it2++ ) {
                
                printf ("[%s]%s\n", (*it).first.c_str(), (*it2).c_str() );
            }
        }
    }
    
    printf ("CSimpleIniChange::Date file = %ld\n", r_CSimpleIni.GetFileDate() );
    
    return 0;
}

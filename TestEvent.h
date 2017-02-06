/* 
 * File:   TestEvent.h
 * Author: La0r4ns
 *
 * Created on 23 janvier 2017, 21:06
 */

#ifndef TESTEVENT_H
#define	TESTEVENT_H

#include "SimpleIni.h"

class TestEvent: public CSimpleIni::CSimpleIniEvent {
public:
    TestEvent();
    virtual ~TestEvent();
    

    virtual int CSimpleIniChange(CSimpleIni& r_CSimpleIni);
    
private:
    CSimpleIni simpleIni;

};

#endif	/* TESTEVENT_H */


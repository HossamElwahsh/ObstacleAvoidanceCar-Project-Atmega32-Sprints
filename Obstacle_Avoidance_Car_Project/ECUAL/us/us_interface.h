/*
 * us_interface.h
 *
 * Created: 15/5/2023 4:24:25 PM
 *  Author: hossam
 */ 


#ifndef US_INTERFACE_H_
#define US_INTERFACE_H_

void US_init(u8 u8_a_triggerPin, u8 u8_a_echoPin);
float US_getDistance(void); // sends a pulse, blocks till timestamp receive > calc dist
void US_evtDistance(); // callback received distance (update flag & lastDist)

#endif /* US_INTERFACE_H_ */
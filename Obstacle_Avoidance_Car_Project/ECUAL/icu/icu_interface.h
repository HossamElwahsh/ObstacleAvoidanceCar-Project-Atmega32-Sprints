/*
 * icu_interface.h
 *
 * Created: 15/5/2023 4:24:07 PM
 *  Author: hossam
 */ 


#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

void ICU_init(u8 u8_a_echoPin, void (* vp_a_callback));
void ICU_getCaptureValue(void);

#endif /* ICU_INTERFACE_H_ */
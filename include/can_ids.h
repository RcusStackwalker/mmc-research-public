#ifndef CAN_IDS_H
#define CAN_IDS_H


#define CAN_Z37A_2005_AC_TO_ENGINE		0x443 //rx0 in z37a'05
#define CAN_Z37A_2005_IMMO_TO_ENGINE		0x111 //rx11
#define CAN_Z37A_2005_ASC_TO_ENGINE		0x300 //rx5
#define CAN_Z37A_2005_ABS_TO_ENGINE		0x200 //rx9
#define CAN_Z37A_2005_EPS_TO_ENGINE		0x2f1 //rx6

//[be_uint16_t:fuel_level][be_uint24_t:odometer]
#define CAN_Z37A_2005_METER_TO_ENGINE1		0x412 //rx2


#endif /*CAN_IDS_H*/

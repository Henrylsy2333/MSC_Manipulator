#ifndef   _NEX_ROBOT_ERRORS_H_
#define   _NEX_ROBOT_ERRORS_H_


#define NER_ERR_NOERR                          ( 0 )  // Success, no error.

#define NER_ERR_DRIVER_HAS_ALARM               (-1)
#define NER_ERR_EMG_STOP                       (-2)


#define NER_ERR_MOTION_BASE                    (-1000)

// Error codes for NER_Robot_MoveLine
#define NER_ERR_TARGETPOS_OVERWORKSPACE        (-1 + NER_ERR_MOTION_BASE )
#define NER_ERR_TARGETPOS_IS_SIGULAR_POINT     (-2 + NER_ERR_MOTION_BASE )
#define NER_ERR_TARGETPOS_OVERAXISLIMIT        (-3 + NER_ERR_MOTION_BASE )
#define NER_ERR_CREATE_LINE_BUFFER_FAILED      (-4 + NER_ERR_MOTION_BASE )

#endif
/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.2-dev */

#ifndef PB_PROTO_GENERAL_RGB_INSTRUCTIONS_PB_H_INCLUDED
#define PB_PROTO_GENERAL_RGB_INSTRUCTIONS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _GeneralRGBData_RGBMessageType {
    GeneralRGBData_RGBMessageType_MATRIX_CYCLE_INDIVIDUAL = 0,
    GeneralRGBData_RGBMessageType_MATRIX_CYCLE_ALL = 1,
    GeneralRGBData_RGBMessageType_MATRIX_STATIC_INDIVIDUAL = 2,
    GeneralRGBData_RGBMessageType_MATRIX_KEYTRIGGER_REACTIVE = 3,
    GeneralRGBData_RGBMessageType_MATRIX_TRIGGER_RIPPLE = 4
} GeneralRGBData_RGBMessageType;

/* Struct definitions */
typedef struct _GeneralRGBData {
    uint32_t message_size;
    GeneralRGBData_RGBMessageType message_type;
    bool more_data;
} GeneralRGBData;


/* Helper constants for enums */
#define _GeneralRGBData_RGBMessageType_MIN GeneralRGBData_RGBMessageType_MATRIX_CYCLE_INDIVIDUAL
#define _GeneralRGBData_RGBMessageType_MAX GeneralRGBData_RGBMessageType_MATRIX_TRIGGER_RIPPLE
#define _GeneralRGBData_RGBMessageType_ARRAYSIZE ((GeneralRGBData_RGBMessageType)(GeneralRGBData_RGBMessageType_MATRIX_TRIGGER_RIPPLE+1))


/* Initializer values for message structs */
#define GeneralRGBData_init_default              {0, _GeneralRGBData_RGBMessageType_MIN, 0}
#define GeneralRGBData_init_zero                 {0, _GeneralRGBData_RGBMessageType_MIN, 0}

/* Field tags (for use in manual encoding/decoding) */
#define GeneralRGBData_message_size_tag          1
#define GeneralRGBData_message_type_tag          2
#define GeneralRGBData_more_data_tag             3

/* Struct field encoding specification for nanopb */
#define GeneralRGBData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   message_size,      1) \
X(a, STATIC,   SINGULAR, UENUM,    message_type,      2) \
X(a, STATIC,   SINGULAR, BOOL,     more_data,         3)
#define GeneralRGBData_CALLBACK NULL
#define GeneralRGBData_DEFAULT NULL

extern const pb_msgdesc_t GeneralRGBData_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define GeneralRGBData_fields &GeneralRGBData_msg

/* Maximum encoded size of messages (where known) */
#define GeneralRGBData_size                      10

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

#define FMT_0(FMT) format [FMT]
#define FMT_1(FMT,V1) format [FMT,V1]
#define FMT_2(FMT,V1,V2) format [FMT,V1,V2]
#define FMT_3(FMT,V1,V2,V3) format [FMT,V1,V2,V3]
#define FMT_4(FMT,V1,V2,V3,V4) format [FMT,V1,V2,V3,V4]
#define FMT_5(FMT,V1,V2,V3,V4,V5) format [FMT,V1,V2,V3,V4,V5]
#define FMT_6(FMT,V1,V2,V3,V4,V5,V6) format [FMT,V1,V2,V3,V4,V5,V6]
#define FMT_7(FMT,V1,V2,V3,V4,V5,V6,V7) format [FMT,V1,V2,V3,V4,V5,V6,V7]
#define FMT_8(FMT,V1,V2,V3,V4,V5,V6,V7,V8) format [FMT,V1,V2,V3,V4,V5,V6,V7,V8]
#define FMT_9(FMT,V1,V2,V3,V4,V5,V6,V7,V8,V9) format [FMT,V1,V2,V3,V4,V5,V6,V7,V8,V9]

#define DUMP_1(V1) format ["%1='%2'",#V1,V1]
#define DUMP_2(V1,V2) format ["%1='%2'; %3='%4'",#V1,V1,#V2,V2]
#define DUMP_3(V1,V2,V3) format ["%1='%2'; %3='%4'; %5='%6'",#V1,V1,#V2,V2,#V3,V3]
#define DUMP_4(V1,V2,V3,V4) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'",#V1,V1,#V2,V2,#V3,V3,#V4,V4]
#define DUMP_5(V1,V2,V3,V4,V5) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'; %9='%10'",#V1,V1,#V2,V2,#V3,V3,#V4,V4,#V5,V5]
#define DUMP_6(V1,V2,V3,V4,V5,V6) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'; %9='%10'; %11='%12'",#V1,V1,#V2,V2,#V3,V3,#V4,V4,#V5,V5,#V6,V6]
#define DUMP_7(V1,V2,V3,V4,V5,V6,V7) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'; %9='%10'; %11='%12'; %13='%14'",#V1,V1,#V2,V2,#V3,V3,#V4,V4,#V5,V5,#V6,V6,#V7,V7]
#define DUMP_8(V1,V2,V3,V4,V5,V6,V7,V8) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'; %9='%10'; %11='%12'; %13='%14'; %15='%16'",#V1,V1,#V2,V2,#V3,V3,#V4,V4,#V5,V5,#V6,V6,#V7,V7,#V8,V8]
#define DUMP_9(V1,V2,V3,V4,V5,V6,V7,V8,V9) format ["%1='%2'; %3='%4'; %5='%6'; %7='%8'; %9='%10'; %11='%12'; %13='%14'; %15='%16'; %17='%18'",#V1,V1,#V2,V2,#V3,V3,#V4,V4,#V5,V5,#V6,V6,#V7,V7,#V8,V8,#V9,V9]

#define LB_LOG(CTX,STRLVL,LVL,MESSG) \
    call { \
        private "_message"; \
        _message = LOGGING_FORMAT(CTX,STRLVL,MESSG); \
        LB_RPT_LOGGER(_message); \
        LB_CHAT_LOGGER(_message); \
        CUSTOM_LOGGER(_message); \
    }
#ifndef COMMON_PROP_TYPES_HPP
#define COMMON_PROP_TYPES_HPP

enum PROPERTY {
    PROP_EVENTCONTEXT   = 0,
    PROP_HANDLETABLE    = 1,
    PROP_EVENTSTATE     = 2,
    PROP_TIMERS         = 3,
    PROP_STRINGSTATE    = 4,
    PROP_JASS           = 5,
    PROP_JVM            = 6,
    PROP_TEXTURES       = 7,
    PROP_MODELS         = 8,
    PROP_AGILE          = 9,
    PROP_TEMPEST        = 10,
    PROP_RAIN           = 11,
    PROP_IPSE           = 12,
    PROP_APPLICATION    = 13,
    PROP_NET            = 14,
    PROP_WORLD          = 15,
    PROP_BATTLENET      = 16,
    PROP_COLLISION      = 17,
    PROPERTIES,
};

typedef void* HPROPCONTEXT;

#endif

#ifndef AL_AL_H
#define AL_AL_H

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef AL_API
 #if defined(AL_LIBTYPE_STATIC)
  #define AL_API
 #elif defined(_WIN32)
  #define AL_API extern __declspec(dllimport)
 #else
  #define AL_API extern
 #endif
#endif

#if defined(_WIN32)
 #define AL_APIENTRY __cdecl
#else
 #define AL_APIENTRY
#endif


/** Deprecated macro. */
#define OPENAL
#define ALAPI                                    AL_API
#define ALAPIENTRY                               AL_APIENTRY
#define AL_INVALID                               (-1)
#define AL_ILLEGAL_ENUM                          AL_INVALID_ENUM
#define AL_ILLEGAL_COMMAND                       AL_INVALID_OPERATION

/** Supported AL version. */
#define AL_VERSION_1_0
#define AL_VERSION_1_1

/** 8-bit boolean */
typedef char ALboolean;

/** character */
typedef char ALchar;

/** signed 8-bit 2's complement integer */
typedef signed char ALbyte;

/** unsigned 8-bit integer */
typedef unsigned char ALubyte;

/** signed 16-bit 2's complement integer */
typedef short ALshort;

/** unsigned 16-bit integer */
typedef unsigned short ALushort;

/** signed 32-bit 2's complement integer */
typedef int ALint;

/** unsigned 32-bit integer */
typedef unsigned int ALuint;

/** non-negative 32-bit binary integer size */
typedef int ALsizei;

/** enumerated 32-bit value */
typedef int ALenum;

/** 32-bit IEEE754 floating-point */
typedef float ALfloat;

/** 64-bit IEEE754 floating-point */
typedef double ALdouble;

/** void type (for opaque pointers only) */
typedef void ALvoid;


/* Enumerant values begin at column 50. No tabs. */

/** "no distance model" or "no buffer" */
#define AL_NONE                                  0

/** Boolean False. */
#define AL_FALSE                                 0

/** Boolean True. */
#define AL_TRUE                                  1


/**
 * Relative source.
 * Type:    ALboolean
 * Range:   [AL_TRUE, AL_FALSE]
 * Default: AL_FALSE
 *
 * Specifies if the Source has relative coordinates.
 */
#define AL_SOURCE_RELATIVE                       0x202


/**
 * Inner cone angle, in degrees.
 * Type:    ALint, ALfloat
 * Range:   [0 - 360]
 * Default: 360
 *
 * The angle covered by the inner cone, where the source will not attenuate.
 */
#define AL_CONE_INNER_ANGLE                      0x1001

/**
 * Outer cone angle, in degrees.
 * Range:   [0 - 360]
 * Default: 360
 *
 * The angle covered by the outer cone, where the source will be fully
 * attenuated.
 */
#define AL_CONE_OUTER_ANGLE                      0x1002

/**
 * Source pitch.
 * Type:    ALfloat
 * Range:   [0.5 - 2.0]
 * Default: 1.0
 *
 * A multiplier for the frequency (sample rate) of the source's buffer.
 */
#define AL_PITCH                                 0x1003

/**
 * Source or listener position.
 * Type:    ALfloat[3], ALint[3]
 * Default: {0, 0, 0}
 *
 * The source or listener location in three dimensional space.
 *
 * OpenAL, like OpenGL, uses a right handed coordinate system, where in a
 * frontal default view X (thumb) points right, Y points up (index finger), and
 * Z points towards the viewer/camera (middle finger).
 *
 * To switch from a left handed coordinate system, flip the sign on the Z
 * coordinate.
 */
#define AL_POSITION                              0x1004

/**
 * Source direction.
 * Type:    ALfloat[3], ALint[3]
 * Default: {0, 0, 0}
 *
 * Specifies the current direction in local space.
 * A zero-length vector specifies an omni-directional source (cone is ignored).
 */
#define AL_DIRECTION                             0x1005

/**
 * Source or listener velocity.
 * Type:    ALfloat[3], ALint[3]
 * Default: {0, 0, 0}
 *
 * Specifies the current velocity in local space.
 */
#define AL_VELOCITY                              0x1006

/**
 * Source looping.
 * Type:    ALboolean
 * Range:   [AL_TRUE, AL_FALSE]
 * Default: AL_FALSE
 *
 * Specifies whether source is looping.
 */
#define AL_LOOPING                               0x1007

/**
 * Source buffer.
 * Type:  ALuint
 * Range: any valid Buffer.
 *
 * Specifies the buffer to provide sound samples.
 */
#define AL_BUFFER                                0x1009

/**
 * Source or listener gain.
 * Type:  ALfloat
 * Range: [0.0 - ]
 *
 * A value of 1.0 means unattenuated. Each division by 2 equals an attenuation
 * of about -6dB. Each multiplicaton by 2 equals an amplification of about
 * +6dB.
 *
 * A value of 0.0 is meaningless with respect to a logarithmic scale; it is
 * silent.
 */
#define AL_GAIN                                  0x100A

/**
 * Minimum source gain.
 * Type:  ALfloat
 * Range: [0.0 - 1.0]
 *
 * The minimum gain allowed for a source, after distance and cone attenation is
 * applied (if applicable).
 */
#define AL_MIN_GAIN                              0x100D

/**
 * Maximum source gain.
 * Type:  ALfloat
 * Range: [0.0 - 1.0]
 *
 * The maximum gain allowed for a source, after distance and cone attenation is
 * applied (if applicable).
 */
#define AL_MAX_GAIN                              0x100E

/**
 * Listener orientation.
 * Type: ALfloat[6]
 * Default: {0.0, 0.0, -1.0, 0.0, 1.0, 0.0}
 *
 * Effectively two three dimensional vectors. The first vector is the front (or
 * "at") and the second is the top (or "up").
 *
 * Both vectors are in local space.
 */
#define AL_ORIENTATION                           0x100F

/**
 * Source state (query only).
 * Type:  ALint
 * Range: [AL_INITIAL, AL_PLAYING, AL_PAUSED, AL_STOPPED]
 */
#define AL_SOURCE_STATE                          0x1010

/** Source state value. */
#define AL_INITIAL                               0x1011
#define AL_PLAYING                               0x1012
#define AL_PAUSED                                0x1013
#define AL_STOPPED                               0x1014

/**
 * Source Buffer Queue size (query only).
 * Type: ALint
 *
 * The number of buffers queued using alSourceQueueBuffers, minus the buffers
 * removed with alSourceUnqueueBuffers.
 */
#define AL_BUFFERS_QUEUED                        0x1015

/**
 * Source Buffer Queue processed count (query only).
 * Type: ALint
 *
 * The number of queued buffers that have been fully processed, and can be
 * removed with alSourceUnqueueBuffers.
 *
 * Looping sources will never fully process buffers because they will be set to
 * play again for when the source loops.
 */
#define AL_BUFFERS_PROCESSED                     0x1016

/**
 * Source reference distance.
 * Type:    ALfloat
 * Range:   [0.0 - ]
 * Default: 1.0
 *
 * The distance in units that no attenuation occurs.
 *
 * At 0.0, no distance attenuation ever occurs on non-linear attenuation models.
 */
#define AL_REFERENCE_DISTANCE                    0x1020

/**
 * Source rolloff factor.
 * Type:    ALfloat
 * Range:   [0.0 - ]
 * Default: 1.0
 *
 * Multiplier to exaggerate or diminish distance attenuation.
 *
 * At 0.0, no distance attenuation ever occurs.
 */
#define AL_ROLLOFF_FACTOR                        0x1021

/**
 * Outer cone gain.
 * Type:    ALfloat
 * Range:   [0.0 - 1.0]
 * Default: 0.0
 *
 * The gain attenuation applied when the listener is outside of the source's
 * outer cone.
 */
#define AL_CONE_OUTER_GAIN                       0x1022

/**
 * Source maximum distance.
 * Type:    ALfloat
 * Range:   [0.0 - ]
 * Default: +inf
 *
 * The distance above which the source is not attenuated any further with a
 * clamped distance model, or where attenuation reaches 0.0 gain for linear
 * distance models with a default rolloff factor.
 */
#define AL_MAX_DISTANCE                          0x1023

/** Source buffer position, in seconds */
#define AL_SEC_OFFSET                            0x1024
/** Source buffer position, in sample frames */
#define AL_SAMPLE_OFFSET                         0x1025
/** Source buffer position, in bytes */
#define AL_BYTE_OFFSET                           0x1026

/**
 * Source type (query only).
 * Type:  ALint
 * Range: [AL_STATIC, AL_STREAMING, AL_UNDETERMINED]
 *
 * A Source is Static if a Buffer has been attached using AL_BUFFER.
 *
 * A Source is Streaming if one or more Buffers have been attached using
 * alSourceQueueBuffers.
 *
 * A Source is Undetermined when it has the NULL buffer attached using
 * AL_BUFFER.
 */
#define AL_SOURCE_TYPE                           0x1027

/** Source type value. */
#define AL_STATIC                                0x1028
#define AL_STREAMING                             0x1029
#define AL_UNDETERMINED                          0x1030

/** Buffer format specifier. */
#define AL_FORMAT_MONO8                          0x1100
#define AL_FORMAT_MONO16                         0x1101
#define AL_FORMAT_STEREO8                        0x1102
#define AL_FORMAT_STEREO16                       0x1103

/** Buffer frequency (query only). */
#define AL_FREQUENCY                             0x2001
/** Buffer bits per sample (query only). */
#define AL_BITS                                  0x2002
/** Buffer channel count (query only). */
#define AL_CHANNELS                              0x2003
/** Buffer data size (query only). */
#define AL_SIZE                                  0x2004

/**
 * Buffer state.
 *
 * Not for public use.
 */
#define AL_UNUSED                                0x2010
#define AL_PENDING                               0x2011
#define AL_PROCESSED                             0x2012


/** No error. */
#define AL_NO_ERROR                              0

/** Invalid name paramater passed to AL call. */
#define AL_INVALID_NAME                          0xA001

/** Invalid enum parameter passed to AL call. */
#define AL_INVALID_ENUM                          0xA002

/** Invalid value parameter passed to AL call. */
#define AL_INVALID_VALUE                         0xA003

/** Illegal AL call. */
#define AL_INVALID_OPERATION                     0xA004

/** Not enough memory. */
#define AL_OUT_OF_MEMORY                         0xA005


/** Context string: Vendor ID. */
#define AL_VENDOR                                0xB001
/** Context string: Version. */
#define AL_VERSION                               0xB002
/** Context string: Renderer ID. */
#define AL_RENDERER                              0xB003
/** Context string: Space-separated extension list. */
#define AL_EXTENSIONS                            0xB004


/**
 * Doppler scale.
 * Type:    ALfloat
 * Range:   [0.0 - ]
 * Default: 1.0
 *
 * Scale for source and listener velocities.
 */
#define AL_DOPPLER_FACTOR                        0xC000

/**
 * Doppler velocity (deprecated).
 *
 * A multiplier applied to the Speed of Sound.
 */
#define AL_DOPPLER_VELOCITY                      0xC001

/**
 * Speed of Sound, in units per second.
 * Type:    ALfloat
 * Range:   [0.0001 - ]
 * Default: 343.3
 *
 * The speed at which sound waves are assumed to travel, when calculating the
 * doppler effect.
 */
#define AL_SPEED_OF_SOUND                        0xC003

/**
 * Distance attenuation model.
 * Type:    ALint
 * Range:   [AL_NONE, AL_INVERSE_DISTANCE, AL_INVERSE_DISTANCE_CLAMPED,
 *           AL_LINEAR_DISTANCE, AL_LINEAR_DISTANCE_CLAMPED,
 *           AL_EXPONENT_DISTANCE, AL_EXPONENT_DISTANCE_CLAMPED]
 * Default: AL_INVERSE_DISTANCE_CLAMPED
 *
 * The model by which sources attenuate with distance.
 *
 * None     - No distance attenuation.
 * Inverse  - Doubling the distance halves the source gain.
 * Linear   - Linear gain scaling between the reference and max distances.
 * Exponent - Exponential gain dropoff.
 *
 * Clamped variations work like the non-clamped counterparts, except the
 * distance calculated is clamped between the reference and max distances.
 */
#define AL_DISTANCE_MODEL                        0xD000

/** Distance model value. */
#define AL_INVERSE_DISTANCE                      0xD001
#define AL_INVERSE_DISTANCE_CLAMPED              0xD002
#define AL_LINEAR_DISTANCE                       0xD003
#define AL_LINEAR_DISTANCE_CLAMPED               0xD004
#define AL_EXPONENT_DISTANCE                     0xD005
#define AL_EXPONENT_DISTANCE_CLAMPED             0xD006

/** Pointer-to-function type, useful for dynamically getting AL entry points. */
typedef void          (AL_APIENTRY *LPALENABLE)(ALenum capability);
typedef void          (AL_APIENTRY *LPALDISABLE)(ALenum capability);
typedef ALboolean     (AL_APIENTRY *LPALISENABLED)(ALenum capability);
typedef const ALchar* (AL_APIENTRY *LPALGETSTRING)(ALenum param);
typedef void          (AL_APIENTRY *LPALGETBOOLEANV)(ALenum param, ALboolean *values);
typedef void          (AL_APIENTRY *LPALGETINTEGERV)(ALenum param, ALint *values);
typedef void          (AL_APIENTRY *LPALGETFLOATV)(ALenum param, ALfloat *values);
typedef void          (AL_APIENTRY *LPALGETDOUBLEV)(ALenum param, ALdouble *values);
typedef ALboolean     (AL_APIENTRY *LPALGETBOOLEAN)(ALenum param);
typedef ALint         (AL_APIENTRY *LPALGETINTEGER)(ALenum param);
typedef ALfloat       (AL_APIENTRY *LPALGETFLOAT)(ALenum param);
typedef ALdouble      (AL_APIENTRY *LPALGETDOUBLE)(ALenum param);
typedef ALenum        (AL_APIENTRY *LPALGETERROR)(void);
typedef ALboolean     (AL_APIENTRY *LPALISEXTENSIONPRESENT)(const ALchar *extname);
typedef void*         (AL_APIENTRY *LPALGETPROCADDRESS)(const ALchar *fname);
typedef ALenum        (AL_APIENTRY *LPALGETENUMVALUE)(const ALchar *ename);
typedef void          (AL_APIENTRY *LPALLISTENERF)(ALenum param, ALfloat value);
typedef void          (AL_APIENTRY *LPALLISTENER3F)(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void          (AL_APIENTRY *LPALLISTENERFV)(ALenum param, const ALfloat *values);
typedef void          (AL_APIENTRY *LPALLISTENERI)(ALenum param, ALint value);
typedef void          (AL_APIENTRY *LPALLISTENER3I)(ALenum param, ALint value1, ALint value2, ALint value3);
typedef void          (AL_APIENTRY *LPALLISTENERIV)(ALenum param, const ALint *values);
typedef void          (AL_APIENTRY *LPALGETLISTENERF)(ALenum param, ALfloat *value);
typedef void          (AL_APIENTRY *LPALGETLISTENER3F)(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void          (AL_APIENTRY *LPALGETLISTENERFV)(ALenum param, ALfloat *values);
typedef void          (AL_APIENTRY *LPALGETLISTENERI)(ALenum param, ALint *value);
typedef void          (AL_APIENTRY *LPALGETLISTENER3I)(ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void          (AL_APIENTRY *LPALGETLISTENERIV)(ALenum param, ALint *values);
typedef void          (AL_APIENTRY *LPALGENSOURCES)(ALsizei n, ALuint *sources);
typedef void          (AL_APIENTRY *LPALDELETESOURCES)(ALsizei n, const ALuint *sources);
typedef ALboolean     (AL_APIENTRY *LPALISSOURCE)(ALuint source);
typedef void          (AL_APIENTRY *LPALSOURCEF)(ALuint source, ALenum param, ALfloat value);
typedef void          (AL_APIENTRY *LPALSOURCE3F)(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void          (AL_APIENTRY *LPALSOURCEFV)(ALuint source, ALenum param, const ALfloat *values);
typedef void          (AL_APIENTRY *LPALSOURCEI)(ALuint source, ALenum param, ALint value);
typedef void          (AL_APIENTRY *LPALSOURCE3I)(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
typedef void          (AL_APIENTRY *LPALSOURCEIV)(ALuint source, ALenum param, const ALint *values);
typedef void          (AL_APIENTRY *LPALGETSOURCEF)(ALuint source, ALenum param, ALfloat *value);
typedef void          (AL_APIENTRY *LPALGETSOURCE3F)(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void          (AL_APIENTRY *LPALGETSOURCEFV)(ALuint source, ALenum param, ALfloat *values);
typedef void          (AL_APIENTRY *LPALGETSOURCEI)(ALuint source, ALenum param, ALint *value);
typedef void          (AL_APIENTRY *LPALGETSOURCE3I)(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void          (AL_APIENTRY *LPALGETSOURCEIV)(ALuint source, ALenum param, ALint *values);
typedef void          (AL_APIENTRY *LPALSOURCEPLAYV)(ALsizei n, const ALuint *sources);
typedef void          (AL_APIENTRY *LPALSOURCESTOPV)(ALsizei n, const ALuint *sources);
typedef void          (AL_APIENTRY *LPALSOURCEREWINDV)(ALsizei n, const ALuint *sources);
typedef void          (AL_APIENTRY *LPALSOURCEPAUSEV)(ALsizei n, const ALuint *sources);
typedef void          (AL_APIENTRY *LPALSOURCEPLAY)(ALuint source);
typedef void          (AL_APIENTRY *LPALSOURCESTOP)(ALuint source);
typedef void          (AL_APIENTRY *LPALSOURCEREWIND)(ALuint source);
typedef void          (AL_APIENTRY *LPALSOURCEPAUSE)(ALuint source);
typedef void          (AL_APIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint source, ALsizei nb, const ALuint *buffers);
typedef void          (AL_APIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint source, ALsizei nb, ALuint *buffers);
typedef void          (AL_APIENTRY *LPALGENBUFFERS)(ALsizei n, ALuint *buffers);
typedef void          (AL_APIENTRY *LPALDELETEBUFFERS)(ALsizei n, const ALuint *buffers);
typedef ALboolean     (AL_APIENTRY *LPALISBUFFER)(ALuint buffer);
typedef void          (AL_APIENTRY *LPALBUFFERDATA)(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
typedef void          (AL_APIENTRY *LPALBUFFERF)(ALuint buffer, ALenum param, ALfloat value);
typedef void          (AL_APIENTRY *LPALBUFFER3F)(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void          (AL_APIENTRY *LPALBUFFERFV)(ALuint buffer, ALenum param, const ALfloat *values);
typedef void          (AL_APIENTRY *LPALBUFFERI)(ALuint buffer, ALenum param, ALint value);
typedef void          (AL_APIENTRY *LPALBUFFER3I)(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
typedef void          (AL_APIENTRY *LPALBUFFERIV)(ALuint buffer, ALenum param, const ALint *values);
typedef void          (AL_APIENTRY *LPALGETBUFFERF)(ALuint buffer, ALenum param, ALfloat *value);
typedef void          (AL_APIENTRY *LPALGETBUFFER3F)(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void          (AL_APIENTRY *LPALGETBUFFERFV)(ALuint buffer, ALenum param, ALfloat *values);
typedef void          (AL_APIENTRY *LPALGETBUFFERI)(ALuint buffer, ALenum param, ALint *value);
typedef void          (AL_APIENTRY *LPALGETBUFFER3I)(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void          (AL_APIENTRY *LPALGETBUFFERIV)(ALuint buffer, ALenum param, ALint *values);
typedef void          (AL_APIENTRY *LPALDOPPLERFACTOR)(ALfloat value);
typedef void          (AL_APIENTRY *LPALDOPPLERVELOCITY)(ALfloat value);
typedef void          (AL_APIENTRY *LPALSPEEDOFSOUND)(ALfloat value);
typedef void          (AL_APIENTRY *LPALDISTANCEMODEL)(ALenum distanceModel);

extern LPALDOPPLERFACTOR alDopplerFactor;
extern LPALDOPPLERVELOCITY alDopplerVelocity;
extern LPALSPEEDOFSOUND alSpeedOfSound;
extern LPALDISTANCEMODEL alDistanceModel;
extern LPALENABLE alEnable;
extern LPALDISABLE alDisable;
extern LPALISENABLED alIsEnabled;
extern LPALGETSTRING alGetString;
extern LPALGETBOOLEAN alGetBooleanv;
extern LPALGETINTEGERV alGetIntegerv;
extern LPALGETFLOATV alGetFloatv;
extern LPALGETDOUBLEV alGetDoublev;
extern LPALGETBOOLEAN alGetBoolean;
extern LPALGETINTEGER alGetInteger;
extern LPALGETFLOAT alGetFloat;
extern LPALGETDOUBLE alGetDouble;
extern LPALGETERROR alGetError;
extern LPALISEXTENSIONPRESENT alIsExtensionPresent;
extern LPALGETPROCADDRESS alGetProcAddress;
extern LPALGETENUMVALUE alGetEnumValue;
extern LPALGETLISTENERF alListenerf;
extern LPALGETLISTENER3F alListener3f;
extern LPALGETLISTENERFV alListenerfv;
extern LPALGETLISTENERI alListeneri;
extern LPALGETLISTENER3I alListener3i;
extern LPALGETLISTENERIV alListeneriv;
extern LPALGETLISTENERF alGetListenerf;
extern LPALGETLISTENER3F alGetListener3f;
extern LPALGETLISTENERFV alGetListenerfv;
extern LPALGETLISTENERI alGetListeneri;
extern LPALGETLISTENER3I alGetListener3i;
extern LPALGETLISTENERIV alGetListeneriv;
extern LPALGENSOURCES alGenSources;
extern LPALDELETESOURCES alDeleteSources;
extern LPALISSOURCE alIsSource;
extern LPALSOURCEF alSourcef;
extern LPALSOURCE3F alSource3f;
extern LPALSOURCEFV alSourcefv;
extern LPALSOURCEI alSourcei;
extern LPALSOURCE3I alSource3i;
extern LPALSOURCEIV alSourceiv;
extern LPALGETSOURCEF alGetSourcef;
extern LPALGETSOURCE3F alGetSource3f;
extern LPALGETSOURCEFV alGetSourcefv;
extern LPALGETSOURCEI alGetSourcei;
extern LPALGETSOURCE3I alGetSource3i;
extern LPALGETSOURCEIV alGetSourceiv;
extern LPALSOURCEPLAYV alSourcePlayv;
extern LPALSOURCESTOPV alSourceStopv;
extern LPALSOURCEREWINDV alSourceRewindv;
extern LPALSOURCEPAUSEV alSourcePausev;
extern LPALSOURCEPLAY alSourcePlay;
extern LPALSOURCESTOP alSourceStop;
extern LPALSOURCEREWIND alSourceRewind;
extern LPALSOURCEPAUSE alSourcePause;
extern LPALSOURCEQUEUEBUFFERS alSourceQueueBuffers;
extern LPALSOURCEUNQUEUEBUFFERS alSourceUnqueueBuffers;
extern LPALGENBUFFERS alGenBuffers;
extern LPALDELETEBUFFERS alDeleteBuffers;
extern LPALISBUFFER alIsBuffer;
extern LPALBUFFERDATA alBufferData;
extern LPALBUFFERF alBufferf;
extern LPALBUFFER3F alBuffer3f;
extern LPALBUFFERFV alBufferfv;
extern LPALBUFFERI alBufferi;
extern LPALBUFFER3I alBuffer3i;
extern LPALBUFFERIV alBufferiv;
extern LPALGETBUFFERF alGetBufferf;
extern LPALGETBUFFER3F alGetBuffer3f;
extern LPALGETBUFFERFV alGetBufferfv;
extern LPALGETBUFFERI alGetBufferi;
extern LPALGETBUFFER3I alGetBuffer3i;
extern LPALGETBUFFERIV alGetBufferiv;

#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif /* AL_AL_H */
#ifndef CONFIG_H
#define CONFIG_H

/* Define to enable ALSA driver */
#define ALSA_SUPPORT 1

/* Define to activate sound output to files */
#define AUFILE_SUPPORT 1

/* whether or not we are supporting CoreAudio */
/* #undef COREAUDIO_SUPPORT */

/* whether or not we are supporting CoreMIDI */
/* #undef COREMIDI_SUPPORT */

/* whether or not we are supporting DART */
/* #undef DART_SUPPORT */

/* Define if building for Mac OS X Darwin */
/* #undef DARWIN */

/* Define if D-Bus support is enabled */
//#define DBUS_SUPPORT  1

/* Soundfont to load automatically in some use cases */
#define DEFAULT_SOUNDFONT "/usr/local/share/soundfonts/default.sf2"

/* Define to enable FPE checks */
/* #undef FPE_CHECK */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* whether or not we are supporting lash */
/* #undef HAVE_LASH */

/* Define to 1 if you have the `MidiShare' library (-lMidiShare). */
/* #undef HAVE_LIBMIDISHARE */

/* Define to 1 if you have the `pthread' library (-lpthread). */
#define HAVE_LIBPTHREAD TRUE

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <machine/soundcard.h> header file. */
/* #undef HAVE_MACHINE_SOUNDCARD_H */

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <MidiShare.h> header file. */
/* #undef HAVE_MIDISHARE_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/soundcard.h> header file. */
#define HAVE_SYS_SOUNDCARD_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the inet_ntop() function. */
#define HAVE_INETNTOP 1

/* Define to enable JACK driver */
#define JACK_SUPPORT 1

/* Include the LADSPA Fx unit */
/* #undef LADSPA */

/* Define to enable IPV6 support */
#define IPV6_SUPPORT 1

/* Define to enable network support */
#define NETWORK_SUPPORT 1

/* libsndfile has ogg vorbis support */
#define LIBSNDFILE_HASVORBIS 1

/* Define to enable libsndfile support */
#define LIBSNDFILE_SUPPORT 1

/* Define to enable MidiShare driver */
/* #undef MIDISHARE_SUPPORT */

/* Define if using the MinGW32 environment */
/* #undef MINGW32 */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define to enable OSS driver */
#define OSS_SUPPORT TRUE

/* Name of package */
#define PACKAGE "fluidsynth"

/* Define to the address where bug reports for this package should be sent. */
/* #undef PACKAGE_BUGREPORT */

/* Define to the full name of this package. */
/* #undef PACKAGE_NAME */

/* Define to the full name and version of this package. */
/* #undef PACKAGE_STRING */

/* Define to the one symbol short name of this package. */
/* #undef PACKAGE_TARNAME */

/* Define to the version of this package. */
/* #undef PACKAGE_VERSION */

/* Define to enable PortAudio driver */
/* #undef PORTAUDIO_SUPPORT */

/* Define to enable PulseAudio driver */
#define PULSE_SUPPORT 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Soundfont to load for unit testing */
/* #undef TEST_SOUNDFONT */

/* SF3 Soundfont to load for unit testing */
/* #undef TEST_SOUNDFONT_SF3 */

/* Define to enable SIGFPE assertions */
/* #undef TRAP_ON_FPE */

/* Define to do all DSP in single floating point precision */
/* #undef WITH_FLOAT */

/* Define to profile the DSP code */
/* #undef WITH_PROFILING */

/* Define to use the readline library for line editing */
#define WITH_READLINE 1

/* Define if the compiler supports VLA */
#define SUPPORTS_VLA 1

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

#endif /* CONFIG_H */

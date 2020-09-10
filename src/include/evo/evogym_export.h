
#ifndef EVOGYM_EXPORT_H
#define EVOGYM_EXPORT_H

#ifdef EVOGYM_STATIC_DEFINE
#  define EVOGYM_EXPORT
#  define EVOGYM_NO_EXPORT
#else
#  ifndef EVOGYM_EXPORT
#    ifdef evo_gym_EXPORTS
        /* We are building this library */
#      define EVOGYM_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define EVOGYM_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef EVOGYM_NO_EXPORT
#    define EVOGYM_NO_EXPORT 
#  endif
#endif

#ifndef EVOGYM_DEPRECATED
#  define EVOGYM_DEPRECATED __declspec(deprecated)
#endif

#ifndef EVOGYM_DEPRECATED_EXPORT
#  define EVOGYM_DEPRECATED_EXPORT EVOGYM_EXPORT EVOGYM_DEPRECATED
#endif

#ifndef EVOGYM_DEPRECATED_NO_EXPORT
#  define EVOGYM_DEPRECATED_NO_EXPORT EVOGYM_NO_EXPORT EVOGYM_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef EVOGYM_NO_DEPRECATED
#    define EVOGYM_NO_DEPRECATED
#  endif
#endif

#endif /* EVOGYM_EXPORT_H */

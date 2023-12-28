#pragma once

#define CYDL_MAJOR_VERSION 0
#define CYDL_MINOR_VERSION 1
#define CYDL_PATCH_VERSION 0


#define CYDL_VERSION_AT_LEAST(x,y,z) (CYDL_MAJOR_VERSION>x || (CYDL_MAJOR_VERSION>=x && \
                                      (CYDL_MINOR_VERSION>y || (CYDL_MINOR_VERSION>=y && \
                                                                 CYDL_PATCH_VERSION>=z))))

// C++ feature support
#if __cplusplus >= 201103L
#define CYDL_NOEXCEPT noexcept
#define CYDL_CONSTEXPR constexpr
#define CYDL_NULLPTR nullptr
#define CYDL_OVERRIDE override
#define CYDL_FINAL final
#else
#define CYDL_NOEXCEPT
#define CYDL_CONSTEXPR
#define CYDL_NULLPTR 0
#define CYDL_OVERRIDE
#define CYDL_FINAL
#endif

// Compiler detection
#ifdef __GNUC__
#define CYDL_COMP_GNUC (__GNUC__*10 + __GNUC_MINOR__)
#else
#define CYDL_COMP_GNUC 0
#endif

#ifdef __clang__
#define CYDL_COMP_CLANG (__clang_major__*100 + __clang_minor__)
#else
#define CYDL_COMP_CLANG 0
#endif

#ifdef __llvm__
#define CYDL_COMP_LLVM 1
#else
#define CYDL_COMP_LLVM 0
#endif

#ifdef __INTEL_COMPILER
#define CYDL_COMP_ICC __INTEL_COMPILER
#else
#define CYDL_COMP_ICC 0
#endif

#ifdef __MINGW32__
#define CYDL_COMP_MINGW 1
#else
#define CYDL_COMP_MINGW 0
#endif

#ifdef __SUNPRO_CC
#define CYDL_COMP_SUNCC 1
#else
#define CYDL_COMP_SUNCC 0
#endif

#ifdef _MSC_VER
#define CYDL_COMP_MSVC _MSC_VER
#else
#define CYDL_COMP_MSVC 0
#endif

#ifdef __IBMCPP__ || defined(__xlc__)
#define CYDL_COMP_IBM 1
#else
#define CYDL_COMP_IBM 0
#endif

#ifdef __PGI
#define CYDL_COMP_PGI 1
#else
#define CYDL_COMP_PGI 0
#endif

#ifdef __CC_ARM || defined(__ARMCC_VERSION)
#define CYDL_COMP_ARM 1
#else
#define CYDL_COMP_ARM 0
#endif

#ifdef __EMSCRIPTEN__
#define CYDL_COMP_EMSCRIPTEN 1
#else
#define CYDL_COMP_EMSCRIPTEN 0
#endif

// Strict MSVC check
#if CYDL_COMP_MSVC && !(CYDL_COMP_ICC || CYDL_COMP_LLVM || CYDL_COMP_CLANG)
#define CYDL_COMP_MSVC_STRICT _MSC_VER
#else
#define CYDL_COMP_MSVC_STRICT 0
#endif
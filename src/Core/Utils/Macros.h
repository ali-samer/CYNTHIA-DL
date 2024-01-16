#ifdef CYDL_DEFINE_GLOBAL_MACROS


#ifndef CYDL_VERSIONING_MACROS
#   define CYDL_MAJOR_VERSION 0
#   define CYDL_MINOR_VERSION 1
#   define CYDL_PATCH_VERSION 0
#endif


#define CYDL_VERSION_AT_LEAST( x , y , z ) (CYDL_MAJOR_VERSION>x || (CYDL_MAJOR_VERSION>=x && \
                                      (CYDL_MINOR_VERSION>y || (CYDL_MINOR_VERSION>=y && \
                                                                 CYDL_PATCH_VERSION>=z))))

// Compiler detection
#ifdef __GNUC__
#   define CYDL_COMP_GNUC (__GNUC__*10 + __GNUC_MINOR__)
#else
#   define CYDL_COMP_GNUC 0
#endif

#ifdef __clang__
#   define CYDL_COMP_CLANG (__clang_major__*100 + __clang_minor__)
#else
#   define CYDL_COMP_CLANG 0
#endif

#ifdef __llvm__
#   define CYDL_COMP_LLVM 1
#else
#   define CYDL_COMP_LLVM 0
#endif

#ifdef __INTEL_COMPILER
#   define CYDL_COMP_ICC __INTEL_COMPILER
#else
#   define CYDL_COMP_ICC 0
#endif

#ifdef __MINGW32__
#   define CYDL_COMP_MINGW 1
#else
#   define CYDL_COMP_MINGW 0
#endif

#ifdef __SUNPRO_CC
#   define CYDL_COMP_SUNCC 1
#else
#   define CYDL_COMP_SUNCC 0
#endif

#ifdef _MSC_VER
#   define CYDL_COMP_MSVC _MSC_VER
#else
#   define CYDL_COMP_MSVC 0
#endif

#if defined(__IBMCPP__) || defined(__xlc__)
#   define CYDL_COMP_IBM 1
#else
#   define CYDL_COMP_IBM 0
#endif

#ifdef __PGI
#   define CYDL_COMP_PGI 1
#else
#   define CYDL_COMP_PGI 0
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#   define CYDL_COMP_ARM 1
#else
#   define CYDL_COMP_ARM 0
#endif

#ifdef __EMSCRIPTEN__
#   define CYDL_COMP_EMSCRIPTEN 1
#else
#   define CYDL_COMP_EMSCRIPTEN 0
#endif

// Strict MSVC check
#if CYDL_COMP_MSVC && !( CYDL_COMP_ICC || CYDL_COMP_LLVM || CYDL_COMP_CLANG )
#   define CYDL_COMP_MSVC_STRICT _MSC_VER
#else
#   define CYDL_COMP_MSVC_STRICT 0
#endif


#ifdef __x86_64__
#   define CYDL_ARCH_X86_64 1
#elif defined(__i386__)
#   define CYDL_ARCH_X86_32 1
#elif defined(__aarch64__)
#   define CYDL_ARCH_ARM64 1
#elif defined(__arm__)
#   define CYDL_ARCH_ARM32 1
#elif defined(_M_X64) || defined(_M_AMD64)
#   define CYDL_ARCH_MS_X64 1
#elif defined(_M_IX86)
#   define CYDL_ARCH_MS_X86 1
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__)
#   define CYDL_ARCH_PPC64 1
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
#   define CYDL_ARCH_PPC32 1
#elif defined(__sparc64__)
#   define CYDL_ARCH_SPARC64 1
#elif defined(__sparc__)
#   define CYDL_ARCH_SPARC32 1
#elif defined(__mips64)
#   define CYDL_ARCH_MIPS64 1
#elif defined(__mips__)
#   define CYDL_ARCH_MIPS32 1
#else
#   define CYDL_ARCH_UNKNOWN 1
#endif


// C++ feature support
#if __cplusplus >= 201103L
#   define CYDL_NOEXCEPT noexcept
#   define CYDL_CONSTEXPR constexpr
#   define CYDL_NULLPTR nullptr
#   define CYDL_OVERRIDE override
#   define CYDL_FINAL final
#   define CYDL_CPP11_SUPPORTED 1
#else
#   define CYDL_NOEXCEPT throw()
#   define CYDL_CONSTEXPR
#   define CYDL_NULLPTR 0
#   define CYDL_OVERRIDE
#   define CYDL_FINAL
#endif

// valid macros since C++98

#define CYDL_STRONG_INLINE inline
#if defined(CYDL_COMP_GNUC) || defined(CYDL_COMP_CLANG) || defined(CYDL_COMP_ICC)
#   define CYDL_FORCE_INLINE __attribute__((always_inline)) inline // this will force the compiler to `inline`
#elif defined(CYDL_COMP_MSVC)
#   define CYDL_FORCE_INLINE __forceinline
#else
#   define CYDL_FORCE_INLINE CYDL_STRONG_INLINE
#endif
#define CYDL_STRONG_EXPLICIT explicit

#if __cplusplus >= 201703L
#   define CYDL_CPP17_SUPPORTED 1
#else
#   define CYDL_CPP17_SUPPORTED 0
#endif

#if __cplusplus >= 202002L
#   define CYDL_CPP20_SUPPORTED 1
#else
#   define CYDL_CPP20_SUPPORTED 0
#endif

#if CYDL_CPP20_SUPPORTED
#   define CYDL_MODULE_SUPPORT 1
#else
#d  efine CYDL_MODULE_SUPPORT 0
#endif

#if CYDL_MODULE_SUPPORT
#   define CYDL_DEFINE_MODULE module;
#   define CYDL_DECLARE_MODULE( module_name ) export module module_name;
#   define CYDL_IMPORT_MODULE( module_name ) import module_name
#else
#   define CYDL_IMPORT_MODULE(module_name)
#endif

#if CYDL_MODULE_EXPORT_SUPPORT
#   define CYDL_EXPORT_MODULE(module_name) export module module_name;
#else
#   define CYDL_EXPORT_MODULE( module_name )
#endif

#ifdef CYDL_CPP17_SUPPORTED
#   define CYDL_DONT_IGNORE_AFLAG [[nodiscard]]
#   define CYDL_UNUSED_AFLAG [[maybe_unused]]
#else
#   define CYDL_DONT_IGNORE_AFLAG
#   define CYDL_UNUSED_AFLAG
#endif

#include <cstdint>
#include <cstdio>

/// \Architecture macro identifiers defined above

// Define CYDL_MAX_SIZE based on the identified architecture
#if defined(CYDL_ARCH_X86_64) || defined(CYDL_ARCH_ARM64) || defined(CYDL_ARCH_MS_X64) || \
    defined(CYDL_ARCH_PPC64) || defined(CYDL_ARCH_SPARC64) || defined(CYDL_ARCH_MIPS64)
#   define CYDL_MAX_SIZE SIZE_MAX
#else
#   define CYDL_MAX_SIZE UINT32_MAX
#endif
typedef std::size_t CYDL_SIZET;

#ifdef CYDL_ARCH_X86_64
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#elif defined(CYDL_ARCH_X86_32) || defined(CYDL_ARCH_MS_X64) || defined(CYDL_ARCH_MS_X86)
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#elif defined(CYDL_ARCH_ARM64) || defined(CYDL_ARCH_AARCH64)
typedef long long CYDL_INT64;
typedef int       CYDL_INT32;
typedef short     CYDL_INT16;
typedef char      CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float  CYDL_FLOAT32;

#elif defined(CYDL_ARCH_ARM32) || defined(CYDL_ARCH_ARM)
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#elif defined(CYDL_ARCH_PPC64) || defined(CYDL_ARCH_PPC32)
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#elif defined(CYDL_ARCH_SPARC64) || defined(CYDL_ARCH_SPARC32)
typedef long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#elif defined(CYDL_ARCH_MIPS64) || defined(CYDL_ARCH_MIPS32)
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#else // Unknown architecture
typedef long long CYDL_INT64;
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

#endif

#define CYDL_RETURN_ON_FAIL( expr ) do { if (!(expr)) return 0; } while (0)
#define CYDL_CONCAT_INTERNAL(X, Y) X##Y
#define CYDL_CONCAT_3_INTERNAL(X, Y, Z) X##Y##Z

#define CYDL_CONCAT(X, Y) CYDL_CONCAT_INTERNAL(X, Y)
#define CYDL_CONCAT_3(X, Y, Z) CYDL_CONCAT_3_INTERNAL(X, Y, Z)

#define CYDL_CONCAT_WITH_DELIMITER( X , _CYDL_DELIMITER_PARAM , Z ) CYDL_CONCAT_3(X, _CYDL_DELIMITER_PARAM, Z)
#define CYDL_DEFAULT_DELIMITER _
#ifndef CYDL_VERSIONING
#   define CYDL_VERSIONING 1
#   define CYDL_VERSIONING_MAJOR_MINOR CYDL_CONCAT_WITH_DELIMITER(CYDL_MAJOR_VERSION, CYDL_DEFAULT_DELIMITER, CYDL_MINOR_VERSION)
#   ifndef CYDL_VERSIONING_FORMAT
#       define CYDL_VERSIONING_FORMAT CYDL_VERSIONING_MAJOR_MINOR
#   endif
#   ifndef CYDL_VERSIONING_DETAIL
#       define CYDL_VERSIONING_DETAIL CYDL_VERSIONING_FORMAT
#   endif
#endif

#ifndef CYDL_VERSIONING_NAMESPACE
#   define CYDL_VERSIONING_NAMESPACE_INTERNAL( _VERSIONING_PARAM_) CYDL_CONCAT(cydl_version_, _VERSIONING_PARAM_)
#   define CYDL_VERSIONING_NAMESPACE CYDL_VERSIONING_NAMESPACE_INTERNAL(CYDL_VERSIONING_DETAIL)
#endif

// Inline namespace for versioning control
#define CYDL_BEGIN_LIB_NAMESPACE namespace cydl { inline namespace CYDL_VERSIONING_NAMESPACE {
#define CYDL_BEGIN_LIB_DETAILS_NAMESPACE namespace details { inline namespace CYDL_VERSIONING_NAMESPACE {
#define CYDL_BEGIN_LIB_POLICIES_NAMESPACE namespace policies { inline namespace CYDL_VERSIONING_NAMESPACE {
#define CYDL_BEGIN_LIB_UTILS_NAMESPACE namespace utils { inline namespace CYDL_VERSIONING_NAMESPACE {
#define CYDL_END_LIB_NAMESPACE }}
#define CYDL_END_LIB_DETAILS_NAMESPACE }}
#define CYDL_END_LIB_POLICIES_NAMESPACE }}
#define CYDL_END_LIB_UTILS_NAMESPACE }}

#define CYDL_VDETAILS cydl::details::CYDL_VERSIONING_NAMESPACE
#define CYDL_VPOLICIES cydl::policies::CYDL_VERSIONING_NAMESPACE
#define CYDL_VUTILS cydl::utils::CYDL_VERSIONING_NAMESPACE

// TODO: these allocation sizes/spaces are temporary. Make sure to find appropriate default
//  allocation space that would be ideal across other systems
#define CYDL_DEFAULT_ALLOCATION_SPACE 500 /* Must change */
#define CYDL_DEFAULT_EXPANSION_SPACE 100 /* Must change */

/// \MEMORY_INITIALIZATION \a cydl memory pool initial size could be set by user before compilation
#ifndef CYDL_MEMORY_POOL_SIZE
	#define CYDL_MEMORY_POOL_SIZE CYDL_DEFAULT_ALLOCATION_SPACE
#endif

/// \MEMORY_EXPANSION \a cydl memory pool expansion size could be set by user upon compilation
#ifndef CYDL_MEMORY_POOL_EXPANSION_SIZE
	#define CYDL_MEMORY_POOL_EXPANSION_SIZE CYDL_DEFAULT_EXPANSION_SPACE
#endif

/// \Attributes
#ifdef _MSC_VER
#   define CYDL_DEFAULT_AFLAG __declspec(dllexport)
#   define CYDL_HIDDEN_AFLAG // MSVC does not support hidden visibility
#   define CYDL_PROTECTED_AFLAG // No direct equivalent in MSVC
#   define CYDL_INTERNAL_AFLAG // No direct equivalent in MSVC
#elif defined(__GNUC__)
#   define CYDL_DEFAULT_AFLAG __attribute__((__visibility__("default")))
#   define CYDL_HIDDEN_AFLAG __attribute__((__visibility__("hidden")))
#   define CYDL_PROTECTED_AFLAG __attribute__((__visibility__("protected")))
#   define CYDL_INTERNAL_AFLAG __attribute__((__visibility__("internal")))
#   define CYDL_PACKED_AFLAG __attribute__((packed))
#else
#   define CYDL_DEFAULT_AFLAG
#   define CYDL_HIDDEN_AFLAG
#   define CYDL_PROTECTED_AFLAG
#   define CYDL_INTERNAL_AFLAG
#endif

#ifndef NDEBUG

	#define CYDL_DEBUG_MSG( msg ) std::cerr << "Debug: " << __FILE__ << ":" << __LINE__ << ":" << __func__ << ":" << msg << std::endl;
#endif

#if defined(CYDL_COMP_CLANG) && defined(CYDL_COMP_GNUC)
	#define DO_PRAGMA( x ) _Pragma(#x)
	#define CYDL_WARNING( x ) DO_PRAGMA(GCC warning x)
#elif defined(_MSC_VER)
#define CYDL_WARNING(x) __pragma(message(x))
#else
	#define CYDL_WARNING(x) /* Other compilers */
#endif

/// \Dependencies
#include "Config.h"

#ifdef CYDL_USE_EIGEN
#   define CYDL_EIGEN_SUPPORT 1
#endif


#endif // End CYDL_DEFINE_MACROS
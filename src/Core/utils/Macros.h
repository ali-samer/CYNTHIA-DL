#ifdef CYDL_DEFINE_GLOBAL_MACROS


#ifndef CYDL_VERSIONING_MACROS
#   define CYDL_MAJOR_VERSION 0
#   define CYDL_MINOR_VERSION 1
#   define CYDL_PATCH_VERSION 0
#endif


#define CYDL_VERSION_AT_LEAST( x , y , z ) (CYDL_MAJOR_VERSION>x || (CYDL_MAJOR_VERSION>=x && \
                                      (CYDL_MINOR_VERSION>y || (CYDL_MINOR_VERSION>=y && \
                                                                 CYDL_PATCH_VERSION>=z))))

// C++ feature support
#if __cplusplus >= 201103L
#   define CYDL_NOEXCEPT noexcept
#   define CYDL_CONSTEXPR constexpr
#   define CYDL_NULLPTR nullptr
#   define CYDL_OVERRIDE override
#   define CYDL_FINAL final
#else
#   define CYDL_NOEXCEPT throw()
#   define CYDL_CONSTEXPR
#   define CYDL_NULLPTR 0
#   define CYDL_OVERRIDE
#   define CYDL_FINAL
#endif

// valid macros since C++98
#define CYDL_STRONG_INLINE inline
#define CYDL_FORCE_INLINE __attribute__((always_inline)) inline
#define CYDL_STRONG_EXPLICIT explicit

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


#include <cstdint>
#include <cstdio>

/// \Architecture macro identifiers defined above

// Define CYDL_MAX_SIZE based on the identified architecture
#if defined(CYDL_ARCH_X86_64) || defined(CYDL_ARCH_ARM64) || defined(CYDL_ARCH_MS_X64) || \
    defined(CYDL_ARCH_PPC64) || defined(CYDL_ARCH_SPARC64) || defined(CYDL_ARCH_MIPS64)
#define CYDL_MAX_SIZE SIZE_MAX
#else
#define CYDL_MAX_SIZE UINT32_MAX
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
typedef int CYDL_INT32;
typedef short CYDL_INT16;
typedef char CYDL_INT8;

typedef double CYDL_FLOAT64;
typedef float CYDL_FLOAT32;

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
#define CYDL_CONCAT( X , Y ) X##Y
#define CYDL_CONCAT_3( X , Y , Z ) X##Y##Z
#define CYDL_CONCAT_WITH_DELIMITER( X , _CYDL_DELIMITER , Z ) CYDL_CONCAT_3(X, _CYDL_DELIMITER, Z)

#ifndef CYDL_VERSIONING
#   define CYDL_VERSIONING 1
#   define CYDL_VERSIONING_MAJOR_MINOR CYDL_CONCAT_WITH_DELIMITER(CYDL_MAJOR_VERSION, _, CYDL_MINOR_VERSION)
#   define CYDL_VERSIONING_FORMAT CYDL_VERSIONING_MAJOR_MINOR
#   define CYDL_VERSIONING_DETAIL CYDL_VERSIONING_FORMAT
#endif

#ifndef CYDL_VERSIONING_NAMESPACE
#   define CYDL_VERSIONING_NAMESPACE CYDL_CONCAT(cydl_version_, CYDL_VERSIONING_DETAIL)
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

#define CYDL_DEFAULT_ALLOCATION_SPACE 500
#define CYDL_DEFAULT_EXPANSION_SPACE 100

/// \MEMORY_INITIALIZATION \a cydl memory pool initial size could be set by user upon compilation
#ifndef CYDL_MEMORY_POOL_SIZE
	#define CYDL_MEMORY_POOL_SIZE CYDL_DEFAULT_ALLOCATION_SPACE
#endif

/// \MEMORY_EXPANSION \a cydl memory pool expansion size could be set by user upon compilation
#ifndef CYDL_MEMORY_POOL_EXPANSION_SIZE
	#define CYDL_MEMORY_POOL_EXPANSION_SIZE CYDL_DEFAULT_EXPANSION_SPACE
#endif

#define CYDL_TEMPLATE_DEFAULT_CFLAG __attribute__((__visibility__("default")))
#endif // End CYDL_DEFINE_MACROS
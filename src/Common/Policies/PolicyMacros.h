#include "Common/TypeTraits.h"


#define CYDL_ENUM_TYPE_POLICY_OBJECT(PolicyName, Major, Minor, Value) \
namespace cydl::detials { \
    struct PolicyName : virtual public Major { \
        using MinorClass = Major::Minor##TypeCate; \
        using Minor = Major::Minor##TypeCate::Value; \
    }; \
}

/// \Purpose: used to define type policy object
#define CYDL_TYPE_POLICY_OBJECT(PolicyName, Major, Minor, Value) \
namespace cydl::detials { \
    struct PolicyName : virtual public Major { \
        using MinorClass = Major::Minor##TypeCate; \
        using Minor = Value; \
    }; \
}

/// \Purpose: used to define value policy object
#define CYDL_VALUE_POLICY_OBJECT(PolicyName, Major, Minor, Value) \
namespace cydl::detials { \
    struct PolicyName : virtual public Major { \
        using MinorClass = Major::Minor##ValueCate; \
    private: \
        using type1 = decltype(Major::Minor); \
        using type2 = RemConstRef<type1>; \
    public: \
        static constexpr type2 Minor = static_cast<type2>(Value); \
    }; \
}

/// \Purpose: used to define type policy object templates
#define CYDL_TYPE_POLICY_TEMPLATE(PolicyName, Major, Minor) \
namespace cydl::detials { \
    template <typename T> \
    struct PolicyName : virtual public Major { \
        using MinorClass = Major::Minor##TypeCate; \
        using Minor = T; \
    }; \
}

/// \Purpose: used to define value policy object templates
#define CYDL_VALUE_POLICY_TEMPLATE(PolicyName, Major, Minor) \
namespace cydl::detials { \
    template <cydl::utils::RemConstRef<decltype(Major::Minor)> T> \
    struct PolicyName : virtual public Major { \
        using MinorClass = Major::Minor##ValueCate; \
    private: \
        using type1 = decltype(Major::Minor); \
        using type2 = cydl::utils::RemoveConstRef_t<type1>; \
    public: \
        static constexpr type2 Minor = T; \
    }; \
}

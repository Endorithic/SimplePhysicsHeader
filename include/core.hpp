#ifndef SILO_CORE
#define SILO_CORE

#include <array>
#include <type_traits>

namespace SI
{

using DimArray = std::array<int, 7>;

template <typename Ty>
concept IsUnit = requires(Ty elem)
{
    elem.DIM_S;
    elem.DIM_M;
    elem.DIM_KG;
    elem.DIM_A;
    elem.DIM_K;
    elem.DIM_MOL;
    elem.DIM_CD;

    elem.value;
};

template <IsUnit First, IsUnit Second>
struct UnitEqual
{
    static constexpr bool EQUAL_S = First::DIM_S == Second::DIM_S;
    static constexpr bool EQUAL_M = First::DIM_M == Second::DIM_M;
    static constexpr bool EQUAL_KG = First::DIM_KG == Second::DIM_KG;
    static constexpr bool EQUAL_A = First::DIM_A == Second::DIM_A;
    static constexpr bool EQUAL_K = First::DIM_K == Second::DIM_K;
    static constexpr bool EQUAL_MOL = First::DIM_MOL == Second::DIM_MOL;
    static constexpr bool EQUAL_CD = First::DIM_CD == Second::DIM_CD;

    static constexpr bool EQUAL_ALL = EQUAL_S && EQUAL_M && EQUAL_KG && EQUAL_A && EQUAL_K && EQUAL_MOL && EQUAL_CD;
};

template <IsUnit First, IsUnit Second>
constexpr bool UnitEqualValue = UnitEqual<First, Second>::EQUAL_ALL;

template <int S, int M, int KG, int A, int K, int MOL, int CD>
struct Unit
{
    static constexpr int DIM_S = S;
    static constexpr int DIM_M = M;
    static constexpr int DIM_KG = KG;
    static constexpr int DIM_A = A;
    static constexpr int DIM_K = K;
    static constexpr int DIM_MOL = MOL;
    static constexpr int DIM_CD = CD;

    double value;

    constexpr Unit() noexcept
        : value(1.0)
    { }

    constexpr Unit(const double val) noexcept
        : value(val)
    { }

    constexpr Unit operator+(const Unit& other) const noexcept
    {
        return Unit{ this->value + other.value };
    }

    constexpr Unit operator-(const Unit& other) const noexcept
    {
        return Unit{ this->value - other.value };
    }

    constexpr Unit operator-() const noexcept
    {
        return Unit{ -this->value };
    }

    template <int S2, int M2, int KG2, int A2, int K2, int MOL2, int CD2>
    constexpr auto operator*(const Unit<S2, M2, KG2, A2, K2, MOL2, CD2>& other) const noexcept
    {
        return Unit<S + S2, M + M2, KG + KG2, A + A2, K + K2, MOL + MOL2, CD + CD2>{ this->value * other.value };
    }

    constexpr Unit operator*(const double scalar) const noexcept
    {
        return Unit{ this->value * scalar };
    }

    template <int S2, int M2, int KG2, int A2, int K2, int MOL2, int CD2>
    constexpr auto operator/(const Unit<S2, M2, KG2, A2, K2, MOL2, CD2>& other) const noexcept
    {
        return Unit<S - S2, M - M2, KG - KG2, A - A2, K - K2, MOL - MOL2, CD - CD2>{ this->value / other.value };
    }

    constexpr Unit operator/(const double scalar) const noexcept
    {
        return Unit{ this->value / scalar };
    }

    constexpr auto operator()(const double value) const noexcept
    {
        return Unit<S, M, KG, A, K, MOL, CD>{ this->value * value };
    }

    constexpr DimArray get_dimensions() const noexcept
    {
        return { S, M, KG, A, K, MOL, CD };
    }
};

template <int S, int M, int KG, int A, int K, int MOL, int CD>
constexpr auto operator*(const double scalar, const Unit<S, M, KG, A, K, MOL, CD>& unit) noexcept
{
    return unit * scalar;
}

template <int S, int M, int KG, int A, int K, int MOL, int CD>
constexpr auto operator/(const double scalar, const Unit<S, M, KG, A, K, MOL, CD>& unit) noexcept
{
    return unit / scalar;
}

template <auto& unit, int power>
struct Power
{
    using UnitType = std::remove_cvref_t<decltype(unit)>;

    static constexpr int UNIT_S = UnitType::DIM_S;
    static constexpr int UNIT_M = UnitType::DIM_M;
    static constexpr int UNIT_KG = UnitType::DIM_KG;
    static constexpr int UNIT_A = UnitType::DIM_A;
    static constexpr int UNIT_K = UnitType::DIM_K;
    static constexpr int UNIT_MOL = UnitType::DIM_MOL;
    static constexpr int UNIT_CD = UnitType::DIM_CD;

    using NewType = Unit<UNIT_S * power, UNIT_M * power, UNIT_KG * power, UNIT_A * power, UNIT_K * power, UNIT_MOL * power, UNIT_CD * power>;
};

template <auto& unit, int power>
using PowerType = Power<unit, power>::NewType;

template <IsUnit UnitT, int power>
struct TPower
{
    static constexpr int UNIT_S = UnitT::DIM_S;
    static constexpr int UNIT_M = UnitT::DIM_M;
    static constexpr int UNIT_KG = UnitT::DIM_KG;
    static constexpr int UNIT_A = UnitT::DIM_A;
    static constexpr int UNIT_K = UnitT::DIM_K;
    static constexpr int UNIT_MOL = UnitT::DIM_MOL;
    static constexpr int UNIT_CD = UnitT::DIM_CD;

    using NewType = Unit<UNIT_S * power, UNIT_M * power, UNIT_KG * power, UNIT_A * power, UNIT_K * power, UNIT_MOL * power, UNIT_CD * power>;
};

template <IsUnit Unit, int power>
using TPowerType = TPower<Unit, power>::NewType;

inline constexpr auto Scalar = Unit<0, 0, 0, 0, 0, 0, 0>{};
inline constexpr auto Second = Unit<1, 0, 0, 0, 0, 0, 0>{};
inline constexpr auto Meter = Unit<0, 1, 0, 0, 0, 0, 0>{};
inline constexpr auto Kilogram = Unit<0, 0, 1, 0, 0, 0, 0>{};
inline constexpr auto Ampere = Unit<0, 0, 0, 1, 0, 0, 0>{};
inline constexpr auto Kelvin = Unit<0, 0, 0, 0, 1, 0, 0>{};
inline constexpr auto Mole = Unit<0, 0, 0, 0, 0, 1, 0>{};
inline constexpr auto Candela = Unit<0, 0, 0, 0, 0, 0, 1>{};

namespace Types
{

using Scalar = decltype(SI::Scalar);
using Second = decltype(SI::Second);
using Meter = decltype(SI::Meter);
using Kilogram = decltype(SI::Kilogram);
using Ampere = decltype(SI::Ampere);
using Kelvin = decltype(SI::Kelvin);
using Mole = decltype(SI::Mole);
using Candela = decltype(SI::Candela);

}

template <auto& Ty>
using AsType = std::remove_cvref_t<decltype(Ty)>;

template <int exponent, IsUnit Ty>
constexpr auto pow(const Ty& val)
{
    static_assert(exponent > 0, "Exponent must be positive. Negative exponents require division.");

    using ResultType = TPowerType<Ty, exponent>;
    const double factor = val.value;
    double scalar = factor;

    for (int i = 1; i < exponent; ++i)
    {
        scalar *= factor;
    }

    return ResultType{}(scalar);
}

}

#endif // SILO_CORE

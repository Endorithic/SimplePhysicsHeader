#ifndef SILO_UNITS
#define SILO_UNITS

#include "core.hpp"

namespace SI
{

namespace Units
{

inline constexpr auto Newton = SI::Kilogram * SI::Meter / SI::PowerType<SI::Second, 2>{};
inline constexpr auto Joule = SI::Kilogram * SI::PowerType<SI::Meter, 2>{} / SI::PowerType<SI::Second, 2>{};
inline constexpr auto Coulomb = SI::Ampere * SI::Second;
inline constexpr auto Farad = SI::PowerType<SI::Second, 4>{} * SI::PowerType<SI::Ampere, 2>{} / (SI::Kilogram * SI::PowerType<SI::Meter, 2>{});
inline constexpr auto Pascal = SI::Kilogram / (SI::Meter * SI::PowerType<SI::Second, 2>{});
inline constexpr auto Watt = SI::Kilogram * SI::PowerType<SI::Meter, 2>{} / SI::PowerType<SI::Second, 3>{};
inline constexpr auto Volt = SI::Kilogram * SI::PowerType<SI::Meter, 2>{} / (SI::PowerType<SI::Second, 3>{} * SI::Ampere);
inline constexpr auto Hertz = SI::Scalar / SI::Second;
inline constexpr auto Ohm = SI::Kilogram * SI::PowerType<SI::Meter, 2>{} / (SI::PowerType<SI::Second, 3>{} * SI::PowerType<SI::Ampere, 2>{});
inline constexpr auto Weber = SI::Kilogram * SI::PowerType<SI::Meter, 2>{} / (SI::PowerType<SI::Second, 2>{} * SI::Ampere);
inline constexpr auto Tesla = SI::Kilogram / (SI::PowerType<SI::Second, 2>{} * SI::Ampere);

} // namespace Units

} // namespace SI

#endif

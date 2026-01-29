#ifndef SILO_CONSTANTS
#define SILO_CONSTANTS

#include "core.hpp"
#include "units.hpp"

namespace SI
{

namespace Constants
{

inline constexpr auto StefanBoltzmann = 5.670374e-8 * SI::Kilogram / (SI::PowerType<SI::Second, 3>{} * SI::PowerType<SI::Kelvin, 4>{});
inline constexpr auto LightSpeed = 299792458.0 * SI::Meter / SI::Second;
inline constexpr auto Gravitational = 6.674302e-11 * SI::PowerType<SI::Meter, 3>{} / (SI::Kilogram * SI::PowerType<SI::Second, 2>{});
inline constexpr auto PlanckConstant = 6.626070e-34 * SI::Units::Joule * SI::Second;
inline constexpr auto ReducedPlanck = 1.054572e-34 * SI::Units::Joule * SI::Second;
inline constexpr auto ElementaryCharge = 1.602177e-19 * SI::Units::Coulomb;
inline constexpr auto BoltzmannConstant = 1.380649e-23 * SI::Units::Joule / SI::Kelvin;
inline constexpr auto AvogadrosConstant = 6.022141e23 * SI::Scalar / SI::Mole;
inline constexpr auto VacuumPermittivity = 8.854188e-12 * SI::Units::Farad / SI::Meter;
inline constexpr auto VacuumPermeability = 1.256637e-6 * SI::Units::Newton / SI::PowerType<SI::Ampere, 2>{};

}

} // namespace SI

#endif // SILO_CONSTANTS

# Units and Unit types
---
## How to use fundamental units.
As a part of the header file, the seven standard SI units are already ready to go. Those are:

1. Second
2. Meter
3. Kilogram
4. Ampere
5. Kelvin
6. Mole
7. Candela

On top of that, an additional `Scalar` unit is provided. This represents a dimensionless quanitity. 
This is included because while units have multiplication and division overloded for other units, they have 
not implemented the same for numerical types like `double` or `int`. In order to derive certain units, we 
need to utilize the `Scalar` unit. We will discuss unit derivation further later.

By default, a unit is instantiated with the `value` 1.0. The `value` represents the actual numerical value of that instance. 
The '10' in '10 meters', the '5' in '5 volts', etc. 

Each of the eight provided units in the `SI::*` namespace are actually simply templated instances of the `Unit<>` struct. 
Therefore, to further create instances of said units, an `operator()` method is provided. Simply call the desired unit  
with the desired scale, and you will create a new instance of that unit with the provided `value`. 
Note that the resulting `value` is not actually simply equal to the `value` you called the instance with. 
It is rather the product of the argument `value` and the public `value` member of the instance on which `operator()` was called. 
When using the standard provided `SI::*` units instances, this is not an issue as those, as previously mentioned, all have a value of 1.0.

To demonstrate how this works, say we create our own imaginary units. We first have `1 plush` equal to `10 meters`, and then `1 flag` equal to `10 plush`.
If we first instantiate `plush` like this:
```cpp
static constexpr auto Plush = SI::Meter(10.0);
```
We can the build on that like this:
```cpp
static constexpr auto Flag = Plush(10.0);
```
The factors will bu multiplied, leaving a total value of `10.0 * 10.0 = 100.0`. This value represents how big our unit is in SI units, namely `100.0 meters`.

## Unit Types
In this library, every unit is represented using a single struct, `Unit`. This `Unit` struct stores all the information about a unit's dimensionality as template parameters.
Because of that, it's incredibly tedious to manually specify the desired type all the time. Imagine if we needed to type out `Unit<-2, 1, 0, 0, 0, 0, 0>` every time we wanted
acceleration. To solve this, two methods of specifying the unit are provided.

  ### Fundamental Types
  For fundamental types, an explicit group of pre-defined type-aliases are defined. They are all located in the `SI::Types::*` namespace.
  For example, the following function will only take instances of the unit `Second`, and will return an instance of the unit `Meter`.
  ```cpp
  SI::Types::Meter func(const SI::Types::Second& time)
  {
      // Code goes here.
  }
  ```
  
  ### Derived Types
  Because predefining every single possible type-alias is an incredibly tedious task, a dynamic alternative is provided, `SI::AsType<>`. This is a helper class
  designed to take an *instance* of a unit, and provide the user with the underlying unit type. For example, if custom units are defined, use `SI::AsType<>` as follows:
  ```cpp
  static constexpr auto Velocity = SI::Meter / SI::Second;
  static constexpr auto Acceleration = Velocity / SI::Second;
 
  SI::AsType<Velocity> func(const SI::AsType<Acceleration>& acc, const SI::Second& time)
  {
      // Code goes here.
  }
  ```
  Note that `SI::AsType<>` is functionally similar to the standard C++ `decltype()` utility, but also removes any `const`, `volatile`, or `reference` qualifier.

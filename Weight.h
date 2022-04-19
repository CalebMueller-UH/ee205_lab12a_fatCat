///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.h
/// @version 1.0
///
/// @author Caleb Mueller <mc61@hawaii.edu>
/// @date   11_Apr_2022
///////////////////////////////////////////////////////////////////////////////
#ifndef EE205_LAB12A_FATCAT_WEIGHT_H
#define EE205_LAB12A_FATCAT_WEIGHT_H

#include <ostream>
#include <iostream>
#include <string>
#include <exception>

#include <assert.h>

using namespace std;

#define PROGRAM_NAME "Fat Cat"

class Weight {
public:  /////////////////////////////////// Enumerations ///////////////////////////////////
    enum UnitOfWeight {
        POUNDS, KILOS, SLUGS
    };

public:  /////////////////////////////////// Constants ///////////////////////////////////
    static const float UNKNOWN_WEIGHT;
    static const float KILOS_IN_A_POUND;
    static const float SLUGS_IN_A_POUND;
    static const UnitOfWeight DEFAULT_UNIT_OF_WEIGHT;
    static const float DEFAULT_MAX_WEIGHT;
    static const std::string POUND_LITERAL;
    static const std::string SLUG_LITERAL;
    static const std::string KILO_LITERAL;

public:  /////////////////////////////////// Static Methods ///////////////////////////////////
    static float fromKilogramsToPounds(const float weightInKilos) noexcept;

    static float fromPoundsToKilograms(const float weightInPounds) noexcept;

    static float fromSlugsToPounds(const float weightInSlugs) noexcept;

    static float fromPoundsToSlugs(const float weightInPounds) noexcept;

    static float convertWeight(const float fromWeight, const UnitOfWeight fromUnit, const UnitOfWeight toUnit) noexcept;

public:  /////////////////////////////////// Class Constructors ///////////////////////////////////
    // ↓ #1 Default Constructor: delegates to #7 with all default values
    Weight() noexcept;

    // ↓ #2 only newWeight parameter provided: delegates to #7 with default values for _unitOfWeight and _maxWeight
    Weight(float newWeight);

    // ↓ #3 Only newUnitOfWeight parameter provided: delegates to #7 with default values for _weight and _unitOfWeight
    Weight(UnitOfWeight newUnitOfWeight) noexcept;

    // ↓ #4 newWeight and newUnitOfWeight parameters provided: delegates to #7 with default value for _maxWeight
    Weight(float newWeight, UnitOfWeight newUnitOfWeight) noexcept;

    // ↓ #5  newWeight and newMaxWeight provided: delegates to #7 with default value for _unitOfWeight
    Weight(float newWeight, float newMaxWeight) noexcept;

    // ↓ #6  newUnitOfWeight and newMaxWeight provided: delegates to #7 with default value for _weight
    Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;

    // ↓ #7  all member variables provided as parameters
    Weight(float newWeight, UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;

public:  /////////////////////////////////// Operators ///////////////////////////////////
    bool operator==(const Weight &rhs) const;

    bool operator<(const Weight &rhs) const;

    Weight &operator+=(const float &rhs_weight);

private:  /////////////////////////////////// Private Member Variables ///////////////////////////////////
    UnitOfWeight _unitOfWeight{DEFAULT_UNIT_OF_WEIGHT};
    float _weight{UNKNOWN_WEIGHT};
    float _maxWeight{DEFAULT_MAX_WEIGHT};
    bool _bIsKnown{false}; ///< bool flag for if _weight has been set to a valid value
    bool _bHasMax{false}; ///< bool flag for if _maxWeight has been set to a valid value

public:  /////////////////////////////////// Public Class Methods ///////////////////////////////////
    bool weightIsKnown() const noexcept;

    bool hasMaxWeight() const noexcept;

    float getWeight() const noexcept;

    float getWeight(const UnitOfWeight weightUnits) const noexcept;

    float getMaxWeight() const noexcept;

    UnitOfWeight getUnitOfWeight() const noexcept;

    void setWeight(const float newWeight);

    void setWeight(const float newWeight, UnitOfWeight weightUnits);

    bool weightIsValid(const float checkWeight) const noexcept;

    bool maxWeightIsValid(const float checkWeight) const noexcept;

    bool validate() const noexcept;

    void dump() const noexcept;

    void setMaxWeight(const float newMaxWeight);

};

std::ostream &operator<<(std::ostream &lhs_stream, const Weight::UnitOfWeight rhsUnit);

#endif //EE205_LAB12A_FATCAT_WEIGHT_H

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
#include <string>

#include <assert.h>

using namespace std;

class Weight {
public:  /////////////////////////////////// Enumerations ///////////////////////////////////
    enum UnitOfWeight { POUNDS, KILOS, SLUGS };

public:  /////////////////////////////////// Constants ///////////////////////////////////
    static const float UNKNOWN_WEIGHT;
    static const float KILOS_IN_A_POUND;
    static const float SLUGS_IN_A_POUND;
    static const UnitOfWeight DEFAULT_UNIT_OF_WEIGHT;
    static const std::string POUND_LITERAL;
    static const std::string SLUG_LITERAL;
    static const std::string KILOGRAM_LITERAL;

public:  /////////////////////////////////// Static Methods ///////////////////////////////////
    static float fromKilogramsToPounds(float weightInKilos) noexcept;
    static float fromPoundsToKilograms(float weightInPounds) noexcept;
    static float fromSlugsToPounds(float weightInSlugs) noexcept;
    static float fromPoundsToSlugs(float weightInPounds) noexcept;
    static float convertWeight(float fromWeight, UnitOfWeight fromUnit, UnitOfWeight toUnit) noexcept;

public:  /////////////////////////////////// Class Constructors ///////////////////////////////////
    // ↓ #1 Default Constructor: delegates to #9 with all default values
    Weight() noexcept;
    // ↓ #2 explicit with only weight parameter provided: delegates to #9 with default values for those not given
    Weight(float newWeight);
    // ↓ #3 explicit with only UnitOfWeight parameter provided: delegates to #9 with default values for those not given
    Weight(UnitOfWeight newUnitOfWeight) noexcept;
    // ↓ #4 explicit with only UnitOfWeight parameter provided: delegates to #9 with default values for those not given
    Weight(float newWeight, UnitOfWeight newUnitOfWeight) noexcept;
    // ↓ #5 explicit with newWeight and newMaxWeight provided: delegates to #9 with default value for UnitOfWeight
    Weight(float newWeight, float newMaxWeight) noexcept;
    // ↓ #6 explicit with newUnitOfWeight and newMaxWeight provided: delegates to #9 with default value for weight
    Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;
    // ↓ #7 explicit with all member variables provided as parameters
    Weight(float newWeight, UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;

public:  /////////////////////////////////// Operators ///////////////////////////////////
    bool operator==(const Weight &rhsWeight) const;
    bool operator<(const Weight &rhsWeight) const;
    bool operator+(const Weight &rhsAddToWeight) const;
    Weight& operator+=(float rhs_addToWeight);

private:  /////////////////////////////////// Private Member Variables ///////////////////////////////////
    UnitOfWeight _unitOfWeight; ///< Intentionally non-initialized so that it may be properly assigned during instantiation
    float _weight{UNKNOWN_WEIGHT}; ///< weight of animal in units set by _unitOfWeight
    float _maxWeight{UNKNOWN_WEIGHT}; ///< max weight of an animal in units set by _unitOfWeight
    bool bIsKnown{false}; ///< bool flag for if _weight is set to a valid entry greater than 0 and not unknown
    bool bHasMax{false}; ///< bool flag for if _maxWeight is set to a valid entry greater than 0 and not unknown

public:  /////////////////////////////////// Public Class Methods ///////////////////////////////////
    bool isWeightKnown() const noexcept;
    bool hasMaxWeight() const noexcept;
    float getWeight() const noexcept;
    float getWeight(UnitOfWeight weightUnits) const noexcept;
    float getMaxWeight() const noexcept;
    UnitOfWeight getUnitOfWeight() const noexcept;
    void setWeight(float newWeight);
    void setWeight(float newWeight, UnitOfWeight weightUnits);
    bool isWeightValid(float checkWeight) const noexcept;
    bool validate() const noexcept;
    void dump() const noexcept;
    void setMaxWeight(float newMaxWeight);


private:  /////////////////////////////////// Private Class Methods ///////////////////////////////////



};


#endif //EE205_LAB12A_FATCAT_WEIGHT_H

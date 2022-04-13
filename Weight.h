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

#include <iostream>
#include <string>

using namespace std;

class Weight {

public:  /////////////////////////////////// Public Member Variables ///////////////////////////////////
    enum UnitOfWeight { POUNDS, KILOS, SLUGS };

private:  /////////////////////////////////// Private Member Variables ///////////////////////////////////
    UnitOfWeight _unitOfWeight{DEFAULT_UNIT_OF_WEIGHT}; // Default = POUNDS
    float _weight; ///< weight of animal in units set by _unitOfWeight
    float _maxWeight{UNKNOWN_WEIGHT}; ///< max weight of an animal in units set by _unitOfWeight
    bool bIsKnown; ///<
    bool bHasMax; ///<

public:  /////////////////////////////////// Constants ///////////////////////////////////
    static constexpr float UNKNOWN_WEIGHT = -1.0;
    static constexpr float KILOS_IN_A_POUND = 0.453592;
    static constexpr float SLUGS_IN_A_POUND = 0.031081;
    static constexpr UnitOfWeight DEFAULT_UNIT_OF_WEIGHT = POUNDS;
    static const std::string POUND_LITERAL;
    static const std::string SLUG_LITERAL;
    static const std::string KILOGRAM_LITERAL;

public:  /////////////////////////////////// Public Class Methods ///////////////////////////////////
    bool isWeightKnown() const noexcept;

    bool hasMaxWeight() const noexcept;

    float getWeight() const noexcept;

    float getWeight(UnitOfWeight weightUnits) const noexcept;

    UnitOfWeight getUnitOfWeight() const noexcept;

    float getMaxWeight() const noexcept;

private:  /////////////////////////////////// Private Class Methods ///////////////////////////////////


public:  /////////////////////////////////// Class Constructors ///////////////////////////////////
    // #1 Default Constructor: delegates to #9 with all default values
    Weight() noexcept;

    // #2 explicit with only weight parameter provided: delegates to #9 with default values for those not given
    Weight(float newWeight);

    // #3 explicit with only UnitOfWeight parameter provided: delegates to #9 with default values for those not given
    Weight(UnitOfWeight newUnitOfWeight) noexcept;

    // #4 explicit with only UnitOfWeight parameter provided: delegates to #9 with default values for those not given
    Weight(float newWeight, UnitOfWeight newUnitOfWeight) noexcept;

    // #5 explicit with newWeight and newMaxWeight provided: delegates to #9 with default value for UnitOfWeight
    Weight(float newWeight, float newMaxWeight) noexcept;

    // #6 explicit with newUnitOfWeight and newMaxWeight provided: delegates to #9 with default value for weight
    Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;

    // #7 explicit with all member variables provided as parameters
    Weight(float newWeight, UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept;

};


#endif //EE205_LAB12A_FATCAT_WEIGHT_H

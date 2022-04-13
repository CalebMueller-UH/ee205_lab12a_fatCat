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
public:  /////////////////////////////////// Public Class Members ///////////////////////////////////
    enum UnitOfWeight { POUNDS, KILOS, SLUGS };

    // Explicit Constructor with default values for resolving implicit call
    Weight(UnitOfWeight unitOfWeight=DEFAULT_UNIT_OF_WEIGHT, float weight=UNKNOWN_WEIGHT);

public:  /////////////////////////////////// Public Class Methods ///////////////////////////////////
    UnitOfWeight getUnitOfWeight() const noexcept;

    float getWeight() const noexcept;

    float getMaxWeight() const noexcept;


public:  /////////////////////////////////// Constants ///////////////////////////////////
    static constexpr float UNKNOWN_WEIGHT = -1.0;
    static constexpr float KILOS_IN_A_POUND = 0.453592;
    static constexpr float SLUGS_IN_A_POUND = 0.031081;
    static constexpr UnitOfWeight DEFAULT_UNIT_OF_WEIGHT = POUNDS;

    static const std::string POUND_LITERAL;

private:  /////////////////////////////////// Private Member Variables ///////////////////////////////////
    UnitOfWeight _unitOfWeight{DEFAULT_UNIT_OF_WEIGHT}; // Default = POUNDS
    float _weight{UNKNOWN_WEIGHT}; ///< weight of animal in units set by _unitOfWeight
    float _maxWeight{UNKNOWN_WEIGHT}; ///< max weight of an animal in units set by _unitOfWeight
    bool bIsKnown; ///<
    bool bHasMax; ///<

};


#endif //EE205_LAB12A_FATCAT_WEIGHT_H

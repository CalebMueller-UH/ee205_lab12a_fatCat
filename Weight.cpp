///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.cpp
/// @version 1.0
///
/// @author Caleb Mueller <mc61@hawaii.edu>
/// @date   11_Apr_2022
///////////////////////////////////////////////////////////////////////////////
#include "Weight.h"

/////////////////////////////////// Constants ///////////////////////////////////
const float Weight::UNKNOWN_WEIGHT = -1.0;
const float Weight::KILOS_IN_A_POUND = 0.453592;
const float Weight::SLUGS_IN_A_POUND = 0.031081;
const Weight::UnitOfWeight Weight::DEFAULT_UNIT_OF_WEIGHT = POUNDS;
const std::string Weight::POUND_LITERAL = "lbs";
const std::string Weight::SLUG_LITERAL = "slugs";
const std::string Weight::KILO_LITERAL = "kgs";

/////////////////////////////////// Static Methods ///////////////////////////////////
float Weight::fromKilogramsToPounds(float weightInKilos) noexcept
{
    return weightInKilos / KILOS_IN_A_POUND;
}

float Weight::fromPoundsToKilograms(float weightInPounds) noexcept
{
    return weightInPounds * KILOS_IN_A_POUND;
}

float Weight::fromSlugsToPounds(float weightInSlugs) noexcept
{
    return weightInSlugs / SLUGS_IN_A_POUND;
}

float Weight::fromPoundsToSlugs(float weightInPounds) noexcept
{
    return weightInPounds * SLUGS_IN_A_POUND;
}

float Weight::convertWeight(float fromWeight, Weight::UnitOfWeight fromUnit, Weight::UnitOfWeight toUnit) noexcept
{
    switch(fromUnit)
    {
        case POUNDS:
            switch(toUnit)
            {
                case POUNDS:
                    return fromWeight;
                case SLUGS:
                    return fromPoundsToSlugs(fromWeight);
                case KILOS:
                    return fromPoundsToKilograms(fromWeight);
                default:
                    assert(0);
            }

        case SLUGS:
            switch(toUnit)
            {
            case POUNDS:
                return fromSlugsToPounds(fromWeight);
            case SLUGS:
                return fromWeight;
            case KILOS:
                return fromPoundsToKilograms(fromSlugsToPounds(fromWeight));
            default:
                assert(0);
            }

        case KILOS:
            switch(toUnit)
            {
            case POUNDS:
                return fromKilogramsToPounds(fromWeight);
            case SLUGS:
                return fromPoundsToSlugs(fromKilogramsToPounds(fromWeight));
            case KILOS:
                return fromWeight;
            default:
                assert(0);
            }
        default:
            assert(0);
    }
}

/////////////////////////////////// Class Constructors ///////////////////////////////////
// ↓ #1
Weight::Weight() noexcept : Weight(UNKNOWN_WEIGHT, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT){}
// ↓ #2
Weight::Weight(float newWeight) : Weight(newWeight, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT){}
// ↓ #3
Weight::Weight(Weight::UnitOfWeight newUnitOfWeight) noexcept : Weight(UNKNOWN_WEIGHT, newUnitOfWeight, UNKNOWN_WEIGHT) {}
// ↓ #4
Weight::Weight(float newWeight, Weight::UnitOfWeight newUnitOfWeight) noexcept : Weight(newWeight, newUnitOfWeight, UNKNOWN_WEIGHT) {}
// ↓ #5
Weight::Weight(float newWeight, float newMaxWeight) noexcept : Weight(newWeight, DEFAULT_UNIT_OF_WEIGHT, newMaxWeight) {}
// ↓ #6
Weight::Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept : Weight(UNKNOWN_WEIGHT, newUnitOfWeight, newMaxWeight) {}
// ↓ #7
Weight::Weight(float newWeight, Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept : _unitOfWeight{newUnitOfWeight}
{
    if(isWeightValid(newWeight))
    {
        _weight = newWeight;
        bIsKnown = true;
    } else
    {
        _weight = UNKNOWN_WEIGHT;
    }

    if(isWeightValid(newMaxWeight))
    {
        _maxWeight = newMaxWeight;
        bHasMax = true;
    } else
    {
        _maxWeight = UNKNOWN_WEIGHT;
    }
}

/////////////////////////////////// Operators ///////////////////////////////////
bool Weight::operator==(const Weight &rhsWeight) const
{
    float lhs_weight = (bIsKnown) ? getWeight(Weight::POUNDS) : 0;
    float rhs_weight = (rhsWeight.bIsKnown) ?
                       rhsWeight.getWeight(Weight::POUNDS) : 0;
    return lhs_weight == rhs_weight;
}

bool Weight::operator<(const Weight &rhsWeight) const
{
    float lhs_weight = (bIsKnown) ? this->getWeight(Weight::POUNDS) : 0;
    float rhs_weight = (bIsKnown) ? rhsWeight.getWeight(Weight::POUNDS) : 0;
    return lhs_weight == rhs_weight;
}

Weight &Weight::operator+=(float &rhs_addToWeight)
{
    float sum = this->getWeight() + rhs_addToWeight;
    if(!isWeightValid(sum))
    {
        throw invalid_argument(PROGRAM_NAME " += operation results is an invalid weight!");
    }
    return *this;
}

std::ostream& operator<<( ostream& lhs_stream, const Weight::UnitOfWeight rhs_UnitOfWeight ) {
    switch( rhs_UnitOfWeight ) {
        case Weight::POUNDS:
            return lhs_stream << Weight::POUND_LITERAL;
        case Weight::KILOS:
            return lhs_stream << Weight::KILO_LITERAL;
        case Weight::SLUGS:
            return lhs_stream << Weight::SLUG_LITERAL;
        default:
            throw out_of_range( "The unit can’t be mapped to a string" );
    }
}

/////////////////////////////////// Public Class Methods ///////////////////////////////////
bool Weight::isWeightKnown() const noexcept
{
    return (isWeightValid(_weight)) ? true : false;
}

bool Weight::hasMaxWeight() const noexcept
{
    return (isWeightValid(_maxWeight)) ? true : false;
}

float Weight::getWeight() const noexcept
{
    return bIsKnown ? _weight : UNKNOWN_WEIGHT;
}

float Weight::getWeight(Weight::UnitOfWeight weightUnits) const noexcept
{
    return (bIsKnown) ? convertWeight(_weight, _unitOfWeight, weightUnits) : 0;
}

float Weight::getMaxWeight() const noexcept
{
    return _maxWeight;
}

Weight::UnitOfWeight Weight::getUnitOfWeight() const noexcept
{
    return _unitOfWeight;
}

void Weight::setWeight(float newWeight)
{
    if(isWeightValid(newWeight))
    {
        _weight = newWeight;
    }
}

void Weight::setWeight(float newWeight, Weight::UnitOfWeight weightUnits)
{
    if(isWeightValid(newWeight))
    {
        _weight = newWeight;
        _unitOfWeight = weightUnits;
    }
}

bool Weight::isWeightValid(float checkWeight) const noexcept
{
    return (checkWeight > 0 && checkWeight != UNKNOWN_WEIGHT) ? true : false;
}

bool Weight::validate() const noexcept
{
    return (isWeightValid(_weight) && isWeightValid(_maxWeight)) ? true : false;
}

void Weight::dump() const noexcept
{
}

void Weight::setMaxWeight(float newMaxWeight)
{
    // Can only set _maxWeight if it isn't already set    ↓
    if(isWeightValid(newMaxWeight) && !isWeightValid(_maxWeight))
    {
        _maxWeight = newMaxWeight;
    }
}



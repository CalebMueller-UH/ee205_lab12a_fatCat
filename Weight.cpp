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

const std::string Weight::POUND_LITERAL = "LBs";
static const std::string SLUG_LITERAL = "SLUGs";
static const std::string KILOGRAM_LITERAL = "KGs";


/////////////////////////////////// Public Class Methods ///////////////////////////////////
bool Weight::isWeightKnown() const noexcept {
    return false;
}

bool Weight::hasMaxWeight() const noexcept {
    return false;
}

Weight::UnitOfWeight Weight::getUnitOfWeight() const noexcept {
return _unitOfWeight;
}

float Weight::getWeight() const noexcept {
return _weight;
}

float Weight::getWeight(Weight::UnitOfWeight weightUnits) const noexcept {
return 0;
}

float Weight::getMaxWeight() const noexcept {
return _maxWeight;
}


/////////////////////////////////// Class Constructors ///////////////////////////////////
// #1
Weight::Weight() noexcept : Weight(UNKNOWN_WEIGHT, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT){}

// #2
Weight::Weight(float newWeight) : Weight(newWeight, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT){}

// #3
Weight::Weight(Weight::UnitOfWeight newUnitOfWeight) noexcept : Weight(UNKNOWN_WEIGHT, newUnitOfWeight, UNKNOWN_WEIGHT) {}

// #4
Weight::Weight(float newWeight, Weight::UnitOfWeight newUnitOfWeight) noexcept : Weight(newWeight, newUnitOfWeight, UNKNOWN_WEIGHT) {}

// #5
Weight::Weight(float newWeight, float newMaxWeight) noexcept : Weight(newWeight, DEFAULT_UNIT_OF_WEIGHT, newMaxWeight) {}

// #6
Weight::Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept : Weight(UNKNOWN_WEIGHT, newUnitOfWeight, newMaxWeight) {}

// #7
Weight::Weight(float newWeight, Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight) noexcept : _weight{newWeight}, _unitOfWeight{newUnitOfWeight}, _maxWeight{newMaxWeight}{}





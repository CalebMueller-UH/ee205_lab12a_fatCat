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

/////////////////////////////////// Constants //////////////////////////////////////
const float Weight::UNKNOWN_WEIGHT = 0;
const float Weight::KILOS_IN_A_POUND = 0.453592;
const float Weight::SLUGS_IN_A_POUND = 0.031081;
const Weight::UnitOfWeight Weight::DEFAULT_UNIT_OF_WEIGHT = POUNDS;
const float Weight::DEFAULT_MAX_WEIGHT = 50;
const std::string Weight::POUND_LITERAL = "lbs";
const std::string Weight::SLUG_LITERAL = "slugs";
const std::string Weight::KILO_LITERAL = "kgs";

/////////////////////////////////// Static Methods //////////////////////////////////////
float Weight::fromKilogramsToPounds( const float weightInKilos ) noexcept
{
	return weightInKilos / KILOS_IN_A_POUND;
}

float Weight::fromPoundsToKilograms( const float weightInPounds ) noexcept
{
	return weightInPounds * KILOS_IN_A_POUND;
}

float Weight::fromSlugsToPounds( const float weightInSlugs ) noexcept
{
	return weightInSlugs / SLUGS_IN_A_POUND;
}

float Weight::fromPoundsToSlugs( const float weightInPounds ) noexcept
{
	return weightInPounds * SLUGS_IN_A_POUND;
}

float Weight::convertWeight( const float fromWeight, const Weight::UnitOfWeight fromUnit, const Weight::UnitOfWeight toUnit ) noexcept
{
	switch( fromUnit )
	{
		case POUNDS:
			switch( toUnit )
			{
				case POUNDS:
					return fromWeight;
				case SLUGS:
					return fromPoundsToSlugs( fromWeight );
				case KILOS:
					return fromPoundsToKilograms( fromWeight );
				default:
					assert( 0 );
			}

		case SLUGS:
			switch( toUnit )
			{
				case POUNDS:
					return fromSlugsToPounds( fromWeight );
				case SLUGS:
					return fromWeight;
				case KILOS:
					return fromPoundsToKilograms( fromSlugsToPounds( fromWeight ));
				default:
					assert( 0 );
			}

		case KILOS:
			switch( toUnit )
			{
				case POUNDS:
					return fromKilogramsToPounds( fromWeight );
				case SLUGS:
					return fromPoundsToSlugs( fromKilogramsToPounds( fromWeight ));
				case KILOS:
					return fromWeight;
				default:
					assert( 0 );
			}
		default:
			assert( 0 );
	}
}

/////////////////////////////////// Class Constructors //////////////////////////////////////
// ↓ #1 Default Constructor: delegates to #7 with all default values
Weight::Weight() noexcept : Weight( UNKNOWN_WEIGHT, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT ) {}

// ↓ #2 only newWeight parameter provided: delegates to #7 with default values for _unitOfWeight and _maxWeight
Weight::Weight( float newWeight ) : Weight( newWeight, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT ) {}

// ↓ #3 Only newUnitOfWeight parameter provided: delegates to #7 with default values for _weight and _unitOfWeight
Weight::Weight( Weight::UnitOfWeight newUnitOfWeight ) noexcept : Weight( UNKNOWN_WEIGHT, newUnitOfWeight, UNKNOWN_WEIGHT ) {}

// ↓ #4 newWeight and newUnitOfWeight parameters provided: delegates to #7 with default value for _maxWeight
Weight::Weight( float newWeight, Weight::UnitOfWeight newUnitOfWeight ) noexcept : Weight( newWeight, newUnitOfWeight, UNKNOWN_WEIGHT ) {}

// ↓ #5  newWeight and newMaxWeight provided: delegates to #7 with default value for _unitOfWeight
Weight::Weight( float newWeight, float newMaxWeight ) noexcept : Weight( newWeight, DEFAULT_UNIT_OF_WEIGHT, newMaxWeight ) {}

// ↓ #6  newUnitOfWeight and newMaxWeight provided: delegates to #7 with default value for _weight
Weight::Weight( UnitOfWeight newUnitOfWeight, float newMaxWeight ) noexcept : Weight( UNKNOWN_WEIGHT, newUnitOfWeight, newMaxWeight ) {}

// ↓ #7  all member variables provided as parameters
Weight::Weight( float newWeight, Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight ) noexcept : _unitOfWeight{ newUnitOfWeight }
{
	if( maxWeightIsValid( newMaxWeight ))
	{
		_maxWeight = newMaxWeight;
		_bHasMax = true;
	}
	else
	{
		_maxWeight = DEFAULT_MAX_WEIGHT;
	}

	if( weightIsValid( newWeight ))
	{
		_weight = newWeight;
		_bIsKnown = true;
	}
	else
	{
		_weight = UNKNOWN_WEIGHT;
	}
}

/////////////////////////////////// Operators //////////////////////////////////////
bool Weight::operator==( const Weight &rhs ) const
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float rhs_weight = ( rhs._bIsKnown ) ? rhs.getWeight( Weight::POUNDS ) : 0;
	return lhs_weight == rhs_weight;
}

bool Weight::operator<( const Weight &rhs ) const
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float rhs_weight = ( rhs._bIsKnown ) ? rhs.getWeight( Weight::POUNDS ) : 0;
	return lhs_weight < rhs_weight;
}

Weight &Weight::operator+=( const float &rhs_weight )
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float sum = lhs_weight + rhs_weight;
	if( !weightIsValid( sum ))
	{
		throw invalid_argument( PROGRAM_NAME
		                        " += operation results is an invalid weight!" );
	}
	setWeight( sum );
	return *this;
}

std::ostream &operator<<( std::ostream &lhs_stream, const Weight::UnitOfWeight rhsUnit )
{
	switch( rhsUnit )
	{
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

/////////////////////////////////// Public Class Methods //////////////////////////////////////
bool Weight::weightIsKnown() const noexcept
{
	return _bIsKnown;
}

bool Weight::hasMaxWeight() const noexcept
{
	return _bHasMax;
}

float Weight::getWeight() const noexcept
{
	return _bIsKnown ? _weight : 0;
}

float Weight::getWeight( const Weight::UnitOfWeight weightUnits ) const noexcept
{
	if( _bIsKnown )
	{
		return convertWeight( _weight, _unitOfWeight, weightUnits );
	}
	return 0; // (!_bisKnown)
}

float Weight::getMaxWeight() const noexcept
{
	return _maxWeight;
}

Weight::UnitOfWeight Weight::getUnitOfWeight() const noexcept
{
	return _unitOfWeight;
}

void Weight::setWeight( const float newWeight )
{
	if( weightIsValid( newWeight ))
	{
		_bIsKnown = true;
		_weight = newWeight;
	}
}

void Weight::setWeight( const float newWeight, Weight::UnitOfWeight weightUnits )
{
	if( weightIsValid( newWeight ))
	{
		_weight = convertWeight( newWeight, _unitOfWeight, weightUnits );
	}
}

bool Weight::weightIsValid( const float checkWeight ) const noexcept
{
	return ( checkWeight > 0 && checkWeight != UNKNOWN_WEIGHT && checkWeight <= _maxWeight );
}

bool Weight::maxWeightIsValid( const float checkMaxWeight ) const noexcept
{
	return ( checkMaxWeight > 0 && checkMaxWeight < DEFAULT_MAX_WEIGHT );
}

bool Weight::validate() const noexcept
{
	return ( weightIsValid( _weight ) && maxWeightIsValid( _maxWeight ));
}

void Weight::dump() const noexcept
{
	std::cout << "Weight: " << _weight << " " << _unitOfWeight << ", ";
	std::cout << "Max Weight: " << _maxWeight << " " << _unitOfWeight << std::endl;
}

void Weight::setMaxWeight( const float newMaxWeight )
{
	// Can only set _maxWeight if it isn't already set    ↓
	if( maxWeightIsValid( newMaxWeight ) && !maxWeightIsValid( _maxWeight ))
	{
		_maxWeight = newMaxWeight;
	}
}

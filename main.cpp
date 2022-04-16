#include <iostream>
#include <assert.h> // For assert tests

#include "Weight.h"

using namespace std;

int main() {
    cout << "Beginning Weight Class testing..." << endl;
    cout << "---------------------------------" << endl;
    /////////////// Constructor Testing //////////////////
    // Testing Constructor #1
    {
        auto *tw = new Weight();
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
        assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
        delete tw;
    }
    // Testing Constructor #2
    {
        auto *tw = new Weight(3.14);
        assert(tw->getWeight() == 3.14F);
        assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
        assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
        delete tw;
    }
    // Testing Constructor #3
    {
        auto *tw = new Weight(Weight::KILOS);
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::KILOS);
        assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
        delete tw;
    }
    // Testing Constructor #4
    {
        auto *tw = new Weight(3.14, Weight::SLUGS);
        assert(tw->getWeight() == 3.14F);
        assert(tw->getUnitOfWeight() == Weight::SLUGS);
        assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
        delete tw;
    }
    // Testing Constructor #5
    {
        auto *tw = new Weight(3.14, 48.7);
        assert(tw->getWeight() == (float)3.14);
        assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
        assert(tw->getMaxWeight() == 48.7F);
        delete tw;
    }
    // Testing Constructor #6
    {
        auto *tw = new Weight(Weight::KILOS, 48.7);
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::KILOS);
        assert(tw->getMaxWeight() == 48.7F);
        delete tw;
    }
    // Testing Constructor #7a
    {
        auto *tw = new Weight(1.23, Weight::POUNDS, 45.6);
        assert(tw->getWeight() == 1.23F);
        assert(tw->getUnitOfWeight() == Weight::POUNDS);
        assert(tw->getMaxWeight() == 45.6F);
        delete tw;
    }
    // Testing Constructor #7b
    {
        auto *tw = new Weight(-1.23, Weight::POUNDS, -45.6);
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::POUNDS);
        assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
        delete tw;
    }
    // Testing Constructor #7c
    {
        //
        auto *tw = new Weight(11, Weight::POUNDS, 10);
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::POUNDS);
        delete tw;
    }

    /////////////// Weight Unit Conversion Testing //////////////////
    {
        assert( Weight::convertWeight(1.0, Weight::POUNDS, Weight::POUNDS) == 1.0);
        assert( Weight::convertWeight(1.0, Weight::POUNDS, Weight::KILOS) == Weight::KILOS_IN_A_POUND);
        assert( Weight::convertWeight(1.0, Weight::POUNDS, Weight::SLUGS) == Weight::SLUGS_IN_A_POUND);

        assert( Weight::convertWeight(1.0, Weight::KILOS, Weight::KILOS) == 1.0);
        assert( Weight::convertWeight(1.0, Weight::KILOS, Weight::POUNDS) == 1 / Weight::KILOS_IN_A_POUND);
        assert( Weight::convertWeight(1.0, Weight::KILOS, Weight::SLUGS) == 1 / (Weight::KILOS_IN_A_POUND / Weight::SLUGS_IN_A_POUND));

        assert( Weight::convertWeight(1.0, Weight::SLUGS, Weight::SLUGS) == 1.0);
        assert( Weight::convertWeight(1.0, Weight::SLUGS, Weight::KILOS) == (Weight::KILOS_IN_A_POUND / Weight::SLUGS_IN_A_POUND));
        assert( Weight::convertWeight(1.0, Weight::SLUGS, Weight::POUNDS) == 1 / Weight::SLUGS_IN_A_POUND);
    }

    /////////////// Weight Operator Testing //////////////////
    {
        /*
         *  bool operator==(const Weight &rhsWeight) const;
            bool operator<(const Weight &rhsWeight) const;
            bool operator+=(const Weight &rhsAddToWeight) const;
            Weight& operator+=(float &rhs_addToWeight);
         */

        auto *a = new Weight(1.0, Weight::POUNDS, 10.0);
        auto *b = new Weight(1.5, Weight::POUNDS, 10.0);

        assert( (a == b) );
    }


    return 0;
}

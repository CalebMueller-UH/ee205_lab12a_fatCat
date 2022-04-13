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
        assert(tw->getMaxWeight() == Weight::UNKNOWN_WEIGHT);
        delete tw;
    }
    // Testing Constructor #2
    {
        auto *tw = new Weight(3.14);
        assert(tw->getWeight() == (float)3.14);
        assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
        assert(tw->getMaxWeight() == Weight::UNKNOWN_WEIGHT);
        delete tw;
    }
    // Testing Constructor #3
    {
        auto *tw = new Weight(Weight::KILOS);
        assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
        assert(tw->getUnitOfWeight() == Weight::KILOS);
        assert(tw->getMaxWeight() == Weight::UNKNOWN_WEIGHT);
        delete tw;
    }
    // Testing Constructor #4
    {
        auto *tw = new Weight(3.14, Weight::SLUGS);
        assert(tw->getWeight() == 3.14F);
        assert(tw->getUnitOfWeight() == Weight::SLUGS);
        assert(tw->getMaxWeight() == Weight::UNKNOWN_WEIGHT);
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
    // Testing Constructor #7
    {
        auto *tw = new Weight(1.23, Weight::POUNDS, 45.6);
        assert(tw->getWeight() == 1.23F);
        assert(tw->getUnitOfWeight() == Weight::POUNDS);
        assert(tw->getMaxWeight() == 45.6F);
        delete tw;
    }

    return 0;
}

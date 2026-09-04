// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/transaction.h"
#include "main.h"
#include "masternode-budget.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_tests)

BOOST_AUTO_TEST_CASE(release_protocol_version)
{
    BOOST_CHECK_EQUAL(PROTOCOL_VERSION, 70966);
}


BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    BOOST_CHECK_EQUAL(
        GetBlockValue(0, 0),
        2100000 * COIN
    );
}


BOOST_AUTO_TEST_CASE(new_reward_schedule_boundaries)
{
    BOOST_CHECK_EQUAL(GetBlockValue(999999, 0), 2 * COIN);

    CAmount expectedAt1000000 =
        (1000000 % 808 == 807) ? 808 * COIN : 2 * COIN;

    BOOST_CHECK_EQUAL(
        GetBlockValue(1000000, 0),
        expectedAt1000000
    );

    BOOST_CHECK_EQUAL(GetBlockValue(1000001, 0), 1 * COIN);
    BOOST_CHECK_EQUAL(GetBlockValue(1100000, 0), 1 * COIN);
    BOOST_CHECK_EQUAL(GetBlockValue(1100001, 0), COIN / 2);
    BOOST_CHECK_EQUAL(GetBlockValue(1200000, 0), COIN / 2);
    BOOST_CHECK_EQUAL(GetBlockValue(1200001, 0), COIN / 4);
    BOOST_CHECK_EQUAL(GetBlockValue(1300001, 0), COIN / 8);
}

BOOST_AUTO_TEST_CASE(new_masternode_reward_boundaries)
{
    BOOST_CHECK_EQUAL(
        GetMasternodePayment(
            1000001,
            GetBlockValue(1000001, 0),
            0
        ),
        85 * COIN / 100
    );

    BOOST_CHECK_EQUAL(
        GetMasternodePayment(
            1100001,
            GetBlockValue(1100001, 0),
            0
        ),
        85 * COIN / 200
    );
}



BOOST_AUTO_TEST_CASE(maximum_supply_cap)
{
    const CAmount maxSupply = Params().MaxMoneyOut();

    BOOST_CHECK_EQUAL(
        GetBlockValue(1000001, maxSupply),
        0
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(1000001, maxSupply - COIN / 2),
        COIN / 2
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(1000001, maxSupply - 1),
        1
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(1100001, maxSupply - COIN),
        COIN / 2
    );
}

BOOST_AUTO_TEST_CASE(reward_floor)
{
    const CAmount minimumReward = 20;

    BOOST_CHECK_EQUAL(
        GetBlockValue(3300001, 0),
        minimumReward
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(10000000, 0),
        minimumReward
    );
}

BOOST_AUTO_TEST_CASE(masternode_reward_at_floor)
{
    const CAmount minimumReward = 20;

    BOOST_CHECK_EQUAL(
        GetMasternodePayment(
            3300001,
            minimumReward,
            0
        ),
        17
    );
}

BOOST_AUTO_TEST_CASE(maximum_supply_cap_at_reward_floor)
{
    const CAmount maxSupply = Params().MaxMoneyOut();

    BOOST_CHECK_EQUAL(
        GetBlockValue(3300001, maxSupply - 19),
        19
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(3300001, maxSupply - 20),
        20
    );

    BOOST_CHECK_EQUAL(
        GetBlockValue(3300001, maxSupply),
        0
    );
}

BOOST_AUTO_TEST_CASE(budget_superblocks_disabled_after_activation)
{
    BOOST_CHECK(!budget.IsBudgetPaymentBlock(1000001));
    BOOST_CHECK(!budget.IsBudgetPaymentBlock(1100000));
    BOOST_CHECK(!budget.IsBudgetPaymentBlock(2000000));
}

BOOST_AUTO_TEST_SUITE_END()

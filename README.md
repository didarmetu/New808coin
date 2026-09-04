# New808coin (N808)

## What is New808coin?

New808coin (N808) is a decentralized peer-to-peer cryptocurrency focused on energy efficiency and music.

The New808coin network uses a Proof-of-Stake (PoS) consensus system together with masternodes. This allows network participants to help secure and maintain the blockchain without relying on energy-intensive Proof-of-Work mining after the initial PoW phase.

Masternodes provide additional network functionality and participate in the block reward distribution. PoS participants earn rewards by staking eligible N808 coins in their wallets.

At the launch of the New808coin network, coins were premined and allocated for the migration/swap of holders from the previous PoW/PoS 808coin network.

Masternode collateral changed during the earlier phases of the blockchain and has been fixed at **25,000 N808** since Phase 6.

The minimum staking age is **80.8 hours**.

---

# New808coin Core v5.2.6.10

## Mandatory Network Upgrade

**New808coin Core v5.2.6.10 is a mandatory consensus upgrade.**

### Activation Height

The new reward rules activate at:

**Block 1,000,001**

All masternode operators, staking wallets, exchanges, explorers, seed nodes, and other New808coin network services should upgrade before the activation height.

### Protocol Version

New808coin Core v5.2.6.10 uses:

**Protocol Version: 70966**

Older compatible protocol peers are temporarily permitted during the migration period.

A later post-activation release may increase the minimum accepted protocol version after the upgraded blockchain has successfully passed the activation height.

---

# New808coin Specifications

Specification | Value
--- | ---
Coin Name | New808coin
Coin Ticker | N808
Consensus | Masternode / Proof-of-Stake
Current Masternode Collateral | 25,000 N808
Minimum Stake Age | 80.8 hours
Block Spacing | 4 minutes
Difficulty Retargeting | Every 80 minutes
Premine | 2,100,000 N808
Maximum Supply | 21,000,000 N808
RPC Port | 8089
P2P / Masternode Port | 33808
Current Protocol Version | 70966
Mandatory Upgrade Version | v5.2.6.10
Reward Upgrade Activation | Block 1,000,001

---

# Reward Distribution Structure

## Genesis Block

Block Height | Reward Amount
--- | ---
1 | 2,100,000 N808

---

## Initial PoW Phase

Block Height | Reward Amount
--- | ---
2-808 | 808 N808

After the initial PoW phase, New808coin transitioned to its Masternode / Proof-of-Stake reward structure.

---

# Historical Masternode / PoS Reward Phases

Phase | Collateral | Block Height | Total Reward | Masternodes | PoS
--- | ---: | ---: | ---: | ---: | ---:
Phase 1 | 2,500 N808 | 809-42,000 | 42 N808 | 85% (35.70 N808) | 15% (6.30 N808)
Phase 2 | 2,500 N808 | 42,001-100,000 | 40 N808 | 85% (34.00 N808) | 15% (6.00 N808)
Phase 3 | 2,500 N808 | 100,001-130,000 | 33 N808 | 85% (28.05 N808) | 15% (4.95 N808)
Phase 4 | 5,000 N808 | 130,001-140,000 | 4 N808 | 85% (3.40 N808) | 15% (0.60 N808)
Phase 5 | 10,000 N808 | 140,001-155,000 | 8 N808 | 86% (6.88 N808) | 14% (1.12 N808)
Phase 6 | 25,000 N808 | 155,001-400,000 | 16 N808 | 87% (13.92 N808) | 13% (2.08 N808)
Phase 7 | 25,000 N808 | 400,001-500,000 | 32 N808 | 88% (28.16 N808) | 12% (3.84 N808)
Phase 8 | 25,000 N808 | 500,001-525,000 | 64 N808 | 89% (56.96 N808) | 11% (7.04 N808)
Phase 9 | 25,000 N808 | 525,001-550,000 | 16 N808 | 87% (13.92 N808) | 13% (2.08 N808)
Phase 10 | 25,000 N808 | 550,001-575,000 | 8 N808 | 86% (6.88 N808) | 14% (1.12 N808)
Phase 11 | 25,000 N808 | 575,001-600,000 | 4 N808 | 85% (3.40 N808) | 15% (0.60 N808)
Phase 12 | 25,000 N808 | 600,001-1,000,000 | 2 N808 | 85% (1.70 N808) | 15% (0.30 N808)

---

# Reward Schedule From Block 1,000,001

Starting at **block 1,000,001**, New808coin begins a new long-term reward schedule.

The rules are:

- Block 1,000,001 starts with a total reward of **1.00000000 N808**.
- The total reward is divided by **2 every 100,000 blocks**.
- Masternodes receive **85%** of the block reward.
- PoS receives **15%** of the block reward.
- Masternode collateral remains **25,000 N808**.
- The final scheduled reward is **0.00000020 N808 until Max Supply is reached**.
- The maximum supply remains **21,000,000 N808**.
- When the maximum supply is reached, the block subsidy becomes zero.
- Historical 808 N808 superblocks are permanently disabled from block 1,000,001.

## New Reward Examples

Block Height | Total Reward | Masternodes 85% | PoS 15%
--- | ---: | ---: | ---:
1,000,001-1,100,000 | 1.00000000 N808 | 0.85000000 N808 | 0.15000000 N808
1,100,001-1,200,000 | 0.50000000 N808 | 0.42500000 N808 | 0.07500000 N808
1,200,001-1,300,000 | 0.25000000 N808 | 0.21250000 N808 | 0.03750000 N808
1,300,001-1,400,000 | 0.12500000 N808 | 0.10625000 N808 | 0.01875000 N808
1,400,001-1,500,000 | 0.06250000 N808 | 0.05312500 N808 | 0.00937500 N808
1,500,001-1,600,000 | 0.03125000 N808 | 0.02656250 N808 | 0.00468750 N808
1,600,001-1,700,000 | 0.01562500 N808 | 0.01328125 N808 | 0.00234375 N808
1,700,001-1,800,000 | 0.00781250 N808 | 0.00664062 N808* | 0.00117188 N808*
1,800,001-1,900,000 | 0.00390625 N808 | Calculated at 85% | Remaining 15%
1,900,001-2,000,000 | 0.00195312 N808* | Calculated at 85% | Remaining 15%

\* Rewards are calculated using the smallest N808 units available in consensus arithmetic. At very small reward values, displayed decimal percentages may be affected by integer-unit rounding.

The reward continues to halve every **100,000 blocks** according to the same rule.

The scheduled reward will never be reduced below:

**0.00000020 N808**

unless the remaining amount before reaching the **21,000,000 N808 maximum supply** is smaller.

At the scheduled minimum reward:

Reward Type | Amount
--- | ---:
Total Scheduled Reward | 0.00000020 N808
Masternode Reward | 0.00000017 N808
PoS Reward | 0.00000003 N808

Once the total money supply reaches the configured maximum supply, the block subsidy becomes zero.

---

# Reward Activation Boundaries

The mandatory upgrade is designed so that all existing consensus reward rules remain unchanged through block **1,000,000**.

Height | Reward Rule
--- | ---
999,999 | Existing Phase 12 rules
1,000,000 | Existing Phase 12 rules
1,000,001 | New reward system starts at 1 N808
1,100,000 | 1 N808
1,100,001 | 0.5 N808
1,200,000 | 0.5 N808
1,200,001 | 0.25 N808
1,300,001 | 0.125 N808

The same 100,000-block halving schedule continues afterward.

---

# Historical Superblock Algorithm

New808coin historically included an additional **808 N808 superblock reward algorithm**.

This historical superblock system remains part of the blockchain rules only through block:

**1,000,000**

Starting from:

**Block 1,000,001**

the 808 N808 superblock reward is **permanently disabled**.

Period | Superblock Status
--- | ---
Historical blocks through 1,000,000 | Enabled according to the historical consensus algorithm
Block 1,000,001 and above | Permanently disabled

The new reward schedule after block 1,000,000 does not contain any 808 N808 superblock override.

---

# Masternodes

The current masternode collateral requirement is:

**25,000 N808**

The collateral amount is not changed by the v5.2.6.10 mandatory upgrade.

After block 1,000,000, the reward distribution remains:

- **85% Masternode**
- **15% PoS**

Only the total block reward changes according to the new 100,000-block halving schedule.

---

# Maximum Supply

The New808coin maximum supply remains:

**21,000,000 N808**

The v5.2.6.10 reward update does not increase the maximum supply.

The scheduled reward is reduced as necessary when the remaining amount before the maximum supply is smaller than the normal scheduled subsidy.

Once maximum supply is reached, the block subsidy becomes zero.

---

# Mandatory Upgrade Information

New808coin Core **v5.2.6.10** contains consensus changes that become active at block **1,000,001**.

Older versions do not contain the new reward rules.

Network participants should upgrade before activation, especially:

- Masternode operators
- PoS staking wallets
- Exchanges
- Block explorers
- Seed nodes
- Mining/staking pools or services
- Infrastructure providers

Older clients may remain network-compatible at the P2P protocol level during the migration period, but after block 1,000,001 they do not contain the correct new reward consensus rules.

A later post-activation release may introduce an updated checkpoint and increase the minimum accepted protocol version after the upgraded network has stabilized.

---

# Building New808coin

Build and development documentation is available in the [`doc`](doc/) directory.

Common documentation includes:

- Unix/Linux build instructions
- Windows build information
- macOS build information
- Masternode configuration
- Release process
- REST interface
- Tor configuration
- ZMQ
- Unit tests
- Gitian builds

For release-specific information, see:

[`doc/release-notes-5.2.6.10.md`](doc/release-notes-5.2.6.10.md)

---

# Links

- Website: https://new808coin.com
- Discord: https://discord.gg/qvPTgdW
- Explorer: https://explorer.new808coin.com
- Wallet Releases: https://github.com/didarmetu/New808coin/releases
- White Paper: https://new808coin.com/white-paper
- GitHub Source: https://github.com/didarmetu/New808coin
- Bitcointalk: https://bitcointalk.org/index.php?topic=5237615
- Twitter / X: https://twitter.com/new808coin
- Telegram: https://t.me/new808coin
- Reddit: https://www.reddit.com/r/New808coin
- Exchange: https://fiberchange.com
- CoinPaprika: https://coinpaprika.com/coin/n808-new808coin
- CoinGecko: https://www.coingecko.com/en/coins/new808coin
- New808Punks NFTs: https://opensea.io/collection/new808punks

---

# License

New808coin Core is open-source software.

See the repository license file for licensing information.
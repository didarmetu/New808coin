# New808coin Core v5.2.6.10

## Mandatory Update

New808coin Core v5.2.6.10 is a mandatory network upgrade.

### Activation Height

The new consensus reward rules activate at:

**Block 1,000,001**

All masternode operators, staking wallets, exchanges, explorers, and other network services should upgrade to v5.2.6.10 before the activation height.

## Reward Changes

Up to and including block 1,000,000, the existing reward rules remain unchanged.

Starting from block 1,000,001:

- The block reward starts at 1.00000000 N808.
- The block reward is divided by 2 every 100,000 blocks.
- The historical 808 N808 superblock reward is permanently disabled.
- The final scheduled reward is 0.00000020 N808 until Max Supply is reached.
- Maximum supply remains 21,000,000 N808.

### Reward Schedule

| Block Height | Total Reward |
| --- | ---: |
| 1,000,001 - 1,100,000 | 1.00000000 N808 |
| 1,100,001 - 1,200,000 | 0.50000000 N808 |
| 1,200,001 - 1,300,000 | 0.25000000 N808 |
| 1,300,001 - 1,400,000 | 0.12500000 N808 |
| 1,400,001 - 1,500,000 | 0.06250000 N808 |
| Continuing every 100,000 blocks | Reward divided by 2 |

The halving schedule continues until the scheduled reward reaches 0.00000020 N808.

The 21,000,000 N808 maximum supply remains enforced. When Max Supply is reached, block subsidy becomes zero.

## Masternode and PoS Rewards

The reward distribution remains:

- Masternodes: 85%
- PoS: 15%

Example at block 1,000,001:

- Total reward: 1.00000000 N808
- Masternode reward: 0.85000000 N808
- PoS reward: 0.15000000 N808

Masternode collateral remains unchanged at:

**25,000 N808**

## Superblocks

The historical 808 N808 superblock system remains active through block 1,000,000.

Starting from block 1,000,001, 808 N808 superblocks are permanently disabled.

## Network Protocol

Protocol version for this release:

**70966**

Older compatible peers are still permitted during the initial upgrade period.

A later post-activation release may increase the minimum accepted protocol version after the network has successfully transitioned to the new consensus rules.

## Upgrade Requirement

Users running older versions should upgrade before block 1,000,001.

Older software does not contain the new reward consensus rules and may produce or accept blocks that are incompatible with the upgraded network after activation.

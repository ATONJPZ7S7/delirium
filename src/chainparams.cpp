// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019-2019 The Delirium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
// HERE
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,    uint256("0x00000d6b38bdd5f1824491836e9b2ad11e978b890076fd81f8ee483c2f942988"))
    (500,  uint256("0xd3dfc1c0fc66e8ed20f6477da6f83b50f82a948b308be2ccee2a6721f13a9d19"))
    (2000, uint256("0x658c81ddb4a3b27e6be0326e557bb694e69b256aa226da5c5cf064140943f98e"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1569890187, // * UNIX timestamp of last checkpoint block
    3604,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000088f521d4b8473b56e1ec0cac91e061ce41e40aab83af4bd112c421f4958"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1568118910,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x40ec46d730160013256af21124bd77b70fe294be307f3b56b4496fabe36b1505"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1568117910,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x1e;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0xad;
        vAlertPubKey = ParseHex("04ccf3a78f6bf2c015651fcbf147c2412fc52c2ccfb6d6bed85627a73ee9a4a9204dafaca4e4e7fe57e448ccd6d859daafa9b2135e5aeff198dc1d50130d40801b");
        nDefaultPort = 30100;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 122862;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 3 * 60;
        nTargetTimespan = 60 * 40; 
        nLastPOWBlock = 416;
	nStakingMinInput = 2400 * COIN;
        nMaturity = 40;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 700;
	nModifierUpgradeBlock = 1000;
        nMaxMoneyOut = 360000000 * COIN;

        const char* pszTimestamp = "bitcoin investiment is long history";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("044C06F5ABD4514F5BEE6C33DB9EAC8A636068CAC8949771B4726975A4583C4149A8E8E20A09AB5A4E7B60B0FDF2AE507C20C29F42911EB82A50D7B1CD0D374698") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1569520635;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 521061;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000d6b38bdd5f1824491836e9b2ad11e978b890076fd81f8ee483c2f942988"));
        assert(genesis.hashMerkleRoot == uint256("0xf9407e43cd3fa0aed4303b3ce3c0378d50f1f271b9839558ffee25baa42293dd"));


        vSeeds.push_back(CDNSSeedData("sed1", "sed1.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed2", "sed2.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed3", "sed3.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed4", "sed4.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed5", "sed5.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed6", "sed6.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed7", "sed7.delirium.cf"));
        vSeeds.push_back(CDNSSeedData("sed8", "sed8.delirium.cf"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,6);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,158);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0418755EFC2F8A0A576540F0DBE3AF4CF82E30FB2381CD794FB5B63730430167F2FE92972CB5247670C21D89D69F0981241A3EB910A69CAB8BBFA8E4055EFA1B2D";
        strObfuscationPoolDummyAddress = "DUBrYgJMqZsDs2ZFDtZ4PBRWSpiwi3amj7";
        nStartMasternodePayments =  genesis.nTime + 86400; 
   }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04E985EF1EECC3407203D99D4F7F93EE9595931D0D52FF511732BAB37F19D06603E963A087AF92D6ECD59A279E127A8C1FE83B162862C0F5B7A82ECCEC48C67E51");
        nDefaultPort = 31101;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 3 * 60;  
        nTargetTimespan = 60 * 40;
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1568118910;
        genesis.nNonce = 1593433;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000088f521d4b8473b56e1ec0cac91e061ce41e40aab83af4bd112c421f4958"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        fRequireRPCPassword = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04262543C61E916FAB4747C6A10E82B6E2CC5BBDF1C99AA76C2B82BB0A76380C62487B3D04C9FB2C05A75B9B0AC4259827BDF286295F9639FB32ED408DFD237F75";
        strObfuscationPoolDummyAddress = "DHkH12EiHCRUQTxTZvTPA7hKrAFUboTBtd";
        nStartMasternodePayments = genesis.nTime + 86400;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
 class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; 
        nTargetSpacing = 1 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1568117910;
        genesis.nBits = 0x207fffff;
        nDefaultPort = 31102;
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x40ec46d730160013256af21124bd77b70fe294be307f3b56b4496fabe36b1505"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 33103;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
CScript CChainParams::GetScriptForDevFeeDestination() {
    CBitcoinAddress DevFeeRewardAddress("3TJyAjExSn5sNuDKrkhPaAQezRzfKAYfy6");
    assert(DevFeeRewardAddress.IsValid());

    CScript script = GetScriptForDestination(DevFeeRewardAddress.Get());
    return script;
}

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The VronToNode Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include "hashblock.h" 

#include <assert.h>
#include <limits>

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
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000cf226bcb18d6a87eb818e59df2bbaf8c4824ea0b7a933539d4c18dbfdd0"))
                              ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1535812747, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1534859399,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1534859399,
    0,
    100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd7;
        pchMessageStart[1] = 0xdb;
        pchMessageStart[2] = 0xd4;
        pchMessageStart[3] = 0xd8;
        vAlertPubKey = ParseHex("028a7bd46cdeb64e1e9c5e7b3f519c6eddb01ec6273ef8c2a3ef04ca4c35d5aaaa");

        nDefaultPort = 25552;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        bnStartWork = ~uint256(0) >> 24;

        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // VronToNode: 1 minute after 6000
        nTargetSpacingSlowLaunch = 1 * 60; // before block 6000
        nMaturity = 6; 
        nMasternodeCountDrift = 3;
        nMaxMoneyOut = 1000000000 * COIN; 

        nStartMasternodePaymentsBlock = 6;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 230; // 60 * 24 * 30; // 
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();

        // 
        const char* pszTimestamp = "We are champions. Top of the world";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 400 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04492bc3c5e0b545ffd667637273d63819522086720d0b8e799f0c23d7a9bcf9cea1fda9ad180699c8663f2733232ca7c5bee08af5eb0a952669c2fdd3bfcc1752") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1562022000;
        genesis.nBits = 0x1e0ffff0;


        // genesis.nNonce = 4977805;
        // hashGenesisBlock = genesis.GetHash();

        // printf("coin genesis.nTime = %u \n", genesis.nTime);
        // printf("coin genesis.nNonce = %u \n", genesis.nNonce);
        // printf("coin genesis.GetHash = %s\n", hashGenesisBlock.ToString().c_str());
        // printf("coin Gensis Hash Merkle: %s\n\n", genesis.hashMerkleRoot.ToString().c_str());

        // uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        // uint256 thash;
        // while(true)
        // {
        //     //thash = scrypt_blockhash(BEGIN(genesis.nVersion));
        //     //thash = Hash9(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     thash = HashKeccak256(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     if (thash <= hashTarget)
        //         break;
        //     if ((genesis.nNonce & 0xFFF) == 0)
        //     {
        //         printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //     }
        //     ++genesis.nNonce;
        //     if (genesis.nNonce == 0)
        //     {
        //         printf("NONCE WRAPPED, incrementing time\n");
        //         ++genesis.nTime;
        //     }
        // }
        // printf("New genesis.nTime = %u \n", genesis.nTime);
        // printf("New genesis.nNonce = %u \n", genesis.nNonce);
        // printf("New genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        // printf("New gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        // //assert(false); 

        // assert(hashGenesisBlock == uint256("0x000001ce3890b225f0d3edb1112374aaf58e1966d589ae60a94dfa999ef87b8f"));
        // assert(genesis.hashMerkleRoot == uint256("0xd6c2ca3308f5816974969959f57fcd7111abfe3b805b8e529c68c9065aeb4fa6"));



        // genesis.nNonce = 5816876;
        // hashGenesisBlock = genesis.GetHash();

        // printf("coin genesis.nTime = %u \n", genesis.nTime);
        // printf("coin genesis.nNonce = %u \n", genesis.nNonce);
        // printf("coin genesis.GetHash = %s\n", hashGenesisBlock.ToString().c_str());
        // printf("coin Gensis Hash Merkle: %s\n\n", genesis.hashMerkleRoot.ToString().c_str());

        // uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        // uint256 thash;
        // while(true)
        // {
        //     //thash = scrypt_blockhash(BEGIN(genesis.nVersion));
        //     thash = Hash9(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     //thash = HashKeccak256(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     if (thash <= hashTarget)
        //         break;
        //     if ((genesis.nNonce & 0xFFF) == 0)
        //     {
        //         printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //     }
        //     ++genesis.nNonce;
        //     if (genesis.nNonce == 0)
        //     {
        //         printf("NONCE WRAPPED, incrementing time\n");
        //         ++genesis.nTime;
        //     }
        // }
        // printf("New genesis.nTime = %u \n", genesis.nTime);
        // printf("New genesis.nNonce = %u \n", genesis.nNonce);
        // printf("New genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        // printf("New gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        // //assert(false); 

        // assert(hashGenesisBlock == uint256("0x00000c6fba2e0ca2817ee18013204df3dd484df94a941f6d029e790c51101cf8"));
        // assert(genesis.hashMerkleRoot == uint256("0xd6c2ca3308f5816974969959f57fcd7111abfe3b805b8e529c68c9065aeb4fa6"));




        // genesis.nNonce = 931712;
        // hashGenesisBlock = genesis.GetHash();

        // printf("coin genesis.nTime = %u \n", genesis.nTime);
        // printf("coin genesis.nNonce = %u \n", genesis.nNonce);
        // printf("coin genesis.GetHash = %s\n", hashGenesisBlock.ToString().c_str());
        // printf("coin Gensis Hash Merkle: %s\n\n", genesis.hashMerkleRoot.ToString().c_str());

        // uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        // uint256 thash;
        // while(true)
        // {
        //     //thash = scrypt_blockhash(BEGIN(genesis.nVersion));
        //     //thash = Hash9(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     //thash = HashKeccak256(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     thash = HashQuark(BEGIN(genesis.nVersion), END(genesis.nNonce));
        //     if (thash <= hashTarget)
        //         break;
        //     if ((genesis.nNonce & 0xFFF) == 0)
        //     {
        //         printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //     }
        //     ++genesis.nNonce;
        //     if (genesis.nNonce == 0)
        //     {
        //         printf("NONCE WRAPPED, incrementing time\n");
        //         ++genesis.nTime;
        //     }
        // }
        // printf("New genesis.nTime = %u \n", genesis.nTime);
        // printf("New genesis.nNonce = %u \n", genesis.nNonce);
        // printf("New genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        // printf("New gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        // //assert(false); 

        // assert(hashGenesisBlock == uint256("00000d8c75c129604bada659b0ac20e49fe1f9bbe94ed6f5460d40dc53660aef"));
        // assert(genesis.hashMerkleRoot == uint256("d6c2ca3308f5816974969959f57fcd7111abfe3b805b8e529c68c9065aeb4fa6"));


        genesis.nNonce = 2317638;
        hashGenesisBlock = genesis.GetHash();

        printf("coin genesis.nTime = %u \n", genesis.nTime);
        printf("coin genesis.nNonce = %u \n", genesis.nNonce);
        printf("coin genesis.GetHash = %s\n", hashGenesisBlock.ToString().c_str());
        printf("coin Gensis Hash Merkle: %s\n\n", genesis.hashMerkleRoot.ToString().c_str());

        uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        uint256 thash;
        while(true)
        {
            //thash = scrypt_blockhash(BEGIN(genesis.nVersion));
            //thash = Hash9(BEGIN(genesis.nVersion), END(genesis.nNonce));
            //thash = HashKeccak256(BEGIN(genesis.nVersion), END(genesis.nNonce));
            thash = HashQuark(BEGIN(genesis.nVersion), END(genesis.nNonce));
            if (thash <= hashTarget)
                break;
            if ((genesis.nNonce & 0xFFF) == 0)
            {
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
            }
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time\n");
                ++genesis.nTime;
            }
        }
        printf("New genesis.nTime = %u \n", genesis.nTime);
        printf("New genesis.nNonce = %u \n", genesis.nNonce);
        printf("New genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        printf("New gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //assert(false); 

        assert(hashGenesisBlock == uint256("00000cf226bcb18d6a87eb818e59df2bbaf8c4824ea0b7a933539d4c18dbfdd0"));
        assert(genesis.hashMerkleRoot == uint256("d6c2ca3308f5816974969959f57fcd7111abfe3b805b8e529c68c9065aeb4fa6"));        











        // vSeeds.push_back(CDNSSeedData("3.112.191.34", "3.112.191.34")); 
        // vSeeds.push_back(CDNSSeedData("13.230.239.62", "13.230.239.62")); 
        // vSeeds.push_back(CDNSSeedData("54.95.166.245", "54.95.166.245")); 
        // vSeeds.push_back(CDNSSeedData("3.113.1.180", "3.113.1.180")); 
        // vSeeds.push_back(CDNSSeedData("52.194.229.210", "52.194.229.210"));     
        // vSeeds.push_back(CDNSSeedData("13.114.140.187", "13.114.140.187"));     
        // vSeeds.push_back(CDNSSeedData("176.34.37.85", "176.34.37.85"));     
        // vSeeds.push_back(CDNSSeedData("3.112.203.169", "3.112.203.169"));     // error
        // vSeeds.push_back(CDNSSeedData("3.112.131.131", "3.112.131.131"));     
        // vSeeds.push_back(CDNSSeedData("3.112.18.143", "3.112.18.143"));     
        // vSeeds.push_back(CDNSSeedData("3.112.234.72", "3.112.234.72"));

        // 
        vSeeds.push_back(CDNSSeedData("block0.vrontonode.org", "block0.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block1.vrontonode.org", "block1.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block2.vrontonode.org", "block2.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block3.vrontonode.org", "block3.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block4.vrontonode.org", "block4.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block5.vrontonode.org", "block5.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block6.vrontonode.org", "block6.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block7.vrontonode.org", "block7.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block8.vrontonode.org", "block8.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block9.vrontonode.org", "block9.vrontonode.org")); 
        vSeeds.push_back(CDNSSeedData("block10.vrontonode.org", "block10.vrontonode.org"));         

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 132); // 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 64); // S or T
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 55); // P
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 9984
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x27)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "033f069a906552224554c6613bf9897b8083f7194ae1058617c7ae1c6aee69aaaa"; //strSporkKey = "033f069a906552224554c6613bf9897b8083f7194ae1058617c7ae1c6aee69509d";
        strObfuscationPoolDummyAddress = "vNwcD7GzThmbtNXbGSGgWPrdXLuJAnEyXM";
        nStartMasternodePayments = 1561885711; //after 1 day and 17h of genesis

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
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x77;
        pchMessageStart[2] = 0x66;
        pchMessageStart[3] = 0xbb;

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = bnProofOfWorkLimit;

        vAlertPubKey = ParseHex("04459DC949A9E2C2E1FA87ED9EE93F8D26CD52F95853EE24BCD4B07D4B7D79458E81F0425D81E52B797ED304A836667A1D2D422CD10F485B06CCBE906E1081FBAC");
        nDefaultPort = 11945;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // VronToNode: 1 minute
        nLastPOWBlock = std::numeric_limits<decltype(nLastPOWBlock)>::max();
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();
        nMaxMoneyOut = 1000000000 * COIN;


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1534859399;
        genesis.nNonce = 290796;

        hashGenesisBlock = genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("vrontonode.org", "seed01.vrontonode.org"));     // Primary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 137); // Testnet VronToNode addresses start with 'x'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet VronToNode script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet VronToNode BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet VronToNode BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet VronToNode BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0421838CC1407E7B8C0C5F2379DF7EBD395181949CFA55124939B4980D5054A7926F88E3059921A50F0F81C5195E882D9A414EA0835BB89C9BB061511B9F132B31";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1534859399; //Fri, 09 Jan 2015 21:05:58 GMT
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

        bnStartWork = ~uint256(0) >> 20;

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetSpacing = 1 * 60;        // VronToNode: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1534859399;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;

        //assert(hashGenesisBlock == uint256("300552a9db8b2921c3c07e5bbf8694df5099db579742e243daeaf5008b1e74de"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
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
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;


    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
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

#include "main.h"

double calculate_total_reward(int blocks_mined) {
    return MINING_REWARD*blocks_mined;
}

bool is_valid_tx_fee(double fee) {
    // TODO: return true if fee is between 0.00001 and 0.01 BTC (inclusive bounds up to you)
    return fee>0.00001 && fee <0.01;
}

bool is_large_balance(double balance) {
    // TODO: return true if balance > 50.0 BTC
    return balance>50;
}

std::string tx_priority(int size_bytes, double fee_btc) {
    // TODO: compute fee rate (fee_btc / size_bytes) and return "high" / "medium" / "low"
    //       high   >= 0.00005
    //       medium >= 0.00001
    //       otherwise low
    double rate = fee_btc/size_bytes;
    if(rate >=0.00005)
      return "high";
    if(rate>=0.00001)
      return "medium";
    return "low";
}

void lowerstr(std::string& str)
{
    for(auto& c : str)
        c = std::tolower(c);
}

bool is_mainnet(std::string network) {
    // TODO: lowercase `network` and return true iff it equals "mainnet"
    lowerstr(network);
    return network=="mainnet";
}

bool is_in_range(double value) {
    // TODO: return true iff 100 <= value <= 200
    return value>=100 && value <=200;
}

bool is_same_wallet(const Wallet& w1, const Wallet& w2) {
    // TODO: return true iff both refs name the same object in memory (compare addresses)
    return &w1 == &w2;
}

std::string normalize_address(std::string address) {
    // TODO: strip leading/trailing whitespace and lowercase the address
    while(address[0]==' ')
      address = address.substr(1);
    while(address[address.size()-1]==' ')
      address = address.substr(0, address.size()-1);
    lowerstr(address);
    return address;
}

std::vector<int> add_utxo(std::vector<int> utxos, int new_utxo) {
    // TODO: append new_utxo to utxos and return the updated vector
    utxos.push_back(new_utxo);
    return utxos;
}

std::optional<std::pair<std::size_t, double>> find_high_fee(const std::vector<double>& fees) {
    // TODO: return (index, fee) of the first fee > 0.005, or std::nullopt if none
    for(int i=0;i<fees.size(); ++i)
    {
        if(fees[i]>0.005)
          return std::pair<std::size_t, double>{i, fees[i]};
    }
    return std::nullopt;
}

std::tuple<std::string, double> get_wallet_details() {
    // TODO: return a tuple of (wallet_name, balance)
    return {"satoshi_wallet", 50.0};
}

std::string get_tx_status(const std::map<std::string, std::string>& tx_pool, const std::string& txid) {
    // TODO: return tx_pool[txid] if present, else "not found"
    auto it = tx_pool.find(txid);
    if(it != tx_pool.end())
      return it->second;
    return "not found";
}

std::string unpack_wallet_info(const std::tuple<std::string, double>& wallet_info) {
    // TODO: destructure into (name, balance) and return "Wallet <name> has balance: <balance> BTC"
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << std::get<1>(wallet_info);
    std::string balance_str= oss.str();  // "3.14"

    std::string str = "Wallet "+std::get<0>(wallet_info)+" has balance: "+balance_str+" BTC";
    return str;
}

long long calculate_sats(double btc) {
    return (long long)(btc*BTC_TO_SATS);
}

std::string generate_address(const std::string& prefix) {
    // TODO: append (32 - prefix.size()) random chars from [a-z0-9] to `prefix` and return it
    std::string addr(prefix);
    for(int i=0;i<(32-prefix.size());++i)
      addr.push_back('a'+rand()%26);
    return addr;
}

std::pair<bool, std::string> validate_block_height(int height) {
    // TODO: reject if negative; reject if > 800000; otherwise valid
    if(height<0)
      return {false, "Block height cannot be negative"};
    if(height>800000)
      return {false, "Block height seems unrealistic"};
    else
      return {true, "Valid block height"};
}

std::pair<bool, std::string> validate_block_height(double height) {
    // TODO: a non-integer block height should always be rejected
    if(height != floor(height))
      return {false, "Block height must be an integer"};
    return validate_block_height(int(height));
}

std::pair<bool, std::string> validate_block_height(const std::string& height) {
    // TODO: a string block height should always be rejected
    return {false, "Block height must be an integer"};
}

std::map<int, long long> halving_schedule(const std::vector<int>& blocks) {
    // TODO: base reward = 50 * BTC_TO_SATS sats, halve every 210_000 blocks
    //       return a map of {block_height: reward_in_sats}
    std::map<int, long long> out, out2;
    long long sats = 50*BTC_TO_SATS;
    int height = 0;
    while (sats>0)
    {
        out[height] = sats;

        height += 210000;
        sats = sats/2;
    }

    for (const auto block : blocks)
    {
        auto it = out.lower_bound(block);
        if(it->first>block)
          --it;
        out2[block] = it->second;
    }
    return out2;
}

std::optional<Utxo> find_utxo_with_min_value(const std::vector<Utxo>& utxos, long long target) {
    const Utxo* sel = nullptr;
    for (const Utxo& utxo : utxos)
    {
        if(utxo.value>=target)
        {
            if(sel ==nullptr)
                sel = &utxo;
            else if (sel->value > utxo.value)
                sel = &utxo;
        }
    }
    if(sel != nullptr)
        return *sel;
    // TODO: among utxos with value >= target, return the one with the smallest value
    //       (std::nullopt if none qualifies)
    return std::nullopt;
}

std::map<std::string, UtxoField> create_utxo(
    const std::string& txid,
    int vout,
    const std::map<std::string, UtxoField>& extras
) {
    // TODO: build a map with {"txid": txid, "vout": vout} merged with `extras`
    return {};
}

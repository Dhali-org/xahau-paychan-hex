#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>

#include <ripple/basics/IOUAmount.h>

#include <ripple/protocol/AccountID.h>
#include <ripple/protocol/Serializer.h>
#include <ripple/protocol/UintTypes.h>
#include <ripple/protocol/STAmount.h>
#include <ripple/protocol/tokens.h>
#include <ripple/protocol/PayChan.h>


int main()
{
    using namespace ripple;

    Serializer msg;
    uint256 channelKey = uint256("C373E17947B78F44537C9C5E6EF71914CEDEC3BEA356CA08F1C186E2BDA05B93");

    IOUAmount amt(1, 0);

    Currency cur;
    std::string currency_string = "DHA";
    to_currency(cur, currency_string);
    
    TokenType type = TokenType::AccountID;
    std::string issuer = "rDyz9rX7eGJRdVDC8NGxMxqh9U14qduqzS";
    std::optional<AccountID> iss = parseBase58<AccountID>(issuer);

    serializePayChanAuthorization(msg, channelKey, amt, cur, iss.value());

    std::cout << "Hex to be signed:\n";
    std::cout << msg.slice() << "\n";

    return 0;
}

const myAddon = require('.');
const result = myAddon.serializePayChanAuthorization(
    "rDyz9rX7eGJRdVDC8NGxMxqh9U14qduqzS", 
    "C373E17947B78F44537C9C5E6EF71914CEDEC3BEA356CA08F1C186E2BDA05B93", 
    "DHA", 
    1.0
);

console.log("PayChan Hex to be Signed:", result);

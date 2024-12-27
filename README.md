# Xahau Payment Channel Hex Generator

![NPM Version](https://img.shields.io/npm/v/xahau-paychan-hex)

The Xahau Payment Channel Hex Generator is an npm package designed to generate hex strings that can be signed by Xahau wallets when spending issued currencies through payment channels.

## Installation

To install the Xahau Payment Channel Hex Generator, use npm:

```bash
npm install xahau-paychan-hex
```

## Usage

After installation, you can use this package to generate the hex strings needed for signing by Xahau wallets.

Example usage:

```javascript
const generateHex = require('xahau-paychan-hex');
const result = generateHex.serializePayChanAuthorization(
    "rDyz9rX7eGJRdVDC8NGxMxqh9U14qduqzS", 
    "C373E17947B78F44537C9C5E6EF71914CEDEC3BEA356CA08F1C186E2BDA05B93", 
    "DHA", 
    1.0
);

console.log("PayChan Hex to be Signed:", result);
```

## Build Instructions

If you prefer (you might need to, because the pre-built binaries in the package may not work for your system) you can build the package from [source](https://github.com/Dhali-org/xahau-paychan-hex) by using the `Dockerfile`

## Example

To run the example, execute the following command:

```bash
node example.js
```

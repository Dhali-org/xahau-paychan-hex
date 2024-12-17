const path = require('path');
const addon = require(path.resolve(__dirname, 'build/addon.node'));

module.exports = {
    serializePayChanAuthorization: addon.serializePayChanAuthorization,
};

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <optional>
#include "PayChan.hpp"

namespace py = pybind11;

std::string serializePayChanAuthorization(const std::string& issuer, 
                                           const std::string& channelId, 
                                           const std::string& currencyCode, 
                                           double amount) {
    try {
        ripple::Serializer msg;
        ripple::uint256 channelKey = ripple::uint256(channelId.c_str());
        ripple::IOUAmount amt(amount, 0);

        ripple::Currency cur;
        to_currency(cur, currencyCode);

        std::optional<ripple::AccountID> issuerAccount = ripple::parseBase58<ripple::AccountID>(issuer);
        if (!issuerAccount) {
            throw std::invalid_argument("Invalid issuer address");
        }

        ripple::serializePayChanAuthorization(msg, channelKey, amt, cur, issuerAccount.value());

        return strHex(msg.slice());

    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

PYBIND11_MODULE(paychan_python, m) {
    m.doc() = "Python binding for PayChan authorization serialization"; // Optional module docstring
    m.def("serialize_paychan_authorization", &serializePayChanAuthorization, 
          py::arg("issuer"), py::arg("channelId"), py::arg("currencyCode"), py::arg("amount"),
          "Serializes PayChan authorization using issuer, channelId, currencyCode, and amount");
}

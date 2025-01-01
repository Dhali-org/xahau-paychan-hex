#include <napi.h>
#include <iostream>
#include <optional>
#include "PayChan.hpp"

// Wrapper function
Napi::String SerializePayChanAuthorization(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 4 || 
        !info[0].IsString() || !info[1].IsString() || 
        !info[2].IsString() || !info[3].IsNumber()) {
        Napi::TypeError::New(env, "Expected (issuer, channelId, currencyCode, amount)").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    std::string issuer = info[0].As<Napi::String>();
    std::string channelId = info[1].As<Napi::String>();
    std::string currencyCode = info[2].As<Napi::String>();
    double amount = info[3].As<Napi::Number>();

    try {
        ripple::Serializer msg;
        ripple::uint256 channelKey = ripple::uint256(channelId.c_str());
        ripple::IOUAmount amt(amount, 0);

        ripple::Currency cur;
        to_currency(cur, currencyCode);

        std::optional<ripple::AccountID> issuerAccount = ripple::parseBase58<ripple::AccountID>(issuer);
        if (!issuerAccount) {
            Napi::Error::New(env, "Invalid issuer address").ThrowAsJavaScriptException();
            return Napi::String::New(env, "");
        }

        ripple::serializePayChanAuthorization(msg, channelKey, amt, cur, issuerAccount.value());

        return Napi::String::New(env, strHex(msg.slice()));

    } catch (const std::exception& e) {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "serializePayChanAuthorization"),
                Napi::Function::New(env, SerializePayChanAuthorization));
    return exports;
}

NODE_API_MODULE(addon, Init)

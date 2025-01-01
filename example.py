import paychan_python

issuer = "rDyz9rX7eGJRdVDC8NGxMxqh9U14qduqzS"
channel_id = "C373E17947B78F44537C9C5E6EF71914CEDEC3BEA356CA08F1C186E2BDA05B93"
currency_code = "DHA"

# The following gives a value of 1.2
mantissa = 12
exponent = -1

serialized_data = paychan_python.serialize_paychan_authorization(
    issuer, channel_id, currency_code, mantissa, exponent
)

print("PayChan Hex to be Signed:", serialized_data);

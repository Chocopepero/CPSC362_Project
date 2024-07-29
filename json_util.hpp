#pragma once

#include <string>

#include "contactinfo.hpp"
#include "date.hpp"
#include "reservation.hpp"
#include "server_utils/rapidjson/document.h"     // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h" // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h" // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

class Date;
class Reservation;
class ContactInfo;

void SerializeContactToJSON(const ContactInfo &contact,
                            rapidjson::Writer<rapidjson::StringBuffer> *writer);
void SerializeDateToJSON(const Date &date,
                         rapidjson::Writer<rapidjson::StringBuffer> *writer);
void SerializeVectorOfPairsToJSON(
    const std::vector<std::pair<std::string, int>> &vec,
    rapidjson::Writer<rapidjson::StringBuffer> *writer);
void SerializeReservationRecordToJSON(
    const Reservation &reservation,
    rapidjson::Writer<rapidjson::StringBuffer> *writer);
std::vector<std::pair<std::string, int>>
DeserializeVectorOfPairsFromJSON(const rapidjson::Value &json);
Date DeserializeDateFromJSON(const rapidjson::Value &json);
ContactInfo DeserializeContactFromJSON(const rapidjson::Value &json);
Reservation DeserializeReservationFromJSON(const rapidjson::Value &json);

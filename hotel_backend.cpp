#include "hotel_backend.hpp"

#include <filesystem>
#include <fstream>

#include "server_utils/rapidjson/document.h"     // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h" // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h" // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

void SerializeContactToJSON(
    const ContactInfo &contact,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->Key("_name");
  writer->String(contact.getName().c_str());

  writer->Key("_phone_number");
  writer->String(contact.getPhoneNumber().c_str());

  writer->Key("_address");
  writer->String(contact.getAddress().address_As_String().c_str());

  writer->EndObject();
}

void SerializeVectorOfPairsToJSON(
    const std::vector<std::pair<std::string,int>> vec,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartArray();
  for (const auto& pair: vec){
    writer->StartObject();

    writer->Key("Type");
    writer->String(pair.first.c_str());

    writer->Key("Num");
    writer->Int(pair.second);

    writer->EndObject();
  }
  writer->EndArray();
}

void SerializeReservationRecordToJSON(
    const Reservation &reservation,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->Key("_reservation_id");
  writer->Int(reservation.get_Reservation_Id());

  writer->Key("_primary_guest");
  SerializeContactToJSON(reservation.get_Primary_Guest(), writer);

  writer->Key("_num_of_adults");
  writer->Int(reservation.get_Num_of_Adults());

  writer->Key("_num_of_children");
  writer->Int(reservation.get_Num_of_Children());

  writer->Key("_num_of_rooms");
  writer->Int(reservation.get_Num_of_Rooms());

  writer->Key("_bed_types");
  SerializeVectorOfPairsToJSON(reservation.get_Bed_Types(), writer);

  writer->Key("_fulfillment_status");
  writer->Bool(reservation.get_Fulfillment_Status());
  writer->EndObject();
}

// Reservation DeserializeReservationFromJSON(
//     const rapidjson::Value &json_obj){
//   Reservation reservation{json_obj[]}
// }

bool HotelBackend::WriteRecordsToJSONFile() const {
  std::ofstream records_file{_reservation_records_filepath};
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartObject();
  for(auto reservation: _reservation_record){
    SerializeReservationRecordToJSON(reservation.second, &writer);
  }
  writer.EndObject();

  records_file << ss.GetString();

  records_file.flush();
  records_file.close();
  return true;
}

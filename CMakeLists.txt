cmake_minimum_required(VERSION 3.17)
project(ElectricStripIoT)

set(CMAKE_CXX_STANDARD 14)

include_directories(.pio/libdeps/esp32dev/ArduinoJson)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonConfigFile)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonFilterExample)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonGeneratorExample)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonHttpClient)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonParserExample)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonServer)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/JsonUdpBeacon)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/MsgPackParser)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/ProgmemExample)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/examples/StringExample)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Collection)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Document)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Memory)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Misc)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/MsgPack)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/mpl)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/StringStorage)
include_directories(.pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant)
include_directories(.pio/libdeps/esp32dev/AsyncTCP/src)
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/examples")
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/examples/CaptivePortal")
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/examples/ESP_AsyncFSBrowser")
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/examples/regex_patterns")
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/examples/simple_server")
include_directories(".pio/libdeps/esp32dev/ESP Async WebServer/src")
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/examples)
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer)
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Client)
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Server)
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/examples/SyncClient)
include_directories(.pio/libdeps/esp32dev/ESPAsyncTCP/src)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_bulk_data_insert)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_console)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_insert_long_blob)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_sdmmc)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_sdspi)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_spiffs)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_stackoverflow_users)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_web_console)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_webquery)
include_directories(.pio/libdeps/esp32dev/Sqlite3Esp32/src)
include_directories(src)
include_directories(src/configs)
include_directories(src/http)
include_directories(src/http/countdown)
include_directories(src/http/dayOfWeek)
include_directories(src/http/stopAndGo)
include_directories(src/modes/countdown)
include_directories(src/modes/dayOfWeek)
include_directories(src/network)
include_directories(src/sqlite)

add_executable(ElectricStripIoT
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonConfigFile/JsonConfigFile.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonFilterExample/JsonFilterExample.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonGeneratorExample/JsonGeneratorExample.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonHttpClient/JsonHttpClient.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonParserExample/JsonParserExample.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonServer/JsonServer.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/JsonUdpBeacon/JsonUdpBeacon.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/MsgPackParser/MsgPackParser.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/ProgmemExample/ProgmemExample.ino
        .pio/libdeps/esp32dev/ArduinoJson/examples/StringExample/StringExample.ino
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ArrayFunctions.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ArrayImpl.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ArrayIterator.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ArrayRef.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ArrayShortcuts.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/ElementProxy.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Array/Utilities.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Collection/CollectionData.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Collection/CollectionImpl.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/ArduinoStreamReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/ArduinoStringReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/FlashReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/IteratorReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/RamReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/StdStreamReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Readers/VariantReader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/DeserializationError.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/deserialize.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Filter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/NestingLimit.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Deserialization/Reader.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Document/BasicJsonDocument.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Document/DynamicJsonDocument.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Document/JsonDocument.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Document/StaticJsonDocument.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/EscapeSequence.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/JsonDeserializer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/JsonSerializer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/Latch.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/PrettyJsonSerializer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/TextFormatter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/Utf16.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Json/Utf8.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Memory/Alignment.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Memory/MemoryPool.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Misc/SerializedValue.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Misc/Visitable.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/MsgPack/endianess.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/MsgPack/ieee754.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/MsgPack/MsgPackDeserializer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/MsgPack/MsgPackSerializer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/arithmeticCompare.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/convertNumber.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/Float.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/FloatParts.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/FloatTraits.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/Integer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Numbers/parseNumber.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/MemberProxy.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/ObjectFunctions.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/ObjectImpl.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/ObjectIterator.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/ObjectRef.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/ObjectShortcuts.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Object/Pair.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/mpl/max.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/conditional.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/declval.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/enable_if.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/integral_constant.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_array.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_base_of.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_class.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_const.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_convertible.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_enum.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_floating_point.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_integral.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_pointer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_same.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_signed.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/is_unsigned.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/make_unsigned.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/remove_const.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/remove_reference.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits/type_identity.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/alias_cast.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/assert.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/attributes.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/ctype.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/integer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/limits.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/math.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/pgmspace.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/pgmspace_generic.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/preprocessor.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/safe_strcmp.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/static_array.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/type_traits.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Polyfills/utility.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/ArduinoStringWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/DummyWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/PrintWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/StaticStringWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/StdStreamWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writers/StdStringWriter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/CountingDecorator.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/measure.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/serialize.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Serialization/Writer.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/ArduinoStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/ConstRamStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/FlashStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/FlashStringIterator.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/IsString.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/IsWriteableString.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/RamStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/SizedFlashStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/SizedRamStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/StdStringAdapter.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/StoragePolicy.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/String.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Strings/StringAdapters.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/StringStorage/StringCopier.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/StringStorage/StringMover.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/StringStorage/StringStorage.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/SlotFunctions.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantAs.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantAsImpl.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantCompare.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantContent.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantData.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantFunctions.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantImpl.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantOperators.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantRef.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantShortcuts.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantSlot.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantTag.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Variant/VariantTo.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/compatibility.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Configuration.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/Namespace.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson/version.hpp
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson.h
        .pio/libdeps/esp32dev/ArduinoJson/src/ArduinoJson.hpp
        .pio/libdeps/esp32dev/ArduinoJson/ArduinoJson.h
        .pio/libdeps/esp32dev/AsyncTCP/src/AsyncTCP.cpp
        .pio/libdeps/esp32dev/AsyncTCP/src/AsyncTCP.h
        ".pio/libdeps/esp32dev/ESP Async WebServer/examples/CaptivePortal/CaptivePortal.ino"
        ".pio/libdeps/esp32dev/ESP Async WebServer/examples/ESP_AsyncFSBrowser/ESP_AsyncFSBrowser.ino"
        ".pio/libdeps/esp32dev/ESP Async WebServer/examples/regex_patterns/regex_patterns.ino"
        ".pio/libdeps/esp32dev/ESP Async WebServer/examples/simple_server/simple_server.ino"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncEventSource.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncEventSource.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncJson.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncWebSocket.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncWebSocket.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/AsyncWebSynchronization.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/ESPAsyncWebServer.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/SPIFFSEditor.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/SPIFFSEditor.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/StringArray.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebAuthentication.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebAuthentication.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebHandlerImpl.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebHandlers.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebRequest.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebResponseImpl.h"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebResponses.cpp"
        ".pio/libdeps/esp32dev/ESP Async WebServer/src/WebServer.cpp"
        .pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Client/Client.ino
        .pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Client/config.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Server/config.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/examples/ClientServer/Server/Server.ino
        .pio/libdeps/esp32dev/ESPAsyncTCP/examples/SyncClient/SyncClient.ino
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/async_config.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/AsyncPrinter.cpp
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/AsyncPrinter.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/DebugPrintMacros.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/ESPAsyncTCP.cpp
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/ESPAsyncTCP.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/ESPAsyncTCPbuffer.cpp
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/ESPAsyncTCPbuffer.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/SyncClient.cpp
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/SyncClient.h
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/tcp_axtls.c
        .pio/libdeps/esp32dev/ESPAsyncTCP/src/tcp_axtls.h
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_bulk_data_insert/sqlite3_bulk_data_insert.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_console/sqlite3_console.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_insert_long_blob/sqlite3_insert_long_blob.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_sdmmc/sqlite3_sdmmc.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_sdspi/sqlite3_sdspi.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_spiffs/sqlite3_spiffs.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_stackoverflow_users/sqlite3_stackoverflow_users.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_web_console/sqlite3_web_console.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/examples/sqlite3_webquery/sqlite3_webquery.ino
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/config_ext.h
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/esp32.cpp
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/shox96_0_2.cpp
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/shox96_0_2.h
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/sqlite3.c
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/sqlite3.h
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/unishox1.c
        .pio/libdeps/esp32dev/Sqlite3Esp32/src/unishox1.h
        src/configs/global.cpp
        src/configs/global.h
        src/configs/network.h
        src/configs/pins.h
        src/http/countdown/http.cpp
        src/http/countdown/http.h
        src/http/dayOfWeek/http.cpp
        src/http/dayOfWeek/http.h
        src/http/stopAndGo/http.cpp
        src/http/stopAndGo/http.h
        src/http/functions.cpp
        src/http/functions.h
        src/modes/countdown/countdown.cpp
        src/modes/countdown/countdown.h
        src/modes/dayOfWeek/dayOfWeek.cpp
        src/modes/dayOfWeek/dayOfWeek.h
        src/network/network.cpp
        src/network/network.h
        src/sqlite/sqlite.cpp
        src/sqlite/sqlite.h
        src/functions.cpp
        src/functions.h
        src/main.cpp)

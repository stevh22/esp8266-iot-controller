/*
const size_t capacity = JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(16) + JSON_ARRAY_SIZE(30) + 4*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 7*JSON_OBJECT_SIZE(6) + 1480;
DynamicJsonDocument doc(capacity);

const char* json = "[{\"name\":\"power\",\"label\":\"Power\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"brightness\",\"label\":\"Brightness\",\"type\":\"Number\",\"value\":255,\"min\":1,\"max\":255},{\"name\":\"pattern\",\"label\":\"Pattern\",\"type\":\"Select\",\"value\":1,\"options\":[\"Pride\",\"Color Waves\",\"Rainbow Twinkles\",\"Snow Twinkles\",\"Cloud Twinkles\",\"Incandescent Twinkles\",\"Retro C9 Twinkles\",\"Red & White Twinkles\",\"Blue & White Twinkles\",\"Red, Green & White Twinkles\",\"Fairy Light Twinkles\",\"Snow 2 Twinkles\",\"Holly Twinkles\",\"Ice Twinkles\",\"Party Twinkles\",\"Forest Twinkles\",\"Lava Twinkles\",\"Fire Twinkles\",\"Cloud 2 Twinkles\",\"Ocean Twinkles\",\"Rainbow\",\"Rainbow With Glitter\",\"Solid Rainbow\",\"Confetti\",\"Sinelon\",\"Beat\",\"Juggle\",\"Fire\",\"Water\",\"Solid Color\"]},{\"name\":\"palette\",\"label\":\"Palette\",\"type\":\"Select\",\"value\":7,\"options\":[\"Rainbow\",\"Rainbow Stripe\",\"Cloud\",\"Lava\",\"Ocean\",\"Forest\",\"Party\",\"Heat\"]},{\"name\":\"speed\",\"label\":\"Speed\",\"type\":\"Number\",\"value\":30,\"min\":1,\"max\":255},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Section\"},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"autoplayDuration\",\"label\":\"Autoplay Duration\",\"type\":\"Number\",\"value\":255,\"min\":0,\"max\":255},{\"name\":\"solidColor\",\"label\":\"Solid Color\",\"type\":\"Section\"},{\"name\":\"solidColor\",\"label\":\"Color\",\"type\":\"Color\",\"value\":\"255,255,255\"},{\"name\":\"fire\",\"label\":\"Fire & Water\",\"type\":\"Section\"},{\"name\":\"cooling\",\"label\":\"Cooling\",\"type\":\"Number\",\"value\":49,\"min\":0,\"max\":255},{\"name\":\"sparking\",\"label\":\"Sparking\",\"type\":\"Number\",\"value\":60,\"min\":0,\"max\":255},{\"name\":\"twinkles\",\"label\":\"Twinkles\",\"type\":\"Section\"},{\"name\":\"twinkleSpeed\",\"label\":\"Twinkle Speed\",\"type\":\"Number\",\"value\":4,\"min\":0,\"max\":8},{\"name\":\"twinkleDensity\",\"label\":\"Twinkle Density\",\"type\":\"Number\",\"value\":5,\"min\":0,\"max\":8}]";

deserializeJson(doc, json);

JsonObject root_0 = doc[0];
const char* root_0_name = root_0["name"]; // "power"
const char* root_0_label = root_0["label"]; // "Power"
const char* root_0_type = root_0["type"]; // "Boolean"
int root_0_value = root_0["value"]; // 255

JsonObject root_1 = doc[1];
const char* root_1_name = root_1["name"]; // "brightness"
const char* root_1_label = root_1["label"]; // "Brightness"
const char* root_1_type = root_1["type"]; // "Number"
int root_1_value = root_1["value"]; // 255
int root_1_min = root_1["min"]; // 1
int root_1_max = root_1["max"]; // 255

JsonObject root_2 = doc[2];
const char* root_2_name = root_2["name"]; // "pattern"
const char* root_2_label = root_2["label"]; // "Pattern"
const char* root_2_type = root_2["type"]; // "Select"
int root_2_value = root_2["value"]; // 1

JsonArray root_2_options = root_2["options"];
const char* root_2_options_0 = root_2_options[0]; // "Pride"
const char* root_2_options_1 = root_2_options[1]; // "Color Waves"
const char* root_2_options_2 = root_2_options[2]; // "Rainbow Twinkles"
const char* root_2_options_3 = root_2_options[3]; // "Snow Twinkles"

JsonObject root_3 = doc[3];
const char* root_3_name = root_3["name"]; // "palette"
const char* root_3_label = root_3["label"]; // "Palette"
const char* root_3_type = root_3["type"]; // "Select"
int root_3_value = root_3["value"]; // 7

JsonArray root_3_options = root_3["options"];
const char* root_3_options_0 = root_3_options[0]; // "Rainbow"
const char* root_3_options_1 = root_3_options[1]; // "Rainbow Stripe"
const char* root_3_options_2 = root_3_options[2]; // "Cloud"
const char* root_3_options_3 = root_3_options[3]; // "Lava"

JsonObject root_4 = doc[4];
const char* root_4_name = root_4["name"]; // "speed"
const char* root_4_label = root_4["label"]; // "Speed"
const char* root_4_type = root_4["type"]; // "Number"
int root_4_value = root_4["value"]; // 30
int root_4_min = root_4["min"]; // 1
int root_4_max = root_4["max"]; // 255

JsonObject root_5 = doc[5];
const char* root_5_name = root_5["name"]; // "autoplay"
const char* root_5_label = root_5["label"]; // "Autoplay"
const char* root_5_type = root_5["type"]; // "Section"

JsonObject root_6 = doc[6];
const char* root_6_name = root_6["name"]; // "autoplay"
const char* root_6_label = root_6["label"]; // "Autoplay"
const char* root_6_type = root_6["type"]; // "Boolean"
int root_6_value = root_6["value"]; // 255

JsonObject root_7 = doc[7];
const char* root_7_name = root_7["name"]; // "autoplayDuration"
const char* root_7_label = root_7["label"]; // "Autoplay Duration"
const char* root_7_type = root_7["type"]; // "Number"
int root_7_value = root_7["value"]; // 255
int root_7_min = root_7["min"]; // 0
int root_7_max = root_7["max"]; // 255

JsonObject root_8 = doc[8];
const char* root_8_name = root_8["name"]; // "solidColor"
const char* root_8_label = root_8["label"]; // "Solid Color"
const char* root_8_type = root_8["type"]; // "Section"

JsonObject root_9 = doc[9];
const char* root_9_name = root_9["name"]; // "solidColor"
const char* root_9_label = root_9["label"]; // "Color"
const char* root_9_type = root_9["type"]; // "Color"
const char* root_9_value = root_9["value"]; // "255,255,255"

JsonObject root_10 = doc[10];
const char* root_10_name = root_10["name"]; // "fire"
const char* root_10_label = root_10["label"]; // "Fire & Water"
const char* root_10_type = root_10["type"]; // "Section"

JsonObject root_11 = doc[11];
const char* root_11_name = root_11["name"]; // "cooling"
const char* root_11_label = root_11["label"]; // "Cooling"
const char* root_11_type = root_11["type"]; // "Number"
int root_11_value = root_11["value"]; // 49
int root_11_min = root_11["min"]; // 0
int root_11_max = root_11["max"]; // 255

JsonObject root_12 = doc[12];
const char* root_12_name = root_12["name"]; // "sparking"
const char* root_12_label = root_12["label"]; // "Sparking"
const char* root_12_type = root_12["type"]; // "Number"
int root_12_value = root_12["value"]; // 60
int root_12_min = root_12["min"]; // 0
int root_12_max = root_12["max"]; // 255

JsonObject root_13 = doc[13];
const char* root_13_name = root_13["name"]; // "twinkles"
const char* root_13_label = root_13["label"]; // "Twinkles"
const char* root_13_type = root_13["type"]; // "Section"

JsonObject root_14 = doc[14];
const char* root_14_name = root_14["name"]; // "twinkleSpeed"
const char* root_14_label = root_14["label"]; // "Twinkle Speed"
const char* root_14_type = root_14["type"]; // "Number"
int root_14_value = root_14["value"]; // 4
int root_14_min = root_14["min"]; // 0
int root_14_max = root_14["max"]; // 8

JsonObject root_15 = doc[15];
const char* root_15_name = root_15["name"]; // "twinkleDensity"
const char* root_15_label = root_15["label"]; // "Twinkle Density"
const char* root_15_type = root_15["type"]; // "Number"
int root_15_value = root_15["value"]; // 5
int root_15_min = root_15["min"]; // 0
int root_15_max = root_15["max"]; // 8

=================================================================================

const size_t capacity = JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(16) + JSON_ARRAY_SIZE(30) + 4*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 7*JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);

JsonObject doc_0 = doc.createNestedObject();
doc_0["name"] = "power";
doc_0["label"] = "Power";
doc_0["type"] = "Boolean";
doc_0["value"] = 255;

JsonObject doc_1 = doc.createNestedObject();
doc_1["name"] = "brightness";
doc_1["label"] = "Brightness";
doc_1["type"] = "Number";
doc_1["value"] = 255;
doc_1["min"] = 1;
doc_1["max"] = 255;

JsonObject doc_2 = doc.createNestedObject();
doc_2["name"] = "pattern";
doc_2["label"] = "Pattern";
doc_2["type"] = "Select";
doc_2["value"] = 1;

JsonArray doc_2_options = doc_2.createNestedArray("options");
doc_2_options.add("Pride");
doc_2_options.add("Color Waves");
doc_2_options.add("Rainbow Twinkles");
doc_2_options.add("Snow Twinkles");
doc_2_options.add("Cloud Twinkles");
doc_2_options.add("Incandescent Twinkles");
doc_2_options.add("Retro C9 Twinkles");
doc_2_options.add("Red & White Twinkles");
doc_2_options.add("Blue & White Twinkles");
doc_2_options.add("Red, Green & White Twinkles");
doc_2_options.add("Fairy Light Twinkles");
doc_2_options.add("Snow 2 Twinkles");
doc_2_options.add("Holly Twinkles");
doc_2_options.add("Ice Twinkles");
doc_2_options.add("Party Twinkles");
doc_2_options.add("Forest Twinkles");
doc_2_options.add("Lava Twinkles");
doc_2_options.add("Fire Twinkles");
doc_2_options.add("Cloud 2 Twinkles");
doc_2_options.add("Ocean Twinkles");
doc_2_options.add("Rainbow");
doc_2_options.add("Rainbow With Glitter");
doc_2_options.add("Solid Rainbow");
doc_2_options.add("Confetti");
doc_2_options.add("Sinelon");
doc_2_options.add("Beat");
doc_2_options.add("Juggle");
doc_2_options.add("Fire");
doc_2_options.add("Water");
doc_2_options.add("Solid Color");

JsonObject doc_3 = doc.createNestedObject();
doc_3["name"] = "palette";
doc_3["label"] = "Palette";
doc_3["type"] = "Select";
doc_3["value"] = 7;

JsonArray doc_3_options = doc_3.createNestedArray("options");
doc_3_options.add("Rainbow");
doc_3_options.add("Rainbow Stripe");
doc_3_options.add("Cloud");
doc_3_options.add("Lava");
doc_3_options.add("Ocean");
doc_3_options.add("Forest");
doc_3_options.add("Party");
doc_3_options.add("Heat");

JsonObject doc_4 = doc.createNestedObject();
doc_4["name"] = "speed";
doc_4["label"] = "Speed";
doc_4["type"] = "Number";
doc_4["value"] = 30;
doc_4["min"] = 1;
doc_4["max"] = 255;

JsonObject doc_5 = doc.createNestedObject();
doc_5["name"] = "autoplay";
doc_5["label"] = "Autoplay";
doc_5["type"] = "Section";

JsonObject doc_6 = doc.createNestedObject();
doc_6["name"] = "autoplay";
doc_6["label"] = "Autoplay";
doc_6["type"] = "Boolean";
doc_6["value"] = 255;

JsonObject doc_7 = doc.createNestedObject();
doc_7["name"] = "autoplayDuration";
doc_7["label"] = "Autoplay Duration";
doc_7["type"] = "Number";
doc_7["value"] = 255;
doc_7["min"] = 0;
doc_7["max"] = 255;

JsonObject doc_8 = doc.createNestedObject();
doc_8["name"] = "solidColor";
doc_8["label"] = "Solid Color";
doc_8["type"] = "Section";

JsonObject doc_9 = doc.createNestedObject();
doc_9["name"] = "solidColor";
doc_9["label"] = "Color";
doc_9["type"] = "Color";
doc_9["value"] = "255,255,255";

JsonObject doc_10 = doc.createNestedObject();
doc_10["name"] = "fire";
doc_10["label"] = "Fire & Water";
doc_10["type"] = "Section";

JsonObject doc_11 = doc.createNestedObject();
doc_11["name"] = "cooling";
doc_11["label"] = "Cooling";
doc_11["type"] = "Number";
doc_11["value"] = 49;
doc_11["min"] = 0;
doc_11["max"] = 255;

JsonObject doc_12 = doc.createNestedObject();
doc_12["name"] = "sparking";
doc_12["label"] = "Sparking";
doc_12["type"] = "Number";
doc_12["value"] = 60;
doc_12["min"] = 0;
doc_12["max"] = 255;

JsonObject doc_13 = doc.createNestedObject();
doc_13["name"] = "twinkles";
doc_13["label"] = "Twinkles";
doc_13["type"] = "Section";

JsonObject doc_14 = doc.createNestedObject();
doc_14["name"] = "twinkleSpeed";
doc_14["label"] = "Twinkle Speed";
doc_14["type"] = "Number";
doc_14["value"] = 4;
doc_14["min"] = 0;
doc_14["max"] = 8;

JsonObject doc_15 = doc.createNestedObject();
doc_15["name"] = "twinkleDensity";
doc_15["label"] = "Twinkle Density";
doc_15["type"] = "Number";
doc_15["value"] = 5;
doc_15["min"] = 0;
doc_15["max"] = 8;

serializeJson(doc, Serial);


 */

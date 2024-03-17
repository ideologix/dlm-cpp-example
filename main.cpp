#include <iostream>

#include "lib/dlm-cpp/include/client.hpp"
#include "lib/rapidjson/include/rapidjson/document.h"


void StoreTokenInStorage(std::string token) {
    // Serves as an example of when you need to store the token.
}

void DeleteTokenFromStorge() {
    // Serves as an example of when you need to delete the token.
}

int main() {

    std::cout << "====== Digital License Manager Example ======" << std::endl;

    // Initialize the API
    DigitalLicenseManager::Connection conn = DigitalLicenseManager::create_connection(
            "http://dlm.test",
            "v1",
            "ck_211f37385f51f31cf820f28e1c00cc04ed9690bb",
            "cs_fe4970b3468b8452bed2853e550bf5e829401eeb"
    );

    // Declare Response
    DigitalLicenseManager::Response response;

    // Create License
    //response = DigitalLicenseManager::licenses_create(conn, {{"license_key", "XXXOJiqojfoqjXOIAXaaa"}, {"activations_limit", "5"}, {"status", "1"}, {"valid_for", "365"}});
    //std::cout << response.get_contents();
    //exit(1);

    // Declare RapidJSON document
    rapidjson::Document doc;

    // Used variables below
    std::string SampleKey = "K2CH-GIG1-IGC3-2N1K";
    std::string token = "";

    // Optional, applies to Example 1b with additional product id check.
    std::string product_id = "149";

    // 1a. EXAMPLE: /licenses/{key}
    std::cout << "Checking License Key" << std::endl;
    response = DigitalLicenseManager::licenses_get(conn, SampleKey);
    doc.Parse(response.get_contents().c_str());
    if (doc.HasMember("code") && doc.HasMember("message")) {
        std::cout << doc["message"].GetString();
    } else if (doc.HasMember("success") && doc["success"].GetBool()) {
        auto is_expired = doc["data"]["is_expired"].GetBool();
        std::string license_key = doc["data"]["license_key"].GetString();
        if (is_expired) {
            std::cout << "- License is " + license_key + " expired." << std::endl;
        } else {
            std::cout << "- License is " + license_key + " valid." << std::endl;
        }
    } else {
        std::cout << "- Invalid response" << std::endl;
    }

    // 1b. EXAMPLE: /license/{key} - With additional product id verification.
    std::cout << "Checking License Key" << std::endl;
    response = DigitalLicenseManager::licenses_get(conn, SampleKey);
    doc.Parse(response.get_contents().c_str());
    if (doc.HasMember("code") && doc.HasMember("message")) {
        std::cout << doc["message"].GetString();
    } else if (doc.HasMember("success") && doc["success"].GetBool()) {
        auto is_expired = doc["data"]["is_expired"].GetBool();
        auto l_product_id = doc["data"]["product_id"].GetInt();
        if(l_product_id != std::stoi(product_id)) {
            std::cout << "- Unable to verify license. Product and license does not match." << std::endl;
        } else {
            std::string license_key = doc["data"]["license_key"].GetString();
            if (is_expired) {
                std::cout << "- License is " + license_key + " expired." << std::endl;
            } else {
                std::cout << "- License is " + license_key + " valid." << std::endl;
            }
        }
    } else {
        std::cout << "- Invalid response" << std::endl;
    }

    // 2. EXAMPLE: /licenses/activate/{license_key}
    std::cout << "Activating token" << std::endl;
    response = DigitalLicenseManager::licenses_activate(conn, SampleKey, "Device X");
    doc.Parse(response.get_contents().c_str());
    if (doc.HasMember("code") && doc.HasMember("message")) {
        std::cout << doc["message"].GetString() << std::endl;
    } else if (doc.HasMember("success") && doc["success"].GetBool()) {
        token = doc["data"]["token"].GetString(); // Store the token somewhere securely.
        StoreTokenInStorage(token); // Example...
        std::cout << "- License " + SampleKey + " activated..." << std::endl;
        std::cout << "- Token " + token + " SET." << std::endl;
    } else {
        std::cout << "- Invalid response" << std::endl;
    }

    // 3. EXAMPLE: /licenses/validate/{token}
    std::cout << "Validating token" << std::endl;
    if (!token.empty()) {
        response = DigitalLicenseManager::licenses_validate(conn, token);
        doc.Parse(response.get_contents().c_str());
        if (doc.HasMember("code") && doc.HasMember("message")) {
            std::cout << doc["message"].GetString() << std::endl;
        } else if (doc.HasMember("success") && doc["success"].GetBool()) {
            token = doc["data"]["token"].GetString(); // Store the token somewhere securely.
            StoreTokenInStorage(token); // Example...
            std::cout << "- Token " + token + " is valid..." << std::endl;
            if (doc["data"].HasMember("license")) {
                bool is_expired = doc["data"]["license"]["is_expired"].GetBool();
                std::string license_key = doc["data"]["license"]["license_key"].GetString();
                if (is_expired) {
                    std::cout << "- License " + license_key + " is expired." << std::endl;
                } else {
                    std::cout << "- License " + license_key + " is valid." << std::endl;
                }
            } else {
                std::cout << "- License NOT found." << std::endl;
            }
        } else {
            std::cout << "- Invalid response" << std::endl;
        }
    } else {
        std::cout << "- Token NOT found." << std::endl;
    }

    // 4. EXAMPLE /licenses/deactivate/{token}
    std::cout << "Deactivating token" << std::endl;
    if (!token.empty()) {
        response = DigitalLicenseManager::licenses_deactivate(conn, token);
        doc.Parse(response.get_contents().c_str());
        if (doc.HasMember("code") && doc.HasMember("message")) {
            std::cout << doc["message"].GetString() << std::endl;
        } else if (doc.HasMember("success") && doc["success"].GetBool()) {
            DeleteTokenFromStorge(); // Example...
            std::cout << "- Token " + token + " deactivated..." << std::endl;
        } else {
            std::cout << "- Invalid response" << std::endl;
        }
    } else {
        std::cout << "- Token NOT found." << std::endl;
    }

    return 0;
}

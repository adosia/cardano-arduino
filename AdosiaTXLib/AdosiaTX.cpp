#include <FS.h> 

#include "Arduino.h"
#include "AdosiaTX.h"

#include <Ed25519.h>                      // Ed25519 cryptography library

#define USE_SERIAL Serial

void AdosiaTX::create_ed25519_keyfile() {
  Ed25519::generatePrivateKey(ed25519_privateKey);

  SPIFFS.begin();
  // SPIFFS.remove("/y.skey");
  
  if( SPIFFS.exists("/y.skey") ) {
    Serial.println("\nskey file exists.");
    return;
  }
    
  // open the config file in write mode
  File f = SPIFFS.open("/y.skey", "w");
 
  if (!f) {
    Serial.println("\nerror creating file");
    return;    
  } else {
     Serial.println("\nNo skey file found.");
     Serial.println("\nCreating skey file.");
    
    // write private key to file
    uint8_t i;
    for (i = 0; i < (uint8_t)(sizeof(ed25519_privateKey)); i++) {
     f.print(ed25519_privateKey[i], HEX);
     Serial.print(ed25519_privateKey[i], HEX);
    }
    
    Serial.println("\nsKey file created");
    f.close();
    return;
  }
  
  f.close();
  return;
}

String AdosiaTX::load_ed25519_keyfile() {
  SPIFFS.begin();
    
  // this opens the file "c.txt" in read-mode
  File f = SPIFFS.open("/y.skey", "r");
  
  if(!f){
   Serial.println("\nFailed to open file for reading");
   return String();
  }
  
  Serial.println("\nReading from file:");
  String psk;
  while(f.available()){
    psk+=String((char)f.read());
  };
    
  Serial.println("psk: ");
  Serial.println(psk);
  
  return psk;
}

void AdosiaTX::sign_ed25519_tx(String tx) {
    // String tx = "ADOSIA WICKED IOT";
    char msg[1096];
    tx.toCharArray(msg, 1096);
    
    const char* psk = load_ed25519_keyfile().c_str();
    Serial.print(psk);
    
    uint8_t *pkk = (unsigned char*)psk;
        
    Serial.println("\nDeriving pub key from skey for singing");
    Ed25519::derivePublicKey(ed25519_publicKey, pkk);
        
    uint8_t i;
    for (i = 0; i < (uint8_t)(sizeof(ed25519_publicKey)); i++) {
      Serial.print(ed25519_publicKey[i], HEX);
    }
    
    Serial.println("\nSigning message: ");
    Serial.write(msg);
    Ed25519::sign(signature, pkk, ed25519_publicKey, msg, 1096);
           
    Serial.println("\nVerifying signed message: ");
    if (!Ed25519::verify(signature, ed25519_publicKey, msg, 1096)) {
       Serial.println("\nverification failed");
    }
    else
      Serial.println("\nsignature verified");    
    
    return;
}

void AdosiaTX::checkFiles() {
    SPIFFS.begin();
    String str = "";
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
        str += dir.fileName();
        str += " / ";
        str += dir.fileSize();
        str += "\r\n";
    }
    Serial.println(str);
    
    return;
}

void AdosiaTX::genPrivKey() {
    Serial.println("\nGenerating ed25519 Key.");
    Serial.println("Done!!");
    
    uint8_t i;

    for (i = 0; i < (uint8_t)(sizeof(ed25519_privateKey)); i++) {
     if (ed25519_privateKey[i] < 0x10) { /* To print "0F", not "F" */
      Serial.write('0');
     }
     Serial.print(ed25519_privateKey[i], HEX);
    }
    
    return;
}


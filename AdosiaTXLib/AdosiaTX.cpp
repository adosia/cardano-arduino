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

void AdosiaTX::remove_ed25519_keyfile() {
    SPIFFS.begin();
    
    Serial.println("\nRemoving all sKey files");
    SPIFFS.remove("/y.skey");
    
    return;
}

String AdosiaTX::load_ed25519_keyfile() {
  SPIFFS.begin();
  // this opens the file "c.txt" in read-mode
  File f = SPIFFS.open("/y.skey", "r");
  
  if(!f){   
    // Serial.println("\nFailed to open file for reading");
    String err = "error";
    String error;
    uint8_t j;
    for (j = 0; j < (uint8_t)(sizeof(err)); j++) {
      // Serial.print(err[j], HEX);
      error = error + err[j];
    };
    return error;
  }else{
    Serial.println("\nFound sKey");
    String psk;
    while(f.available()){
      psk+=String((char)f.read());
    };
    return psk;
  };
}

String AdosiaTX::sign_ed25519_tx( String tx, const char* psk ) {
  char msg[1096];
  tx.toCharArray(msg, 1096);
  
  uint8_t *pkk = (unsigned char*)psk;
        
  Serial.println("\nDeriving pub key from skey for singing");
  Ed25519::derivePublicKey(ed25519_publicKey, pkk);
  
  /*
  uint8_t i;
  for (i = 0; i < (uint8_t)(sizeof(ed25519_publicKey)); i++) {
    Serial.print(ed25519_publicKey[i], HEX);
  };
  */
  
  Serial.println("\nSigning tx");
  // Serial.write(msg);  
  Ed25519::sign(signature, pkk, ed25519_publicKey, msg, 1096);
  
  String txSignature;
  uint8_t j;
  for (j = 0; j < (uint8_t)(sizeof(signature)); j++) {
    // Serial.print(signature[j], HEX);
    txSignature = txSignature + signature[j];
  };
  
  bool verify = verify_ed25519_tx(tx, pkk, signature);
  
  if(!verify){
    String err = "error";
    String error;
    uint8_t j;
    for (j = 0; j < (uint8_t)(sizeof(err)); j++) {
      // Serial.print(err[j], HEX);
      error = error + err[j];
    };
    return error;
  };
  
  //Serial.println(txSignature);
  return txSignature;
}

bool AdosiaTX::verify_ed25519_tx( String tx, uint8_t *pkk, uint8_t* signature ) {
  char msg[1096];
  uint8_t ed25519_publicKey[32];
  tx.toCharArray(msg, 1096);
     
  // Serial.println("\nDeriving pub key from skey for singing");
  Ed25519::derivePublicKey(ed25519_publicKey, pkk);
  
  Serial.println("\nVerifying signed message");
  if (!Ed25519::verify(signature, ed25519_publicKey, msg, 1096)) {
    Serial.println("\nverification failed");
    return false;
  }else{
    Serial.println("\nsignature verified");
    return true;
  };
}

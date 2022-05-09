/*
  AdosiaTX.h - Library for singing transactions.
  Created by Adosia.
  Released into the public domain.
*/
#ifndef AdosiaTX_h
#define AdosiaTX_h

#include "Arduino.h"

class AdosiaTX {
  public:
    uint8_t signature[64];
    uint8_t ed25519_privateKey[32];
    uint8_t ed25519_publicKey[32];
    void create_ed25519_keyfile();
    String load_ed25519_keyfile();
    void sign_ed25519_tx(String tx);
    void printHex();
    void genPrivKey();
    void checkFiles();
};

#endif

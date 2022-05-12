 About:
 
 This library contains the following functions.
    
   `void create_ed25519_keyfile();`<br />
   `void remove_ed25519_keyfile();`<br />
   `String load_ed25519_keyfile();`<br />
   `String sign_ed25519_tx( String tx, const char* psk );`<br />
   `bool verify_ed25519_tx( String tx, uint8_t *pkk, uint8_t* signature );`<br />
    
    
   <details>
   <summary><b>create_ed25519_keyfile()</b></summary>

    :: This function checks if a ed25519 key file exists on the device if not it creates one.
   </details>

   <details>
   <summary><b>remove_ed25519_keyfile()</b></summary>

    :: This function removes all key files on the device.
   </details>
   
   <details>
   <summary><b>load_ed25519_keyfile()</b></summary>

    :: This function opens the ed25519 file if it exists and returns the psk.
   </details>   
  
   <details>
   <summary><b>sign_ed25519_tx(String tx, const char* psk)</b></summary>

    :: This function takes in a tx and the private key obtained with `load_ed25519_keyfile()` and creates a signature for it and also verifies.
   </details>

   <details>
   <summary><b>verify_ed25519_tx( String tx, uint8_t *pkk, uint8_t* signature )</b></summary>

    :: This function will take in your tx, private key from `load_ed25519_keyfile()` and signature from  `sign_ed25519_tx` functions and verify the signature matches the hash. This function is also used in sign_ed25519_tx as an extra measure.
   </details>
 
   How to Use:
 
   Make sure you take all the library folders included in this directory and move them to your OS Adruino library folder.
   Once you load up the example sketch and all the included libraries are in the correct places on your system you sohuld be able to compile and use.

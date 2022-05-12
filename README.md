 About:
 
 This library contianes the following functions.
    
   `void create_ed25519_keyfile();`
   `void remove_ed25519_keyfile();`
   `String load_ed25519_keyfile();`
   `String sign_ed25519_tx( String tx, const char* psk );`
   `bool verify_ed25519_tx( String tx, uint8_t *pkk, uint8_t* signature );`
    
    
   <details>
   <summary><b>create_ed25519_keyfile()</b></summary>

    :: This function checks if a ed25519 key file exists on the device if not it creates one.
   </details>
   
   
   **remove_ed25519_keyfile()** :: This function removes all key files on the device.
   
   **load_ed25519_keyfile()** :: This function opens the ed25519 file if it exists and returns the psk.
 
   **sign_ed25519_tx(String tx, const char* psk)** :: This function takes a generates tx and the private key obntained with `load_ed25519_keyfile()` and creates a signature for it and also verifies.
 
   **verify_ed25519_tx( String tx, uint8_t *pkk, uint8_t* signature )** :: This function will take in your tx, private key from `load_ed25519_keyfile()` and signature from  `sign_ed25519_tx` functions and verify the sig matches. This function is also used in sign_ed25519_tx as an extra measure.
 
   In the 'Example' folder there is a sketch that lets you play with all three of these functions.

 
   How to Use:
 
   Make sure you take all the library folders included in this directory and move them to your OS Adruino library folder.
   Once you load up the example sketch and all the library folders are i thier correct places you sohuld be able to compile and use.
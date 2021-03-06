#include <AdosiaTX.h>
#include <string>

AdosiaTX atx;

void setup() {
  Serial.begin(115200);

  //Example serialized cbor tx to sign
  String tx = "82a500818258206d5e2ccbdade2e6c1813a8df14cacf63a4e7c3cd9ad75d3007543cd3c82473f40001818258390193d63b8b1f0963d24929efd4e315f7343ae57117d00f5b6c610cd914a9f3414d87b331d7a34b711e07d90c8a0659ff99665bf3c6ae6138a01a00140118021a0002e248031a00895440075820ff7300a5aad784af04a56befcd3070ad7b6236e30ee35efcd7fdd1e5d4b1c62ea101a66743686f69636573a3623135a36b43616e6469646174654964782464393133633136642d633865612d346138622d613232352d66633234343034613536326668566f746552616e6b016a566f746557656967687401623232a36b43616e6469646174654964782466306434316361652d323339332d343562622d393635322d38396234326331373266653568566f746552616e6b026a566f746557656967687401623233a36b43616e6469646174654964782463656135626361352d316163612d346461612d396333622d65356335343364633834663968566f746552616e6b036a566f746557656967687401694e6574776f726b49646653504f4352416a4f626a656374547970656a566f746542616c6c6f746d4f626a65637456657273696f6e65312e302e306a50726f706f73616c4964782430306438663633622d396566622d343162362d393064632d33356439306635616434653267566f7465724964782438343537653237662d613134632d343232362d616335652d326662336433633637623738";

  // This function checks if there is a skey file if no it creates a new one if there is it ignores and let you know.
  // atx.create_ed25519_keyfile();

  // This function removes all traces of any sKey files.
  // atx.remove_ed25519_keyfile();

  // Load the above created skey file so we can use it.
  const char* psk = atx.load_ed25519_keyfile().c_str();
  Serial.println(psk);
  if(std::string(psk) == "error"){
    Serial.println("\nFailed to open file for reading");
  } else if (std::string(psk) == ""){
    Serial.println("\nFailed to open file for reading");
  } else {
    // use the above loaded key to sign our tx with and returns the signature if valid and error if not.
    const char* txSignature = atx.sign_ed25519_tx(tx, psk).c_str();
    Serial.println("\nTX Signature");
    Serial.println(txSignature);
  };
}

void loop() {
  // put your main code here, to run repeatedly:

}

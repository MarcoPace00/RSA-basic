import <iostream>;
import <cmath>;
//import Test_module;
import Vigenere;


void test_vigenere_imports() {
	//MyFunc();
	std::cout << to_lower_hardcoded("Test DI FUNZIONE IMPORTATA da MODULO Vigenere\n");
	std::string msg = "Messaggio di prova";
	std::string test_key = "Chiave";
	std::string encrypted = crypt(test_key, msg);
	std::cout << decrypt(test_key, encrypted) << " " << msg + "\n";
}

std::string int_to_string(int& input) {
	if (input == 0) return "a"; // '0' -> 'a'

	//std::cout << "Chiave numerica: " << input << "\n\n";
	std::string output;

	while (input > 0) {
		int new_digit = input % 10;
		output = char('a' + new_digit) + output; // Convert 0-9 to 'a'-'j'
		input /= 10;
	}

	//std::cout << "Chiave leggibile: " << output << "\n\n";
	return output;
}




int main() {
	//	KEY SHARING
	// 
	// (0) Choice of g, primitive root e p, prime number. Both are public.
	int p = 31;
	int g = 24;
	// (1) Choice of a, Alice's private key, and b, Bob's private key.
	int a = 11;
	int b = 17;
	// (2.1) Alice sends g^a mod p, due to the discrete log problem a is hidden.
	int bob_g_a = (int)(std::pow(g, a)) % p;
	// (2.2) Bob sends g^b mod p, due to the discrete log problem b is hidden.
	//int alice_g_b = (g ^ b) % p;
	int alice_g_b = (int)(std::pow(g, b)) % p;
	// (3) Alice and Bob compute their key K = g^(b*a) mod p = g^(a*b) mod p. 
	//		Such key is known only to Alice and Bob due to the secrecy of a and b.
	int alice_key_int = (int) std::pow(alice_g_b, a) % p;

	int bob_key_int = (int)std::pow(bob_g_a, a) % p;

	if (alice_key_int == bob_key_int) {
		std::cout << "YEAH: alice and bob shared a key in public! The key (mod p) is: \n"
			<< alice_key_int<<"\n";
	}
	else {
		std::cout << "ERROR: alice and bob have different keys\n";
		return -1;
	}

	if (alice_key_int < 0) { // not necessary but I want the keys positive
		alice_key_int = alice_key_int + p;
		bob_key_int = bob_key_int + p;
	}

	

	//test_vigenere_imports();

	// MESSAGE ENCRYPTION AND DECRIPTION VIA VIGENERE
	// (0) The digits of the keys are converted to a string so that
	//		Alice and Bob can computes the antikey.

	std::string alice_key_str = int_to_string(alice_key_int);
	std::string bob_key_str = int_to_string(bob_key_int);

	std::cout << "Alice key: " + alice_key_str + "\n"
		 + "Bob key: " + bob_key_str + "\n\n";
	// (1) Alice writes a message to be encrypted using Vigenere
	std::string alice_msg = "Hello Bob, whatsapp?";
	std::string encripted_msg = crypt(alice_key_str, alice_msg);
	// (2) Bob decripts the message using the antikey
	std::cout << "Bob receives: " + decrypt(bob_key_str, encripted_msg);

	return 0;
}